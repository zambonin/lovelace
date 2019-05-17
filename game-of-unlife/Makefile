CFLAGS = -Wall -Wextra -O3 -DGSTEP=10 -fopenmp

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.out /usr/bin/cmp all
	./gou $< | cmp -s $(word 2, $?) -

clean:
	rm $(basename $(wildcard *.c))
