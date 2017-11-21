CXXFLAGS = -Wall -Wextra -Ofast -fsigned-zeros -fopenmp -std=c++11

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.ppm /usr/bin/cmp all
	@./rt $< | cmp -s $(word 2, $?) -

clean:
	@rm $(basename $(wildcard *.cpp))
