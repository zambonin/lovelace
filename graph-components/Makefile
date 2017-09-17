CXX = clang++
CXXFLAGS = -Wall -Wextra -Ofast -march=native -std=c++11

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.cpp))
