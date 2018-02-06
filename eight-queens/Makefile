CXX = clang++
CXXFLAGS = -Wall -Wextra -Ofast -std=c++11
SHELL = /bin/bash

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

test: /usr/bin/cmp all
	cmp -s <(./nq 8) <(echo "Solutions = 92")
	cmp -s <(./nq 4) <(echo "Solutions = 2")
	cmp -s <(./nq 3) <(echo "Solutions = 0")
	cmp -s <(./nq 12) <(echo "Solutions = 14200")

clean:
	rm $(basename $(wildcard *.cpp))
