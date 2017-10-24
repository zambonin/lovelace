CC=g++
OUT=subsum

all: subsum debug

subsum: subsetsum.cpp
	$(CC) -o $(OUT) subsetsum.cpp -Ofast -std=c++11

debug: subsetsum.cpp
	$(CC) -o $(OUT).debug subsetsum.cpp -Ofast -std=c++11 -DDEBUG=1

clean:
	rm $(OUT) $(OUT).debug
