OUT=gou

all: gou

gou: game_of_unlife.c
	$(CC) -o $(OUT) game_of_unlife.c -O1

debug: game_of_unlife.c
	$(CC) -o $(OUT).debug game_of_unlife.c -DDEBUG -O0

clean:
	rm $(OUT) $(OUT).debug
