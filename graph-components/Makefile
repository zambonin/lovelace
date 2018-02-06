CXX = clang++
CXXFLAGS = -Wall -Wextra -O3 -std=c++11

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

test:

clean:
	rm $(basename $(wildcard *.cpp))
