CXXFLAGS = -Wall -Wextra -Ofast -std=c++11 -fopenmp

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.cpp))
