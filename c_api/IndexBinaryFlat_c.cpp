/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD+Patents license found in the
 * LICENSE file in the root directory of this source tree.
 */

// -*- c++ -*-

#include "IndexBinaryFlat_c.h"
#include "IndexBinaryFlat.h"
#include "macros_impl.h"

extern "C" {

using faiss::IndexBinaryFlat;

DEFINE_DESTRUCTOR(IndexBinaryFlat)
DEFINE_INDEX_DOWNCAST(IndexBinaryFlat)

DEFINE_GETTER(IndexBinaryFlat, int, use_heap)
DEFINE_GETTER(IndexBinaryFlat, size_t, query_batch_size)

int faiss_IndexBinaryFlat_new(FaissIndexBinaryFlat** p_index, idx_t d) {
    try {
        *p_index = reinterpret_cast<FaissIndexBinaryFlat*>(new IndexBinaryFlat(d));
    } CATCH_AND_HANDLE
}

void faiss_IndexBinaryFlat_xb(FaissIndexBinaryFlat* index, uint8_t** p_xb, size_t* p_size) {
    auto& i = *reinterpret_cast<IndexBinaryFlat*>(index);
    if (p_xb) {
        *p_xb = i.xb.data();
    }
    if (p_size) {
        *p_size = i.xb.size();
    }
}

}
