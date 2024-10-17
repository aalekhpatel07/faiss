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
        idx_t d,
        FaissMetricType metric) {
    try {
        IndexBinaryFlat* index =
                new IndexBinaryFlat(d, static_cast<faiss::MetricType>(metric));
        *p_index = reinterpret_cast<FaissIndexBinaryFlat*>(index);
        return 0;
    }
    CATCH_AND_HANDLE
}

void faiss_IndexBinaryFlat_xb(FaissIndexBinaryFlat* index, uint8_t** p_xb, size_t* p_size) {
    IndexBinaryFlat* indexf = reinterpret_cast<IndexBinaryFlat*>(index);
    *p_xb = indexf->get_xb();
    if (p_size) {
        *p_size = indexf->codes.size() / sizeof(uint8_t);
    }
}

int faiss_IndexBinaryFlat_compute_distance_subset(
        FaissBinaryIndex* index,
        idx_t n,
        const uint8_t* x,
        idx_t k,
        uint8_t* distances,
        const idx_t* labels) {
    try {
        reinterpret_cast<IndexBinaryFlat*>(index)->compute_distance_subset(
                n, x, k, distances, labels);
        return 0;
    }
    CATCH_AND_HANDLE
}
