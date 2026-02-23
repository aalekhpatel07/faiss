/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// -*- c++ -*-

#include <faiss/IndexBinaryBloom.h>

#include <faiss/impl/AuxIndexStructures.h>
#include <faiss/impl/FaissAssert.h>
#include <faiss/impl/maybe_owned_vector.h>
#include <cstdint>
#include <cstring>

namespace faiss {

IndexBinaryBloom::IndexBinaryBloom(idx_t d) : d(d), code_size(d / 8) {
    FAISS_THROW_IF_NOT(d % 16 == 0);
    bitmap = MaybeOwnedVector<uint8_t>(512 * (d / 16));
}

void IndexBinaryBloom::add(idx_t n, const uint8_t* x) {
    for (size_t segment_offset = 0; segment_offset < 512 * d;
         segment_offset += 8192) {
        uint16_t segment;
        size_t segment_idx = segment_offset / 8192;

        for (int query = 0; query < n * code_size; query += code_size) {
            // read the two bytes in LE into the segment.
            std::memcpy(&segment, x + query + segment_idx, 2);

            // treat the value as usize.
            size_t segment_val = segment;

            size_t byte_offset = segment_val / 8;
            size_t bit_offset = segment_val % 8;

            bitmap[segment_offset + byte_offset] |= (1 << (7 - bit_offset));
        }
    }
}

void IndexBinaryBloom::reset() {
    bitmap.clear();
}

void IndexBinaryBloom::should_reject(
        idx_t n,
        const uint8_t* x,
        int acceptance_radius,
        RejectionResult* result) const {

    // Even if none of the segments match,
    // we can only guarantee the query vectors
    // are at least (d / 16) distance away.
    // So, if vectors at that distance or farther
    // are acceptable, then we can't take the fast
    // rejection path for any of them.
    if ((d / 16) <= acceptance_radius) {
        for (int query_idx = 0; query_idx < n; query_idx++) {
            result->set(query_idx, false);
        }
        return;
    }

    for (int query = 0; query < n * code_size; query += code_size) {
        int segments_missed = 0;
        bool should_reject = false;

        for (size_t segment_offset = 0; segment_offset < 512 * d;
             segment_offset += 8192) {
            uint16_t segment;
            size_t segment_idx = segment_offset / 8192;

            std::memcpy(&segment, x + query + segment_idx, 2);
            size_t segment_val = segment;

            size_t byte_offset = segment_val / 8;
            size_t bit_offset = segment_val % 8;

            size_t value = bitmap[segment_offset + byte_offset];

            if (!(value & (1 << (7 - bit_offset)))) {
                segments_missed++;
                if (segments_missed > acceptance_radius) {
                    should_reject = true;
                    break;
                }
            }
        }
        // if some X segments haven't been seen before,
        // we're guaranteed the query vector is at least
        // a distance of X-away from any of the
        // vectors in the database.
        result->set(query / code_size, should_reject);
    }
}

void IndexBinaryBloom::segments(SegmentsResult* result) const {
    for (size_t segment_offset = 0; segment_offset < 512 * d;
         segment_offset += 8192) {
        size_t segment_idx = segment_offset / 8192;

        for (size_t offset = 0; offset < 8192; offset += 8) {
            uint64_t block;
            std::memcpy(&block, bitmap.data() + segment_offset + offset, 8);

            uint64_t mask = 1UL << 63;
            size_t bit_offset = 0;

            while (mask) {
                if (block & mask) {
                    size_t value = 64 * offset + bit_offset;
                    result->set(segment_idx, (uint16_t) value);
                }
                bit_offset++;
                mask >>= 1;
            }
        }
    }
}
} // namespace faiss
