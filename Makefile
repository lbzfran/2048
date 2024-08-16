SH=sh -c
CC=gcc -g
CFLAGS=-Wall -std=c99
INC=-I include/
LIB=-L lib/
BIN=2048

ifeq ($(OS),Windows_NT)
	CFLAGS+= -D WIN32
	LINK=-lraylib -lopengl32 -lgdi32 -lwinmm
	BIN=2048.exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CFLAGS+= -D LINUX
		LINK=-lraylib -lm
	endif
	ifeq ($(UNAME_S),Darwin)
		echo "OSX detected, compilation not supported"
		exit 1
	endif
endif

install:
	$(SH) "$(CC) $(CFLAGS) ./src/board.c ./src/screen.c ./src/main.c -o $(BIN) $(INC) $(LIB) $(LINK)"

clean:
	rm -f $(BIN)
