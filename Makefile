CC = clang
CXX = clang++
CFLAGS = -Wall -Wextra -Ofast -march=native -fopenmp -DGSTEP=10 -DMSTEP=16
CXXFLAGS = -Wall -Wextra -Ofast -std=c++11 -fopenmp -fsigned-zeros -I.

SRC_FILES = $(wildcard **/*.c) $(wildcard **/*.cpp)
OBJ_FILES = $(basename $(SRC_FILES))

all: $(OBJ_FILES)

debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: all

test: /usr/bin/cmp all
	$(foreach d,$(wildcard */.),$(MAKE) 'SHELL=/bin/bash' -C $d test;)

clean:
	rm -f $(OBJ_FILES)
