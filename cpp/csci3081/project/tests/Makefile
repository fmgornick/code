CXX=g++
CXXFLAGS = -std=c++11 -g

ROOT_DIR := $(shell git rev-parse --show-toplevel)
-include $(ROOT_DIR)/config/settings
-include $(DEP_DIR)/env

INCLUDE_DIR = $(ROOT_DIR)/project/build/install/include
LIB_DIR = $(ROOT_DIR)/project/build/install/lib

INCLUDES = -I$(INCLUDE_DIR) -I$(DEP_DIR)/include `pkg-config --cflags opencv`
LIBS = -L$(LIB_DIR) -L$(DEP_DIR)/lib -lgtest_main -lgtest -lgmock -lCppWebServer -lwebsockets -lssl -lcrypto -lz -lpthread -lsimulation -limage `pkg-config --libs opencv` -lfftw3

SRC_PATH = src
OBJ_PATH = src/objects
TESTFILES = $(wildcard $(SRC_PATH)/*.cc)
TESTOBJFILES = $(TESTFILES:$(SRC_PATH)/%.cc=$(OBJ_PATH)/%.o)

all: test-app

test-app: $(TESTOBJFILES)
	$(CXX) $(CXXFLAGS) $(TESTOBJFILES) -o $@ $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test: 
	./test-app

clean:
	rm -f test-app src/objects/*.o
