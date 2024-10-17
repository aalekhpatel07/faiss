/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Copyright 2004-present Facebook. All Rights Reserved
// -*- c -*-

#ifndef FAISS_INDEX_BINARY_FLAT_C_H
#define FAISS_INDEX_BINARY_FLAT_C_H

#include "IndexBinary_c.h"
#include "faiss_c.h"

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
typedef enum FaissMetricType FaissMetricType;

/** Opaque type for IndexFlat */
FAISS_DECLARE_CLASS_INHERITED(IndexBinaryFlat, IndexBinary)

int faiss_IndexBinaryFlat_new(FaissIndexBinaryFlat** p_index);

int faiss_IndexBinaryFlat_new_with(
        FaissIndexBinaryFlat** p_index,
        idx_t d,
        FaissMetricType metric);

/** get a pointer to the index's internal data (the `xb` field). The outputs
 * become invalid after any data addition or removal operation.
 *
 * @param index   opaque pointer to index object
 * @param p_xb    output, the pointer to the beginning of `xb`.
 * @param p_size  output, the current size of `sb` in number of float values.
 */
void faiss_IndexBinaryFlat_xb(FaissIndexBinaryFlat* index, uint8_t** p_xb, size_t* p_size);

/** attempt a dynamic cast to a flat index, thus checking
 * check whether the underlying index type is `IndexFlat`.
 *
 * @param index opaque pointer to index object
 * @return the same pointer if the index is a flat index, NULL otherwise
 */
FAISS_DECLARE_INDEX_DOWNCAST_BINARY(IndexBinaryFlat)

FAISS_DECLARE_DESTRUCTOR(IndexBinaryFlat)

/** compute distance with a subset of vectors
 *
 * @param index   opaque pointer to index object
 * @param x       query vectors, size n * d
 * @param labels  indices of the vectors that should be compared
 *                for each query vector, size n * k
 * @param distances
 *                corresponding output distances, size n * k
 */
int faiss_IndexBinaryFlat_compute_distance_subset(
        FaissIndexBinary* index,
        idx_t n,
        const uint8_t* x,
        idx_t k,
        const uint8_t* distances,
        const idx_t* labels);

/** Opaque type for IndexBinaryFlatL2 */
FAISS_DECLARE_CLASS_INHERITED(IndexBinaryFlatL2, Index)

FAISS_DECLARE_INDEX_DOWNCAST_BINARY(IndexBinaryFlatL2)
FAISS_DECLARE_DESTRUCTOR(IndexBinaryFlatL2)

int faiss_IndexBinaryFlatL2_new(FaissIndexBinaryFlatL2** p_index);

int faiss_IndexBinaryFlatL2_new_with(FaissIndexBinaryFlatL2** p_index, idx_t d);

/** Opaque type for IndexBinaryFlat1D
 *
 * optimized version for 1D "vectors"
 */
FAISS_DECLARE_CLASS_INHERITED(IndexBinaryFlat1D, Index)

FAISS_DECLARE_INDEX_DOWNCAST_BINARY(IndexBinaryFlat1D)
FAISS_DECLARE_DESTRUCTOR(IndexBinaryFlat1D)

int faiss_IndexBinaryFlat1D_new(FaissIndexBinaryFlat1D** p_index);
int faiss_IndexBinaryFlat1D_new_with(
        FaissIndexBinaryFlat1D** p_index,
        int continuous_update);

int faiss_IndexBinaryFlat1D_update_permutation(FaissIndexBinaryFlat1D* index);

#ifdef __cplusplus
}
#endif

#endif
