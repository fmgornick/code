CXX=g++
CXXFLAGS = -std=c++11 -g
ROOT_DIR := $(shell git rev-parse --show-toplevel)
-include $(ROOT_DIR)/config/settings
-include $(DEP_DIR)/env

INCLUDE_DIR = $(ROOT_DIR)/project/build/install/include
LIB_DIR = $(ROOT_DIR)/project/build/install/lib

INCLUDES = -I$(INCLUDE_DIR) -I$(DEP_DIR)/include $(OPENCV_INCLUDES)
LIBS = -L$(LIB_DIR) -L$(DEP_DIR)/lib -lCppWebServer -lwebsockets -lssl -lcrypto -lz -lpthread -lsimulation -limage $(OPENCV_LIBS) -lfftw3 

all: web_app

web_app: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) main.cc -o $@ $(LIBS)

run:
	touch data/log/log.csv && rm data/log/log.csv && ./web_app 8081 $(ROOT_DIR)/project/simulation/web

clean:
	rm -f web_app
