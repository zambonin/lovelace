CXX = clang++
CXXFLAGS = -Wall -Wextra -Ofast -std=c++11
SHELL = /bin/bash

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.cpp))

test: /usr/bin/cmp all
	cmp -s <(./ss 10 53 32 10) <(echo "Number of subsets = 3")
	cmp -s <(./ss 30 100 146 20) <(echo "Number of subsets = 1343")
	cmp -s <(./ss 32 1000 2000 1) <(echo "Number of subsets = 870")
	cmp -s <(./ss 300 138000 58820 1) <(echo "Number of subsets = 1233")
