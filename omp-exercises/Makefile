CFLAGS = -Wall -Wextra -march=native -O3 -lm -fopenmp

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

clean:
	@rm $(basename $(wildcard *.c))
