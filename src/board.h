
#ifndef BOARD_H
#define BOARD_H

#include "config.h"

extern int current_board[TILE_SIZE][TILE_SIZE];
extern int current_board_capacity;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

void add_tile(int x, int y, int value);
int board_max();
int board_full();
int check_rows(Direction);
int check_cols(Direction);
void shift_row(int x, Direction);
void shift_col(int y, Direction);
char *render_tile(int x, int y);
void render_board(int num_tiles);

#endif
