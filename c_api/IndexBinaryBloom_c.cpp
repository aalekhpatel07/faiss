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
        auto index = new faiss::IndexBinaryBloom(d);
        *p_index = reinterpret_cast<FaissIndexBinaryBloom*>(index);
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

int faiss_IndexBinaryBloom_should_reject(
        const FaissIndexBinaryBloom* index,
        idx_t n,
        const uint8_t* x,
        int acceptance_radius,
        FaissRejectionResult* result) {
    try {
        reinterpret_cast<const faiss::IndexBinaryBloom*>(index)->should_reject(
                n,
                x,
                acceptance_radius,
                reinterpret_cast<faiss::RejectionResult*>(result));
    }
    CATCH_AND_HANDLE
}

int faiss_IndexBinaryBloom_segments(
        const FaissIndexBinaryBloom* index,
        FaissSegmentsResult* result) {
    try {
        reinterpret_cast<const faiss::IndexBinaryBloom*>(index)->segments(
                reinterpret_cast<faiss::SegmentsResult*>(result));
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
