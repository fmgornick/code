FROM gcc:11

RUN mkdir -p /usr/src/p1
COPY . /usr/src/p1
WORKDIR /usr/src/p1

RUN apt-get update && apt-get install -y gdb valgrind
