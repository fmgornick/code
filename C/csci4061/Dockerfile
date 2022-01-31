FROM ubuntu:18.04 as env

RUN groupdel dialout

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  build-essential \
  gdb \
  libssl-dev \
  zlib1g-dev \
  dos2unix \
  doxygen \
  graphviz \
  libc6-dbg \
  valgrind \
  git \
  libomp-dev \
  cmake \
  wget

ARG USER_ID
ARG GROUP_ID
ARG DEP_DIR
ARG SRC_DIR

RUN addgroup --gid $GROUP_ID user
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

RUN mkdir -p /home/user
WORKDIR /home/user/repo

USER user
