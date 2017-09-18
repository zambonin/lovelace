CFLAGS = -Wall -Wextra -O3 -DSTEP=16
CXXFLAGS = -O2 -std=c++11 -Wall -Wextra

all: $(basename $(wildcard *.c*))

debug: CFLAGS += -g
debug: CXXFLAGS += -g
debug: all

clean:
	rm $(basename $(wildcard *.c*))
