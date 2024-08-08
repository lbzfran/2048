
CC=gcc
CFLAGS=-Wall

install:
	$(CC) $(CFLAGS) ./src/board.c -o board

clean:
	rm -f ./board
