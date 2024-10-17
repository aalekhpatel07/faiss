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

/** Opaque type for IndexFlat */
FAISS_DECLARE_CLASS_INHERITED(IndexBinaryFlat, IndexBinary)

int faiss_IndexBinaryFlat_new(FaissIndexBinaryFlat** p_index);

int faiss_IndexBinaryFlat_new_with(
        FaissIndexBinaryFlat** p_index,
        idx_t d);

/** attempt a dynamic cast to a flat index, thus checking
 * check whether the underlying index type is `IndexFlat`.
 *
 * @param index opaque pointer to index object
 * @return the same pointer if the index is a flat index, NULL otherwise
 */
FAISS_DECLARE_INDEX_DOWNCAST_BINARY(IndexBinaryFlat)

FAISS_DECLARE_DESTRUCTOR(IndexBinaryFlat)

#ifdef __cplusplus
}
#endif

#endif
