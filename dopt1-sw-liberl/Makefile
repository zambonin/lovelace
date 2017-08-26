CFLAGS = -Wall -Wextra -O3
CXXFLAGS = -Wall -Wextra -Ofast -std=c++11

all: $(basename $(wildcard *.c*))

debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.c*))
