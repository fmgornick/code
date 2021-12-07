CXX=g++
CXXFLAGS = -std=c++11 -g -Iinclude -I/usr/local/include -L/usr/local/lib -lfftw3 -lm
ROOT_DIR := $(shell git rev-parse --show-toplevel)
-include $(ROOT_DIR)/config/settings
-include $(DEP_DIR)/env

SRCDIR=src
INCLDIR=include
LIBDIR=lib

SOURCES = $(wildcard $(SRCDIR)/*.cc)
OBJFILES = $(SOURCES:$(SRCDIR)/.cc=$(LIBDIR)/.o)

all: image_processor

# Applicaiton Targets:
image_processor: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(OBJFILES) -o $@ -lfftw3

$(LIBDIR)/%.o : $(SRCDIR)/%.cc $(INCLDIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o image_processor

