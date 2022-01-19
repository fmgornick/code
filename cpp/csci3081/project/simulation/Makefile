CXX=g++
CXXFLAGS = -std=c++11 -g
ROOT_DIR := $(shell git rev-parse --show-toplevel)
-include $(ROOT_DIR)/config/settings
-include $(DEP_DIR)/env

INCLUDE_DIR = $(ROOT_DIR)/project/build/install/include
LIB_DIR = $(ROOT_DIR)/project/build/install/lib

INCLUDES = -Iinclude -I$(DEP_DIR)/include -I$(INCLUDE_DIR) `pkg-config --cflags opencv`
LIBS = -L$(LIB_DIR) -L$(DEP_DIR)/lib -lCppWebServer -lwebsockets -lssl -lcrypto -lz -lpthread -limage `pkg-config --libs opencv` -lfftw3

SRC_PATH = src
INC_PATH = include
OBJ_PATH = src/objects
DATA_PATH = data
IMAGE_DIR = $(ROOT_DIR)/project/image

INCS = $(wildcard $(INC_PATH)/*.h)
SRCS = $(wildcard $(SRC_PATH)/*.cc)
OBJS = $(SRCS:$(SRC_PATH)/%.cc=$(OBJ_PATH)/%.o)

EXEFILE = $(BUILD_DIR)/web-app

TESTFILES = $(wildcard tests/*.cc)
TESTOBJFILES = $(filter-out $(BUILD_DIR)/main.o,$(OBJFILES)) $(addprefix $(BUILD_DIR)/, $(notdir $(TESTFILES:.cc=.o)))
TESTEXEFILE = $(BUILD_DIR)/test-app

all: web-app simulationlib

# applicaiton Target:
web-app: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) main.cc -o $@ $(LIBS)

# library creation
simulationlib: $(OBJS)
	ar rcs libsimulation.a $(OBJS) && mv libsimulation.a $(LIB_DIR) && cp $(INCS) $(INCLUDE_DIR)

# object file targets:
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cc $(INCS) $(IMAGE_DIR)/image-processor-app
	$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(IMAGE_DIR)/image-processor-app: 
	cd $(IMAGE_DIR) && $(MAKE) -j && cd .

# generate dependencies
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $(INCLUDES) $1
-include $(OBJFILES:.o=.d)

run:
	touch data/log/log.csv && rm data/log/log.csv && ./web-app 8081 web

clean:
	rm -f src/objects/*.o src/objects/*.d web-app
