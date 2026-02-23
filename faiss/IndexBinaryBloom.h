/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// -*- c++ -*-

#ifndef INDEX_BINARY_BLOOM_H
#define INDEX_BINARY_BLOOM_H

#include <vector>

#include <faiss/IndexBinary.h>

#include <faiss/impl/maybe_owned_vector.h>

namespace faiss {

/// Forward declarations see AuxIndexStructures.h
struct RejectionResult;

struct SegmentsResult;

/** Index that allows an efficient neighborhood dismembership test. */
struct IndexBinaryBloom {
    int d;

    /// A bitmap that tracks presence of 16-bit segments of the database
    /// vectors. size: 512 * d
    MaybeOwnedVector<uint8_t> bitmap;

    idx_t code_size; /// = (d / 8)

    IndexBinaryBloom(idx_t d);

    /// Add given vectors to the index.
    void add(idx_t n, const uint8_t* x);

    /// Clear all data from the index and reset it.
    void reset();

    /// Determine if any of the query vectors are guaranteed
    /// to lie outside the radius from all the indexed vectors.
    void should_reject(
            idx_t n,
            const uint8_t* x,
            int acceptance_radius,
            RejectionResult* result) const;

    /// Get all indexed uint16_t's for every 16-bit segment of the indexed
    /// vectors.
    void segments(SegmentsResult* result) const;
};

} // namespace faiss

#endif // INDEX_BINARY_BLOOM_H
