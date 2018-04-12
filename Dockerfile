FROM nvidia/cuda:9.0-devel-ubuntu16.04
MAINTAINER Pierre Letessier <pletessier@ina.fr>

RUN apt-get update && apt-get install -y software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get update -y
RUN apt-get install -y gcc-6 g++-6 libopenblas-dev python3-dev python3-numpy swig git python3-pip curl wget
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6
RUN gcc --version

RUN pip3 install matplotlib

COPY . /opt/faiss

WORKDIR /opt/faiss

ENV BLASLDFLAGS /usr/lib/libopenblas.so.0

RUN mv example_makefiles/makefile.inc.Linux.cuda9.py3 ./makefile.inc

RUN make -j $(nproc) && \
    make py

RUN cd tests && \
    make test_blas -j $(nproc) && \
    make test_ivfpq_indexing -j $(nproc)

RUN cd gpu && \
    make -j $(nproc) && \
    make test/demo_ivfpq_indexing_gpu && \
    make py

ENV PYTHONPATH $PYTHONPATH:/opt/faiss

# RUN ./tests/test_blas && \
#     tests/test_ivfpq_indexing

RUN ./tests/test_blas && \
    tests/test_ivfpq_indexing && \
    gpu/test/demo_ivfpq_indexing_gpu

# RUN wget ftp://ftp.irisa.fr/local/texmex/corpus/sift.tar.gz && \
#     tar xf sift.tar.gz && \
#     mv sift sift1M

# RUN tests/demo_sift1M
