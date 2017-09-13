CC=clang
CFLAGS = -Wall -Wextra -O3
OUTPUT=apsp

all:
	@$(CC) $(CFLAGS) $(wildcard *.c) -o $(OUTPUT)

debug: CFLAGS += -g
debug: all

clean:
	@rm $(OUTPUT)
