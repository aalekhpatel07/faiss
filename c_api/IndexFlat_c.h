/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD+Patents license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Copyright 2004-present Facebook. All Rights Reserved
// -*- c -*-

#ifndef FAISS_INDEX_FLAT_C_H
#define FAISS_INDEX_FLAT_C_H

#include "Index_c.h"
#include "faiss_c.h"

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
typedef enum FaissMetricType FaissMetricType;

/** Opaque type for IndexFlat */
FAISS_DECLARE_CLASS_INHERITED(IndexFlat, Index)

int faiss_IndexFlat_create(FaissIndexFlat** p_index);

int faiss_IndexFlat_create_with(FaissIndexFlat** p_index, idx_t d, FaissMetricType metric);

FAISS_DECLARE_DESTRUCTOR(IndexFlat)

/** compute distance with a subset of vectors
 *
 * @param index   opaque pointer to index object
 * @param x       query vectors, size n * d
 * @param labels  indices of the vectors that should be compared
 *                for each query vector, size n * k
 * @param distances
 *                corresponding output distances, size n * k
 */
int faiss_IndexFlat_compute_distance_subset(
    FaissIndex *index,
    idx_t n,
    const float *x,
    idx_t k,
    float *distances,
    const idx_t *labels);

/** Opaque type for IndexFlatIP */
FAISS_DECLARE_CLASS_INHERITED(IndexFlatIP, IndexFlat)

int faiss_IndexFlatIP_new(FaissIndexFlatIP** p_index);

int faiss_IndexFlatIP_new_with(FaissIndexFlatIP** p_index, idx_t d);

/** Opaque type for IndexFlatL2 */
FAISS_DECLARE_CLASS_INHERITED(IndexFlatL2, IndexFlat)

int faiss_IndexFlatL2_new(FaissIndexFlatL2** p_index);

int faiss_IndexFlatL2_new_with(FaissIndexFlatL2** p_index, idx_t d);

/** Opaque type for IndexFlatL2BaseShift
 *
 * same as an IndexFlatL2 but a value is subtracted from each distance
 */
FAISS_DECLARE_CLASS_INHERITED(IndexFlatL2BaseShift, IndexFlatL2)

int faiss_IndexFlatL2BaseShift_new(FaissIndexFlatL2BaseShift** p_index, idx_t d, size_t nshift, const float *shift);

/** Opaque type for IndexRefineFlat
 *
 * Index that queries in a base_index (a fast one) and refines the
 * results with an exact search, hopefully improving the results.
 */
FAISS_DECLARE_CLASS_INHERITED(IndexRefineFlat, Index)

int faiss_IndexRefineFlat_new(FaissIndexRefineFlat** p_index, FaissIndex* base_index);

FAISS_DECLARE_DESTRUCTOR(IndexRefineFlat)

/** Opaque type for IndexFlat1D
 * 
 * optimized version for 1D "vectors"
 */
FAISS_DECLARE_CLASS_INHERITED(IndexFlat1D, IndexFlatL2)

int faiss_IndexFlat1D_new(FaissIndexFlat1D** p_index);
int faiss_IndexFlat1D_new_with(FaissIndexFlat1D** p_index, int continuous_update);

int faiss_IndexFlat1D_update_permutation(FaissIndexFlat1D* index);

#ifdef __cplusplus
}
#endif

#endif