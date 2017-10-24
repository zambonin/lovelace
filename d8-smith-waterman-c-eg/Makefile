CC    :=gcc
FLAGS :=-fopenmp -Wall -Ofast
OUT   :=sw

.PHONY: all clean

all:
	$(CC) SmithWaterman.c $(FLAGS) -o $(OUT)

clean:
	rm -rf $(OUT)
