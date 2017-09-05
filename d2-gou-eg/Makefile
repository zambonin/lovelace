OUT=gou

all: gou

gou: game_of_unlife.c
	$(CC) -o $(OUT) game_of_unlife.c -Ofast -DSTEP=10 -fopenmp

debug: game_of_unlife.c
	$(CC) -o $(OUT).debug game_of_unlife.c -DDEBUG -O0 -DSTEP=10 -fopenmp

clean:
	rm $(OUT) $(OUT).debug
