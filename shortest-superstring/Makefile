CXXFLAGS = -Wall -Wextra -O3 -std=c++11

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.out /usr/bin/cmp all
	@./shs $< | cmp -s $(word 2, $?) -

clean:
	rm $(basename $(wildcard *.cpp))
