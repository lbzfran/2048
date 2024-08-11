
SH=sh -c
CC=gcc -g
CFLAGS=-Wall -std=c99
INC=-I include/
LIB=-L lib/

ifeq ($(OS),Windows_NT)
	CFLAGS+= -D WIN32
	LINK=-lraylib -lopengl32 -lgdi32 -lwinmm
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CFLAGS+= -D LINUX
		LINK=-lraylib -lm
	endif
	ifeq ($(UNAME_S),Darwin)
		CFLAGS+= -D OSX
		echo "OSX detected, compilation not supported"
		exit 1
	endif
endif

board:
	$(SH) "$(CC) $(CFLAGS) ./src/board.c -o board"

screen:
	$(SH) "$(CC) $(CFLAGS) ./src/board.c ./src/screen.c -o screen $(INC) $(LIB) $(LINK)"

clean:
	rm -f ./board ./screen
