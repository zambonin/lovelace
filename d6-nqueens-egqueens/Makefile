CC=g++
OUT=nqueens

all: $(OUT) debug

$(OUT): nqueens.cc
	$(CC) -o $(OUT) nqueens.cc -O2 -std=c++11

debug: nqueens.cc
	$(CC) -o $(OUT).debug nqueens.cc -O2 -std=c++11 -DDEBUG=665

clean:
	rm $(OUT) $(OUT).debug
