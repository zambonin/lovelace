CXXFLAGS = -Wall -Wextra -Ofast
SHELL = /bin/bash

all: $(basename $(wildcard *.cpp))

debug: CXXFLAGS += -g
debug: all

test: /usr/bin/cmp all
	@./nq 8 | cmp -s <(echo "Solutions = 92")
	@./nq 4 | cmp -s <(echo "Solutions = 2")
	@./nq 3 | cmp -s <(echo "Solutions = 0")
	@./nq 12 | cmp -s <(echo "Solutions = 14200")

clean:
	@rm $(basename $(wildcard *.cpp))
