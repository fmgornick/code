FROM ubuntu:18.04 as builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  build-essential \
  libssl-dev \
  zlib1g-dev \
  doxygen \
  graphviz \
  libc6-dbg \
  git \
  libopencv-dev \
  libomp-dev \
  cmake \
  wget


ENV DEP_DIR=/project/grades/Fall-2021/csci3081/dependencies
ENV SRC_DIR=/env

RUN mkdir -p ${SRC_DIR}
RUN mkdir -p ${DEP_DIR}
WORKDIR ${SRC_DIR}
RUN mkdir imageio
WORKDIR ${SRC_DIR}/imageio
RUN wget https://github.com/fiveman1/imageio/raw/master/imageio.tar.gz
RUN tar xzvf imageio.tar.gz
RUN cp -R include ${DEP_DIR}
RUN mkdir ${DEP_DIR}/lib
RUN mv lib/libimageio-docker.so lib/libimageio.so
RUN cp lib/libimageio.so ${DEP_DIR}/lib

WORKDIR ${SRC_DIR}/fftw
RUN wget https://www.fftw.org/fftw-3.3.10.tar.gz
RUN tar -zxvf fftw-3.3.10.tar.gz
WORKDIR ${SRC_DIR}/fftw/fftw-3.3.10
RUN ./configure && make && make install

WORKDIR ${SRC_DIR}
RUN git clone https://github.com/dtorban/CppWebServer.git CppWebServer
RUN mkdir -p ${SRC_DIR}/CppWebServer/build
RUN git clone https://github.com/google/googletest.git gtest
RUN mkdir -p ${SRC_DIR}/gtest/build
WORKDIR ${SRC_DIR}/CppWebServer/build
RUN cmake -DCMAKE_INSTALL_PREFIX=${DEP_DIR} ..
RUN make install
WORKDIR ${SRC_DIR}/gtest/build
RUN cmake -DCMAKE_INSTALL_PREFIX=${DEP_DIR} ..
RUN make install 

RUN echo OPENCV_INCLUDES=`pkg-config --cflags opencv` >> ${DEP_DIR}/env
RUN echo OPENCV_LIBS=`pkg-config --libs opencv` >> ${DEP_DIR}/env

RUN find ${DEP_DIR} -type d -exec chmod 775 {} \;
RUN find ${DEP_DIR} -type f -exec chmod 664 {} \;

# build and run simulation 
RUN mkdir -p /home/user/repo
COPY . /home/user/repo/project
WORKDIR /home/user/repo

RUN git init .
RUN mkdir -p config
RUN echo DEP_DIR=${DEP_DIR} > config/settings

# build the project
WORKDIR /home/user/repo/project
RUN make

# image for the project
FROM ubuntu:18.04 as sim

# uncomment the following commands if you are using opencv
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  libopencv-dev

RUN mkdir -p /sim/bin
RUN mkdir -p /sim/lib

ENV DEP_DIR=/project/grades/Fall-2021/csci3081/dependencies
ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:/sim/lib

COPY --from=builder /usr/lib/x86_64-linux-gnu/libssl.so.1.1 /usr/lib/x86_64-linux-gnu/libssl.so.1.1
COPY --from=builder /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1 /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1
COPY --from=builder ${DEP_DIR}/lib/libimageio.so /sim/lib/
COPY --from=builder /home/user/repo/project/build/install/lib /sim/lib
COPY --from=builder /home/user/repo/project/simulation/web /sim/web
COPY --from=builder /home/user/repo/project/data /sim/data
# uncomment if you have docs
COPY --from=builder /home/user/repo/project/docs/html /sim/web/docs
COPY --from=builder /home/user/repo/project/build/install/bin/web-app /sim/bin
COPY --from=builder /home/user/repo/project/build/install/bin/test-app /sim/bin


EXPOSE 8081
WORKDIR /sim
CMD while true; do /sim/bin/web-app 8081 /sim/web/ ; done

