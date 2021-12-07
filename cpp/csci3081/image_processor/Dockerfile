FROM ubuntu:18.04 as env

RUN groupdel dialout
ARG DEBIAN_FRONTEND=noninteractive 

RUN apt-get update && apt-get install -y \
    wget \
    build-essential \
    gdb \
    libssl-dev \
    zlib1g-dev \
    dos2unix \
    rsync \
    doxygen \
    graphviz \
    libc6-dbg \
    valgrind \
    git \
    cmake \
    unzip \
    pkg-config \
    libopencv-dev \ 
    libfftw3-dev \
    libfftw3-doc \
    libfftw3-3 \
    libjpeg-dev \ 
    libpng-dev \ 
    libtiff-dev \ 
    libgtk2.0-dev \ 
    libatlas-base-dev \
    gfortran \
    webp \
    qt5-default \
    libvtk6-dev \
    fig2dev \
    texinfo \
    ghostscript


RUN apt-get update && apt-get install -y --no-install-recommends \
    apt-utils vim git gfortran \
    build-essential \
    ca-certificates


ARG USER_ID
ARG GROUP_ID
ARG DEP_DIR
ARG SRC_DIR

ENV DEP_DIR=/${DEP_DIR}
RUN echo ${DEP_DIR}
ENV SRC_DIR=/${SRC_DIR}
RUN echo ${SRC_DIR}


RUN addgroup --gid $GROUP_ID user
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

RUN mkdir -p ${SRC_DIR}
WORKDIR ${SRC_DIR}
RUN git clone https://github.com/dtorban/CppWebServer.git CppWebServer
RUN mkdir -p ${SRC_DIR}/CppWebServer/build
RUN git clone https://github.com/google/googletest.git gtest
RUN mkdir -p ${SRC_DIR}/gtest/build
WORKDIR ${SRC_DIR}/CppWebServer/build
RUN cmake -DCMAKE_INSTALL_PREFIX=${DEP_DIR} ..
RUN make install -j
WORKDIR ${SRC_DIR}/gtest/build
RUN cmake -DCMAKE_INSTALL_PREFIX=${DEP_DIR} ..
RUN make install -j

# Get FFTW source code from GitHub
# and compile FFTW from scratch configure in double-precision.
WORKDIR ${SRC_DIR}/fftw
RUN wget https://www.fftw.org/fftw-3.3.10.tar.gz
RUN tar -zxvf fftw-3.3.10.tar.gz
WORKDIR ${SRC_DIR}/fftw/fftw-3.3.10
RUN ./configure && make && make install

# WORKDIR ${SRC_DIR}
# RUN git clone https://github.com/opencv/opencv opencv
# RUN git clone https://github.com/opencv/opencv_contrib opencv_contrib
# RUN mkdir -p ${SRC_DIR}/opencv/build
# WORKDIR ${SRC_DIR}/opencv/build
# RUN cmake \
#     -D CMAKE_BUILD_TYPE=RELEASE \ 
#     -D CMAKE_INSTALL_PREFIX=/usr/local \ 
#     -D WITH_CUDA=OFF \ 
#     -D OPENCV_EXTRA_MODULES_PATH=${SRC_DIR}/opencv_contrib/modules \ 
#     -D OPENCV_ENABLE_NONFREE=ON \ 
#     -D BUILD_EXAMPLES=ON ..
# RUN make -j4
# RUN make install
# RUN ldconfig

RUN find ${install_dir} -type d -exec chmod 775 {} \;
RUN find ${install_dir} -type f -exec chmod 664 {} \;

RUN mkdir -p /home/user
WORKDIR /home/user/repo

USER user
