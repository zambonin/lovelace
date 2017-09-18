CC=g++
OUT=generator

all: generator

generator: sparse_matrix_generator.cpp
	$(CC) -o $(OUT) sparse_matrix_generator.cpp -O2 -std=c++11

clean:
	rm $(OUT)
