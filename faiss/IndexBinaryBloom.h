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

/** Index that allows an efficient neighborhood dismembership test. */
struct IndexBinaryBloom {
    int d;

    /// A bitmap that tracks presence of 16-bit segments of the database
    /// vectors. size: 512 * d
    MaybeOwnedVector<uint8_t> bitmap;

    idx_t code_size; /// = (d / 8)

    IndexBinaryBloom(idx_t d);

    void add(idx_t n, const uint8_t* x);

    void reset();

    void reject(idx_t n, const uint8_t* x, RejectionResult* result) const;
};

} // namespace faiss

#endif // INDEX_BINARY_BLOOM_H
