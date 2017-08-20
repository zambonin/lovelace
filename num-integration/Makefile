CXX = clang++
CXXFLAGS = -Wall -Wextra -Ofast -std=c++11

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.cpp))
