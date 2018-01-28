CC = clang
CFLAGS = -Wall -Wextra -Ofast

all: $(basename $(wildcard *.c))

debug: CFLAGS += -g
debug: all

test: $(addsuffix .test, $(basename $(wildcard tests/*.in)))
%.test: %.in %.out /usr/bin/cmp all
	@./fw $< | cmp -s $(word 2, $?) -
	@python fw.py $< | cmp -s $(word 2, $?) -

clean:
	rm $(basename $(wildcard *.c))
