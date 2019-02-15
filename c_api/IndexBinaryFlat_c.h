/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD+Patents license found in the
 * LICENSE file in the root directory of this source tree.
 */

// -*- c -*-

#ifndef INDEX_BINARY_FLAT_C_H
#define INDEX_BINARY_FLAT_C_H

#include <stddef.h>
#include <stdint.h>
#include "faiss_c.h"
#include "IndexBinary_c.h"

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
typedef enum FaissMetricType FaissMetricType;

/** Binary Index that stores the full vectors and performs exhaustive search. */
FAISS_DECLARE_CLASS_INHERITED(IndexBinaryFlat, IndexBinary)
FAISS_DECLARE_DESTRUCTOR(IndexBinaryFlat)

int faiss_IndexBinaryFlat_new(FaissIndexBinaryFlat** p_index, idx_t d);

/** get a pointer to the index's internal data (the `xb` field). The outputs
 * become invalid after any data addition or removal operation.
 * 
 * @param index   opaque pointer to index object
 * @param p_xb    output, the pointer to the beginning of `xb`.
 * @param p_size  output, the current size of `xb` in number of bytes (`ntotal * d / 8`).
 */
void faiss_IndexBinaryFlat_xb(FaissIndexBinaryFlat* index, uint8_t** p_xb, size_t* p_size);

/** attempt a dynamic cast to a flat index, thus checking
 * check whether the underlying index type is `IndexBinaryFlat`.
 * 
 * @param index opaque pointer to index object
 * @return the same pointer if the index is a flat binary index, NULL otherwise
 */
FAISS_DECLARE_INDEX_DOWNCAST(IndexBinaryFlat)

/** Select between using a heap or counting to select the k smallest values
 * when scanning inverted lists.
 */
FAISS_DECLARE_GETTER(IndexBinaryFlat, int, use_heap)
FAISS_DECLARE_GETTER(IndexBinaryFlat, size_t, query_batch_size)

#ifdef __cplusplus
}
#endif

#endif  // INDEX_BINARY_FLAT_C_H
