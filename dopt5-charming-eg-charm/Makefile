CFLAGS = -Wall -Wextra -Ofast
CHARMDIR = ~/charm
CHARMC = $(CHARMDIR)/bin/charmc

all: neighbor_sum charming_sum

charming_sum: pre-build
	$(CHARMC) -language charm++ -o $@ $(shell ls *.o)

pre-build:
	$(CHARMC) $(wildcard *.ci) $(wildcard *.C)

clean:
	rm $(wildcard *.def.h)
	rm $(wildcard *.decl.h)
	rm $(wildcard *.o)
	rm neighbor_sum charming_sum charmrun
