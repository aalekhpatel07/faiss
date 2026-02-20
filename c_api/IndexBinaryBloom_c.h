/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// -*- c -*-

#ifndef FAISS_INDEX_BINARY_BLOOM_C_H
#define FAISS_INDEX_BINARY_BLOOM_C_H

#include <stddef.h>
#include "Index_c.h"
#include "faiss_c.h"

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration required here
FAISS_DECLARE_CLASS(RejectionResult)

/// Opaque type for referencing to a binary index bloom object
FAISS_DECLARE_CLASS(IndexBinaryBloom)
FAISS_DECLARE_DESTRUCTOR(IndexBinaryBloom)

/// Getter for d
FAISS_DECLARE_GETTER(IndexBinaryBloom, int, d)

/**
 * Create a new Binary Bloom index for vectors of the given dimension.
 */
int faiss_IndexBinaryBloom_new(
	FaissIndexBinaryBloom** p_index,
	idx_t d);

/** Add n vectors of dimension d to the index.
 *
 * This function slices the input vectors in chunks smaller than
 * blocksize_add and calls add_core.
 * @param index  opaque pointer to index object
 * @param x      input matrix, size n * d
 */
int faiss_IndexBinaryBloom_add(
        FaissIndexBinaryBloom* index,
        idx_t n,
        const uint8_t* x);

/** Determine if any of the query vectors can be rejected safely,
 * guaranteeing it does not fall within a reasonably small neighborhood
 * of any vector from the database.
 *
 * @param index       opaque pointer to index object
 * @param x           input vectors to search, size n * d
 * @param result      result list, where true indicates the corresponding query
 * can be rejected safely.
 */
int faiss_IndexBinaryBloom_reject(
        const FaissIndexBinaryBloom* index,
        idx_t n,
        const uint8_t* x,
        FaissRejectionResult* result);

/** removes all elements from the cache.
 * @param index       opaque pointer to index object
 */
int faiss_IndexBinaryBloom_reset(FaissIndexBinaryBloom* index);

#ifdef __cplusplus
}
#endif

#endif
