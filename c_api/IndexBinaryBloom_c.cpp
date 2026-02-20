/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// -*- c++ -*-

#include "IndexBinaryBloom_c.h"
#include <faiss/IndexBinaryBloom.h>
#include "macros_impl.h"

extern "C" {

DEFINE_DESTRUCTOR(IndexBinaryBloom)

DEFINE_GETTER(IndexBinaryBloom, int, d)

int faiss_IndexBinaryBloom_new(FaissIndexBinaryBloom** p_index, idx_t d) {
    try {
        *p_index = reinterpret_cast<FaissIndexBinaryBloom*>(
                new IndexBinaryBloom(d));
        return 0;
    }
    CATCH_AND_HANDLE
}

int faiss_IndexBinaryBloom_add(
        FaissIndexBinaryBloom* index,
        idx_t n,
        const uint8_t* x) {
    try {
        reinterpret_cast<faiss::IndexBinaryBloom*>(index)->add(n, x);
    }
    CATCH_AND_HANDLE
}

int faiss_IndexBinaryBloom_reject(
        const FaissIndexBinaryBloom* index,
        idx_t n,
        const uint8_t* x,
        FaissRejectionResult* result) {
    try {
        reinterpret_cast<const faiss::IndexBinaryBloom*>(index)->reject(
                n, x, reinterpret_cast<faiss::RejectionResult*>(result));
    }
    CATCH_AND_HANDLE
}

int faiss_IndexBinaryBloom_reset(FaissIndexBinaryBloom* index) {
    try {
        reinterpret_cast<faiss::IndexBinaryBloom*>(index)->reset();
    }
    CATCH_AND_HANDLE
}
}
