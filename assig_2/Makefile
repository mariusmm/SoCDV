
# for compilation
CXXFLAGS = -std=c++17
INCFLAGS = -I$(SYSTEMC)/include
LDFLAGS  = -L$(SYSTEMC)/lib-$(ARCH) -lsystemc -Wl,-rpath=$(SYSTEMC)/lib-$(ARCH)

# for project
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
DEPS = $(patsubst %.cpp, %.d, $(SRCS))

# for local setup
ARCH=linux64
SYSTEMC=/eda/systemc-3.0.0
LD_LIBRARY_PATH=/eda/systemc-3.0.0/lib-linux64/

# phony target name
.PHONY = all run clean help

all: run

run: 
	@vsim -do run.do

runc: 
	@vsim -c -do run.do

clean: ## clean all file except for source codes
	$(RM) -rf work *.wlf *.mti transcript 

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'
