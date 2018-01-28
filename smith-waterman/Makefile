CC = clang
CXX = clang++
CFLAGS = -Wall -Wextra -Ofast
CXXFLAGS = -Wall -Wextra -Ofast -std=c++11

all: $(basename $(wildcard *.c*))

debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: all

test: all
	@$(foreach p,""  +,$(foreach t,1 2,\
		./sw$p $(wildcard tests/*$(t).in) | cmp -s tests/$(t).out -;))

clean:
	rm $(basename $(wildcard *.c*))
