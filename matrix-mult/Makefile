CFLAGS = -Wall -Wextra -O3 -DSTEP=16

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.c))
