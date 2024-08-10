
SH=sh -c
CC=gcc
CFLAGS=-Wall -std=c99
INC=-I include/
LIB=-L lib/
LINK=-lraylib -lopengl32 -lgdi32 -lwinmm

board:
	$(SH) "$(CC) $(CFLAGS) ./src/board.c -o board"

screen:
	 $(SH) "$(CC) $(CFLAGS) ./src/screen.c -o screen $(INC) $(LIB) $(LINK)"

clean:
	rm -f ./board
