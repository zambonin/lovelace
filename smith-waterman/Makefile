CC = clang
CFLAGS = -Wall -Wextra -O3

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

test: all
	@$(foreach t,1 2,\
		./sw $(wildcard tests/*$(t).in) | cmp -s tests/$(t).out -;)

clean:
	rm $(basename $(wildcard *.c))
