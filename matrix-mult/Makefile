CC = clang
CFLAGS = -Wall -Wextra -Ofast

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.c))
