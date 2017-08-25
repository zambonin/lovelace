CFLAGS = -Wall -Wextra -O3 -g

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.c))
