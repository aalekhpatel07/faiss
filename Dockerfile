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

ENV BLASLDFLAGS=/usr/lib/libopenblas.so.0

RUN ./configure && \
    make -j $(nproc) && \
    make test && \
    make install

RUN make -C gpu -j $(nproc) && \
    make -C gpu/test

RUN make -C python gpu && \
    make -C python build && \
    make -C python install