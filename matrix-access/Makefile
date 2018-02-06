CC = clang
CFLAGS = -Wall -Wextra -Ofast

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

test:

clean:
	rm $(basename $(wildcard *.c))
