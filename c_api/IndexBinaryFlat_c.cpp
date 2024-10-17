/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Copyright 2004-present Facebook. All Rights Reserved.
// -*- c++ -*-

#include "IndexBinaryFlat_c.h"
#include <faiss/IndexBinaryFlat.h>
#include <faiss/IndexBinary.h>
#include "macros_impl.h"

extern "C" {

using faiss::IndexBinary;
using faiss::IndexBinaryFlat;

DEFINE_DESTRUCTOR(IndexBinaryFlat)
DEFINE_INDEX_DOWNCAST_BINARY(IndexBinaryFlat)

int faiss_IndexBinaryFlat_new(FaissIndexBinaryFlat** p_index) {
    try {
        *p_index = reinterpret_cast<FaissIndexBinaryFlat*>(new IndexBinaryFlat());
        return 0;
    }
    CATCH_AND_HANDLE
}

int faiss_IndexBinaryFlat_new_with(
        FaissIndexBinaryFlat** p_index,
        idx_t d) {
    try {
        IndexBinaryFlat* index =
                new IndexBinaryFlat(d);
        *p_index = reinterpret_cast<FaissIndexBinaryFlat*>(index);
        return 0;
    }
    CATCH_AND_HANDLE
}

}