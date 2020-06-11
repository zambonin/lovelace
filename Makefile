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

.NOTPARALLEL:
test: all $(patsubst %.test,%.stdout,$(shell find . -name \*.test))
%.stdout: %.test /usr/bin/python /usr/bin/git
	./$< > $@ || (touch --date=@0 $@; false)
	git diff --exit-code $@ || (touch --date=@0 $@; false)

clean:
	$(RM) $(OBJ_FILES)
