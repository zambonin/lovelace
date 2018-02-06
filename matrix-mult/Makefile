CFLAGS = -Wall -Wextra -O3 -DSTEP=16
CXXFLAGS = -Wall -Wextra -Ofast -std=c++11 -fopenmp

all: $(basename $(wildcard *.c*))

debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: all

test: $(addsuffix .test, $(basename $(wildcard tests/*.in*)))
%.test: %.in1 %.in2 %.out /usr/bin/cmp all
	./smm $< $(word 2, $?) | cmp -s $(word 3, $?) -

clean:
	rm $(basename $(wildcard *.c*))
