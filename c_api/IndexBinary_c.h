/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD+Patents license found in the
 * LICENSE file in the root directory of this source tree.
 */

// -*- c -*-

#ifndef FAISS_INDEX_BINARY_C_H
#define FAISS_INDEX_BINARY_C_H

#include <stddef.h>
#include <stdint.h>
#include "faiss_c.h"
#include "Index_c.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Forward declaration, see AuxIndexStructures_c.h
FAISS_DECLARE_CLASS(RangeSearchResult)

/** Abstract structure for a binary index.
 *
 * Supports adding vertices and searching them.
 *
 * All queries are symmetric because there is no distinction between codes and
 * vectors.
 */
FAISS_DECLARE_CLASS(IndexBinary)
FAISS_DECLARE_DESTRUCTOR(IndexBinary)

/// Getter for d
FAISS_DECLARE_GETTER(IndexBinary, int, d)

/// Getter for code_size
FAISS_DECLARE_GETTER(IndexBinary, int, code_size)

/// Getter for is_trained
FAISS_DECLARE_GETTER(IndexBinary, int, is_trained)

/// Getter for ntotal
FAISS_DECLARE_GETTER(IndexBinary, idx_t, ntotal)

/// Getter for metric_type
FAISS_DECLARE_GETTER(IndexBinary, FaissMetricType, metric_type)

/** Perform training on a representative set of vectors.
 *
 * @param n      nb of training vectors
 * @param x      training vecors, size n * d / 8
 */
int faiss_IndexBinary_train(FaissIndexBinary* index, idx_t n, const uint8_t *x);

/** Add n vectors of dimension d to the index.
 *
 * Vectors are implicitly assigned labels ntotal .. ntotal + n - 1
 * @param x      input matrix, size n * d / 8
 */
int faiss_IndexBinary_add(FaissIndexBinary* index, idx_t n, const uint8_t *x);

/** Same as add, but stores xids instead of sequential ids.
 *
 * The default implementation fails with an assertion, as it is
 * not supported by all indexes.
 *
 * @param xids if non-null, ids to store for the vectors (size n)
 */
int faiss_IndexBinary_add_with_ids(FaissIndexBinary* index, idx_t n, const uint8_t *x, const long *xids);

/** Query n vectors of dimension d to the index.
 *
 * return at most k vectors. If there are not enough results for a
 * query, the result array is padded with -1s.
 *
 * @param x           input vectors to search, size n * d / 8
 * @param labels      output labels of the NNs, size n*k
 * @param distances   output pairwise distances, size n*k
 */
int faiss_IndexBinary_search(const FaissIndexBinary* index, idx_t n, const uint8_t *x,
                             idx_t k, int32_t *distances, idx_t *labels);

/** Query n vectors of dimension d to the index.
 *
 * return all vectors with distance < radius. Note that many
 * indexes do not implement the range_search (only the k-NN search
 * is mandatory).
 *
 * @param x           input vectors to search, size n * d / 8
 * @param radius      search radius
 * @param result      result table
 */
int faiss_IndexBinary_range_search(const FaissIndexBinary* index, idx_t n, const uint8_t *x,
                                   int radius, FaissRangeSearchResult *result);

/** Return the indexes of the k vectors closest to the query x.
 *
 * This function is identical to search but only returns labels of neighbors.
 * @param x           input vectors to search, size n * d / 8
 * @param labels      output labels of the NNs, size n*k
 * @param k           the k vectors to retrieve
 */
int faiss_IndexBinary_assign(FaissIndexBinary* index, idx_t n, const uint8_t *x, idx_t *labels, idx_t k);

/// Removes all elements from the database.
int faiss_IndexBinary_reset(FaissIndexBinary* index);

/** Removes IDs from the index. Not supported by all indexes.
 * @param index       opaque pointer to index object
 * @param sel         ID selector of the vectors to remove
 * @param nremove     output for the number of IDs removed
 */
int faiss_IndexBinary_remove_ids(FaissIndexBinary* index, const FaissIDSelector* sel, long* n_removed);

/** Reconstruct a stored vector.
 *
 * This function may not be defined for some indexes.
 * @param key         id of the vector to reconstruct
 * @param recons      reconstucted vector (size d / 8)
 */
int faiss_IndexBinary_reconstruct(const FaissIndexBinary* index, idx_t key, uint8_t *recons);


/** Reconstruct vectors i0 to i0 + ni - 1.
 *
 * This function may not be defined for some indexes.
 * @param recons      reconstucted vectors (size ni * d / 8)
 */
int faiss_IndexBinary_reconstruct_n(const FaissIndexBinary* index, idx_t i0, idx_t ni, uint8_t *recons);

/** Similar to search, but also reconstructs the stored vectors (or an
 * approximation in the case of lossy coding) for the search results.
 *
 * If there are not enough results for a query, the resulting array
 * is padded with -1s.
 *
 * @param recons      reconstructed vectors size (n, k, d)
 **/
int faiss_IndexBinary_search_and_reconstruct(const FaissIndexBinary* index, idx_t n, const uint8_t *x, idx_t k,
                                             int32_t *distances, idx_t *labels, uint8_t *recons);

/** Display the actual class name and some more info. */
void faiss_Index_binary_display(const FaissIndex* index);

#ifdef __cplusplus
}
#endif

#endif  // FAISS_INDEX_BINARY_C_H
