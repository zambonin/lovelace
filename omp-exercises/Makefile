CFLAGS = -Wall -Wextra -O3 -march=native -fopenmp

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

test:

clean:
	rm $(basename $(wildcard *.c))
