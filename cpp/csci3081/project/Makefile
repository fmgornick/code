CXX=g++
ROOT_DIR := $(shell git rev-parse --show-toplevel)
-include $(ROOT_DIR)/config/settings
-include $(DEP_DIR)/env
CXXFLAGS = -std=c++11 -g -Wl,-rpath,$(DEP_DIR)/lib

INCLUDE_DIR = $(ROOT_DIR)/project/build/install/include
LIB_DIR = $(ROOT_DIR)/project/build/install/lib

INCLUDES = -I$(INCLUDE_DIR) -I$(DEP_DIR)/include `pkg-config --cflags opencv`
LIBS = -L$(LIB_DIR) -L$(DEP_DIR)/lib -lgtest_main -lgtest -lgmock -lCppWebServer -lwebsockets -lssl -lcrypto -lz -lpthread 
LIBS += -lsimulation -limage `pkg-config --libs opencv` -lfftw3

BUILD_DIR = build
BINARIES = build/install/bin
APP_DIR = apps

SIMULATION_DIR = simulation
IMAGE_DIR = image
TEST_DIR = tests

SIMULATION_MAIN = $(SIMULATION_DIR)/main.cc
IMAGE_MAIN = $(IMAGE_DIR)/main.cc
TESTFILES = $(wildcard $(TEST_DIR)/src/*.cc)
TESTOBJFILES = $(TESTFILES:$(TEST_DIR)/src/%.cc=$(BUILD_DIR)/%.o)

WEB_APP = $(BINARIES)/web-app
IMAGE_APP = $(BINARIES)/image-app
TEST_APP = $(BINARIES)/test-app

all: $(WEB_APP) $(IMAGE_APP) $(TEST_APP)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_APP): $(TESTOBJFILES) $(WEB_APP) $(IMAGE_APP)
	$(CXX) $(CXXFLAGS) $(TESTOBJFILES) -o $@ $(LIBS)

# Object File Targets:
$(BUILD_DIR)/%.o: $(TEST_DIR)/src/%.cc $(WEB_APP) $(IMAGE_APP)
	$(call make-depend-cxx,$<,$@,$(subst .o,.d,$@))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(WEB_APP): $(SIMULATION_MAIN) $(SIMULATION_DIR)/web-app
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@ $(LIBS)

$(IMAGE_APP): $(IMAGE_MAIN) $(IMAGE_DIR)/image-processor-app
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@ $(LIBS)

$(SIMULATION_DIR)/web-app: 
	cd $(SIMULATION_DIR) && $(MAKE) -j && cd .

$(IMAGE_DIR)/image-processor-app:
	cd $(IMAGE_DIR) && $(MAKE) -j && cd .

# Generate dependencies
make-depend-cxx=$(CXX) -MM -MF $3 -MP -MT $2 $(CXXFLAGS) $(INCLUDES) $1
-include $(OBJFILES:.o=.d)

i?=input
f?=filter
o?=output
img:
	./$(IMAGE_APP) $(i) $(f) $(o)

run:
	touch data/log/log.csv && rm data/log/log.csv && ./$(WEB_APP) 8081 $(SIMULATION_DIR)/web

test: 
	./$(BINARIES)/test-app

clean:
	rm -f $(WEB_APP) $(IMAGE_APP) $(TEST_APP) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d

clean_all: 
	rm -f $(WEB_APP) $(IMAGE_APP) $(TEST_APP) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d  \
	$(SIMULATION_DIR)/src/objects/*.o $(SIMULATION_DIR)/src/objects/*.d $(SIMULATION_DIR)/web-app \
	$(IMAGE_DIR)/src/objects/*.o $(IMAGE_DIR)/src/objects/*.d $(IMAGE_DIR)/image-processor-app \
	$(APP_DIR)/web_app/web_app $(APP_DIR)/image_processor_app/image_processor_app \
	$(TEST_DIR)/src/objects/*.o $(TEST_DIR)/test-app
