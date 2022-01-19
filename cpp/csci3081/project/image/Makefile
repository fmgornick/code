CXX = g++
CXXFLAGS = -std=c++11 -g
ROOT_DIR := $(shell git rev-parse --show-toplevel)
-include $(ROOT_DIR)/config/settings
-include $(DEP_DIR)/env

INCLUDE_DIR = $(ROOT_DIR)/project/build/install/include
LIB_DIR = $(ROOT_DIR)/project/build/install/lib

INCLUDES = -Iinclude `pkg-config --cflags opencv`
LIBS = -lpthread `pkg-config --libs opencv` -lfftw3

SRC_PATH = src
INC_PATH = include
OBJ_PATH = src/objects

INCS = $(wildcard $(INC_PATH)/*.h)
SRCS = $(wildcard $(SRC_PATH)/*.cc)
OBJS = $(SRCS:$(SRC_PATH)/%.cc=$(OBJ_PATH)/%.o)

all: image-processor-app

image-processor-app: $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) main.cc -o $@ $(LIBS)

imagelib: $(OBJS)
	ar rcs libimage.a $(OBJS) && mv libimage.a $(LIB_DIR)/libimage.a && cp $(INCS) $(INCLUDE_DIR)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cc $(INCS)
	$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Generate dependencies
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $(INCLUDES) $1
-include $(OBJFILES:.o=.d)

clean:
	rm -f src/objects/*.o src/objects/*.d image-processor-app
