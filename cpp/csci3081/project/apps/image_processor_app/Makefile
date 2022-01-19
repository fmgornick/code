CXX=g++
CXXFLAGS = -std=c++11 -g
ROOT_DIR := $(shell git rev-parse --show-toplevel)

INCLUDE_DIR = $(ROOT_DIR)/project/build/install/include
LIB_DIR = $(ROOT_DIR)/project/build/install/lib

INCLUDES = -I$(INCLUDE_DIR) `pkg-config --cflags opencv`
LIBS = -L$(LIB_DIR) -limage `pkg-config --libs opencv` -lfftw3 

all: image_processor_app

image_processor_app: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) main.cc -o $@ $(LIBS)

clean:
	rm -f image_processor_app
