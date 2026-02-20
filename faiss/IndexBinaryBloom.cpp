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
    for (int segment_idx = 0; segment_idx < (d / 16); segment_idx += 16) {
        uint16_t segment;
        size_t segment_offset = segment_idx;
        segment_offset *= 1 << 16;
        for (int i = 0; i < n * code_size; i += code_size) {
            // read the two bytes in LE into the segment.
            std::memcpy(&segment, x + i + segment_idx, sizeof(segment));
            size_t segment_val = segment;

            size_t byte_offset = segment_val / 8;
            size_t bit_offset = segment_val % 8;

            bitmap[segment_offset + byte_offset] ^= (1 << bit_offset);
        }
    }
}

void IndexBinaryBloom::reset() {
    bitmap.clear();
}

void IndexBinaryBloom::reject(
        idx_t n,
        const uint8_t* x,
        RejectionResult* result) const {
    for (int i = 0; i < n * code_size; i += code_size) {
        bool segment_hit = false;
        for (int segment_idx = 0; segment_idx < (d / 16); segment_idx += 16) {
            uint16_t segment;

            size_t segment_offset = segment_idx;
            segment_offset *= 1 << 16;

            std::memcpy(&segment, x + i + segment_idx, sizeof(segment));
            size_t segment_val = segment;

            size_t byte_offset = segment_val / 8;
            size_t bit_offset = segment_val % 8;

            size_t value = bitmap[segment_offset + byte_offset];

            if (value & (1 << bit_offset)) {
                segment_hit = true;
                break;
            }
        }
        // if none of the segments had been seen before,
        // we're guaranteed the query vector is at least
        // a distance of (d / 16)-away from any of the
        // vectors in the database.
        result->set(i / code_size, !segment_hit);
    }
}
} // namespace faiss
