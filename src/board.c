#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int current_board[TILE_SIZE][TILE_SIZE] = {{0}};
int current_board_capacity = 0;

void add_tile(int x, int y, int value) {
    // add a tile to the board at position x, y with value.
    current_board[x][y] = value;
    current_board_capacity++;
}

int board_max() {
    // return the maximum value on the board.
    int max = 0;
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            if (current_board[i][j] > max) {
                max = current_board[i][j];
            }
        }
    }
    return max;
}

int board_full() {
    // check if the board is full.
    return current_board_capacity == TILE_SIZE * TILE_SIZE;
}

int check_rows(Direction direction) {
    // check if a shift is possible in the given direction for all rows.
    // 0 if no shift possible
    // 1 if left/right is possible
    // FIXME: add another check to see if no more moves are possible.
    if (direction == RIGHT) {
        // right shift
        for (int r_idx = 0; r_idx < TILE_SIZE; r_idx++) {
            for (int i = TILE_SIZE-2; i >= 0; i--) {
                if ((current_board[r_idx][i] != 0 && current_board[r_idx][i+1] == 0) ||
                        (current_board[r_idx][i] != 0 && current_board[r_idx][i+1] == current_board[r_idx][i])) {
                    return 1;
                }
            }
        }
    } else if (direction == LEFT) {
        // left shift
        for (int r_idx = 0; r_idx < TILE_SIZE; r_idx++) {
            for (int i = 1; i <= TILE_SIZE-1; i++) {
                if ((current_board[r_idx][i] != 0 && current_board[r_idx][i-1] == 0) ||
                        (current_board[r_idx][i] != 0 && current_board[r_idx][i-1] == current_board[r_idx][i])) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check_cols(Direction direction) {
    // check if a shift is possible in the given direction for all columns.
    // 0 if no shift possible
    // 1 if up/down is still possible
    // FIXME: add another check to see if no more moves are possible.
    if (direction == DOWN) {
        // down shift
        for (int r_idx = 0; r_idx < TILE_SIZE; r_idx++) {
            for (int i = TILE_SIZE-2; i >= 0; i--) {
                if ((current_board[i][r_idx] != 0 && current_board[i+1][r_idx] == 0) ||
                        (current_board[i][r_idx] != 0 && current_board[i+1][r_idx] == current_board[i][r_idx])) {
                    return 1;
                }
            }
        }
    } else if (direction == UP) {
        // up shift
        for (int r_idx = 0; r_idx < TILE_SIZE; r_idx++) {
            for (int i = 1; i <= TILE_SIZE-1; i++) {
                if ((current_board[i][r_idx] != 0 && current_board[i-1][r_idx] == 0) ||
                        (current_board[i][r_idx] != 0 && current_board[i-1][r_idx] == current_board[i][r_idx])) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void shift_row(int x, Direction direction) {
    if (direction == RIGHT) {
        // right shift
        for (int i = TILE_SIZE-2; i >= 0; i--) {
            if (current_board[x][i] != 0) {
                for (int j = i+1; j <= TILE_SIZE-1; j++) {
                    if (current_board[x][j] == 0) {
                        current_board[x][j] = current_board[x][j-1];
                        current_board[x][j-1] = 0;
                    } else if (current_board[x][j] == current_board[x][j-1]) {
                        current_board[x][j] *= 2;
                        current_board[x][j-1] = 0;
                        current_board_capacity--;
                    } else {
                        //printf("%d\n", current_board[x][j]);
                        break;
                    }
                }
            }
        }
    } else if (direction == LEFT) {
        // left shift
        for (int i = 1; i <= TILE_SIZE-1; i++) {
            if (current_board[x][i] != 0) {
                for (int j = i-1; j >= 0; j--) {
                    if (current_board[x][j] == 0) {
                        current_board[x][j] = current_board[x][j+1];
                        current_board[x][j+1] = 0;
                    } else if (current_board[x][j] == current_board[x][j+1]) {
                        current_board[x][j] *= 2;
                        current_board[x][j+1] = 0;
                        current_board_capacity--;
                    } else {
                        //printf("%d\n", current_board[x][j]);
                        break;
                    }
                }
            }
        }
    }
}


void shift_col(int y, Direction direction) {
    if (direction == DOWN) {
        // down shift
        for (int i = TILE_SIZE-2; i >= 0; i--) {
            if (current_board[i][y] != 0) {
                for (int j = i+1; j <= TILE_SIZE-1; j++) {
                    if (current_board[j][y] == 0) {
                        current_board[j][y] = current_board[j-1][y];
                        current_board[j-1][y] = 0;
                    } else if (current_board[j][y] == current_board[j-1][y]) {
                        current_board[j][y] *= 2;
                        current_board[j-1][y] = 0;
                        current_board_capacity--;
                    } else {
                        //printf("%d\n", current_board[j][y]);
                        break;
                    }
                }
            }
        }
    } else if (direction == UP) {
        // up shift
        for (int i = 1; i <= TILE_SIZE-1; i++) {
            if (current_board[i][y] != 0) {
                for (int j = i-1; j >= 0; j--) {
                    if (current_board[j][y] == 0) {
                        current_board[j][y] = current_board[j+1][y];
                        current_board[j+1][y] = 0;
                    } else if (current_board[j][y] == current_board[j+1][y]) {
                        current_board[j][y] *= 2;
                        current_board[j+1][y] = 0;
                        current_board_capacity--;
                    } else {
                        //printf("%d\n", current_board[j][y]);
                        break;
                    }
                }
            }
        }
    }
}

char *render_tile(int x, int y) {
    // given some coordinate in board, return its string representation.
    static char tile[TILE_SIZE];
    for  (int i = 0; i < 4; i++) {
        tile[i] = ' ';
    }
    int a = 3;
    if (current_board[x][y] != 0) {
        int n = current_board[x][y];
        ASSERT(n < 10000 && n % 2 == 0);
        do {
            tile[a--] = '0' + n % 10;
            n /= 10;
        } while (n > 0);
    }
    return tile;

}

void render_board(int num_tiles) {
    /*
    |0000|0001|0002|0003|
    |0100|0101|0102|0103|
    |0200|0201|0202|0203|
    |0300|0301|0302|0303|
    */
    for (int i = 0; i < num_tiles; i++) {
        printf("|");
        for (int j = 0; j < num_tiles; j++) {
            printf("%s|",render_tile(i, j));
        }
        printf("\n");
    }
}


int boot_cli() {
    // play game in CLI mode.
    int x;
    int y;
    int board_moved_lastturn = 1;
    int game_running = 1;

    //system("clear");
    printf("\x1B[2J");
    while (game_running) {

        if (board_moved_lastturn) {
            board_moved_lastturn = 0;
            do {
                x = rand() % 4;
                y = rand() % 4;
            } while (current_board[x][y] != 0 && !board_full());
            // FIXME: give ability to adapt number based on highest number on board.
            add_tile(x, y, 2);
            if (DEBUGGING) printf("tile added at %d, %d\n", x, y);
        }

        if (board_full() && ((check_rows(1) || check_rows(-1) || check_cols(1) || check_cols(-1)))) {
            // FIXME: add another check to see if no more moves are possible.
            game_running = 0;
            CLEAR;
            break;
        } else if (board_max() == 2048) {
            game_running = 0;
            CLEAR;
            printf("You have reached 2048!\n");
            break;
        } else {
            render_board(TILE_SIZE);
        }

        // get user input
        char input;
        Direction move;
        input = getchar();
        while (getchar() != '\n');


        if (input == 'd') {
            move = RIGHT;
        } else if (input == 'a') {
            move = LEFT;
        } else if (input == 's') {
            move = DOWN;
        } else if (input == 'w') {
            move = UP;
        } else if (input == 'q') {
            game_running = 0;
        } else {
            continue;
        }

        if ((move == LEFT || move == RIGHT) && check_rows(move)) {
            board_moved_lastturn = 1;
            for (int i = 0; i < TILE_SIZE; i++) {
                shift_row(i,move);
            }

        }
        else if ((move == UP || move == DOWN) && check_cols(move)) {
            board_moved_lastturn = 1;
            for (int i = 0; i < TILE_SIZE; i++) {
                shift_col(i,move);
            }
        }
        CLEAR;
    }
    printf("game has ended.\n");
    render_board(TILE_SIZE);
    return 0;
}
