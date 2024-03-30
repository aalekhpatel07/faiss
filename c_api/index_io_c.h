/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

//  Copyright 2004-present Facebook. All Rights Reserved
// -*- c++ -*-
// I/O code for indexes

#ifndef FAISS_INDEX_IO_C_H
#define FAISS_INDEX_IO_C_H

#include <stdio.h>
#include "IndexBinary_c.h"
#include "Index_c.h"
#include "faiss_c.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Write index to a file.
 * This is equivalent to `faiss::write_index` when a file descriptor is
 * provided.
 */
int faiss_write_index(const FaissIndex* idx, FILE* f);

/** Write index to a file.
 * This is equivalent to `faiss::write_index` when a file path is provided.
 */
int faiss_write_index_fname(const FaissIndex* idx, const char* fname);

/** Write index to a writer.
 * This is equivalent to `faiss::write_index` when an IOWriter is
 * provided.
 */
int faiss_write_index_writer(const FaissIndex* idx, IOWriter* writer);


#define FAISS_IO_FLAG_MMAP 1
#define FAISS_IO_FLAG_READ_ONLY 2

/** Read index from a file.
 * This is equivalent to `faiss:read_index` when a file descriptor is given.
 */
int faiss_read_index(FILE* f, int io_flags, FaissIndex** p_out);

/** Read index from a file.
 * This is equivalent to `faiss:read_index` when a file path is given.
 */
int faiss_read_index_fname(const char* fname, int io_flags, FaissIndex** p_out);

/** Read index from a reader.
 * This is equivalent to `faiss::read_index` when an IOReader is
 * provided.
 */
int faiss_read_index_reader(IOReader* reader, int io_flags, const FaissIndex** p_out);

/** Write index to a file.
 * This is equivalent to `faiss::write_index_binary` when a file descriptor is
 * provided.
 */
int faiss_write_index_binary(const FaissIndexBinary* idx, FILE* f);

/** Write index to a file.
 * This is equivalent to `faiss::write_index_binary` when a file path is
 * provided.
 */
int faiss_write_index_binary_fname(
        const FaissIndexBinary* idx,
        const char* fname);


/** Write index to a writer.
 * This is equivalent to `faiss::write_index_binary` when an IOWriter is
 * provided.
 */
int faiss_write_index_binary_writer(
        const FaissIndexBinary* idx,
        IOWriter* writer);

/** Read index from a file.
 * This is equivalent to `faiss:read_index_binary` when a file descriptor is
 * given.
 */
int faiss_read_index_binary(FILE* f, int io_flags, FaissIndexBinary** p_out);

/** Read index from a file.
 * This is equivalent to `faiss:read_index_binary` when a file path is given.
 */
int faiss_read_index_binary_fname(
        const char* fname,
        int io_flags,
        FaissIndexBinary** p_out);


/** Read index from a reader.
 * This is equivalent to `faiss::read_index` when an IOReader is
 * provided.
 */
int faiss_read_index_binary_reader(IOReader* reader, int io_flags, const FaissIndexBinary** p_out);

#ifdef __cplusplus
}
#endif
#endif
