/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD+Patents license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Copyright 2004-present Facebook. All Rights Reserved.
// -*- c++ -*-

#include "Clustering_c.h"
#include "Clustering.h"
#include "Index.h"
#include <vector>
#include "macros_impl.h"

extern "C" {

using faiss::Clustering;
using faiss::ClusteringParameters;
using faiss::Index;


DEFINE_GETTER(Clustering, int, niter)
DEFINE_GETTER(Clustering, int, nredo)
DEFINE_GETTER(Clustering, int, verbose)
DEFINE_GETTER(Clustering, int, spherical)
DEFINE_GETTER(Clustering, int, update_index)
DEFINE_GETTER(Clustering, int, frozen_centroids)

DEFINE_GETTER(Clustering, int, min_points_per_centroid)
DEFINE_GETTER(Clustering, int, max_points_per_centroid)

DEFINE_GETTER(Clustering, int, seed)

/// getter for d
DEFINE_GETTER(Clustering, size_t, d)

/// getter for k
DEFINE_GETTER(Clustering, size_t, k)

/// getter for centroids (size = k * d)
void faiss_Clustering_centroids(
    FaissClustering* clustering, float** centroids, size_t* size) {
    std::vector<float>& v = reinterpret_cast<Clustering*>(clustering)->centroids;
    if (centroids) {
        *centroids = v.data();
    }
    if (size) {
        *size = v.size();
    }
}

/// getter for objective values (sum of distances reported by index)
/// over iterations
void faiss_Clustering_obj(
    FaissClustering* clustering, float** obj, size_t* size) {
    std::vector<float>& v = reinterpret_cast<Clustering*>(clustering)->obj;
    if (obj) {
        *obj = v.data();
    }
    if (size) {
        *size = v.size();
    }
}

/// the only mandatory parameters are k and d
int faiss_Clustering_new(FaissClustering** p_clustering, int d, int k) {
    try {
        Clustering* c = new Clustering(d, k);
        *p_clustering = reinterpret_cast<FaissClustering*>(c);
        return 0;
    } CATCH_AND_HANDLE
}

int faiss_Clustering_new_with_params(
    FaissClustering** p_clustering, int d, int k, const FaissClusteringParameters* cp) {
    try {
        Clustering* c = new Clustering(d, k, *reinterpret_cast<const ClusteringParameters*>(cp));
        *p_clustering = reinterpret_cast<FaissClustering*>(c);
        return 0;
    } CATCH_AND_HANDLE
}

/// Index is used during the assignment stage
int faiss_Clustering_train(
    FaissClustering* clustering, idx_t n, const float* x, FaissIndex* index) {
    try {
        reinterpret_cast<Clustering*>(clustering)->train(
            n, x, *reinterpret_cast<Index*>(index));
        return 0;
    } CATCH_AND_HANDLE
}

void faiss_Clustering_free(FaissClustering* clustering) {
    delete reinterpret_cast<Clustering*>(clustering);
}

int kmeans_clustering (size_t d, size_t n, size_t k,
                       const float *x,
                       float *centroids,
                       float *q_error) {
    try {
        float out = faiss::kmeans_clustering(d, n, k, x, centroids);
        if (q_error) {
            *q_error = out;
        }
        return 0;
    } CATCH_AND_HANDLE
}

}