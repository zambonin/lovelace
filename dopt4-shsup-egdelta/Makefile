.PHONY = all clean test doc bin

all : bin doc

bin : shsup ingen

doc : shortest_superstring.pdf

clean:
	rm -rf shsup ingen shortest_superstring.pdf

test: bin input-example.txt input-eval-2-to-3-min.txt input-draw-3-to-5-min.txt
	cat input-example.txt
	./shsup < input-example.txt

shsup: shortest_superstring.cc
	g++ -std=c++11 -Wall -Ofast shortest_superstring.cc -o shsup -g -fopenmp

ingen: input-generator.cc
	g++ -std=c++11 -Wall -Ofast input-generator.cc -o ingen -pg -fopenmp

shortest_superstring.pdf: shortest_superstring.tex
	latexmk -pdf shortest_superstring.tex
	latexmk -c shortest_superstring.tex

