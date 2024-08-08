
#include <stdio.h>
#include <stdlib.h>
#include "board.h"


#define TILE_SIZE 4

static int current_board[TILE_SIZE][TILE_SIZE] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {4,0,0,0}
};
static int current_board_capacity = 1;


void add_tile(int x, int y, int value) {
    // add a tile to the board at position x, y with value.
    current_board[x][y] = value;
    current_board_capacity++;
}

int check_row(int x, int x_direction) {
    // check if a shift is possible in the given direction.
    // 0 if no shift
    // 1 if left or right is still possible
    if (x_direction == 1) {
        // right shift
        for (int i = 0; i < TILE_SIZE-1; i++) {
            if (current_board[x][i] != 0 && current_board[x][i+1] == 0) {
                return 1;
            }
        }
    } else if (x_direction == -1) {
        // left shift
        for (int i = TILE_SIZE-1; i > 0; i--) {
            if (current_board[x][i] != 0 && current_board[x][i-1] == 0) {
                return 1;
            }
        }
    }
    return 0;
}



int check_col(int y, int y_direction) {
    // check if a shift is possible in the given direction.
    // 0 if no shift
    // 1 if up or down is still possible
    if (y_direction == 1) {
        // down shift
        for (int i = 0; i < TILE_SIZE-1; i++) {
            if (current_board[i][y] != 0 && current_board[i+1][y] == 0) {
                return 1;
            }
        }
    } else if (y_direction == -1) {
        // up shift
        for (int i = TILE_SIZE-1; i > 0; i--) {
            if (current_board[i][y] != 0 && current_board[i-1][y] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void shift_row(int x, int x_direction) {
    if (x_direction == 1) {
        // right shift
        for (int i = 0; i < TILE_SIZE-1; i++) {
            if (current_board[x][i] != 0 && current_board[x][i+1] == 0) {
                current_board[x][i + x_direction] = current_board[x][i];
                current_board[x][i] = 0;
            }
        }
    } else {
        // left shift
        for (int i = TILE_SIZE-1; i > 0; i--) {
            if (current_board[x][i] != 0 && current_board[x][i-1] == 0) {
                current_board[x][i + x_direction] = current_board[x][i];
                current_board[x][i] = 0;
            }
        }
    }
}

void shift_col(int y, int y_direction) {
    if (y_direction == 1) {
        // down shift
        for (int i = 0; i < TILE_SIZE-1; i++) {
            if (current_board[i][y] != 0 && current_board[i+1][y] == 0) {
                current_board[i + y_direction][y] = current_board[i][y];
                current_board[i][y] = 0;

            }
        }
    } else {
        // up shift
        for (int i = TILE_SIZE-1; i > 0; i--) {
            if (current_board[i][y] != 0 && current_board[i-1][y] == 0) {
                current_board[i + y_direction][y] = current_board[i][y];
                current_board[i][y] = 0;
            }
        }
    }
}

char *render_tile(int x, int y) {
    // given some coordinate in board, return its string representation.
    static char tile[4];
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
    //char *board = malloc(board_size);

    for (int i = 0; i < num_tiles; i++) {
        printf("|");
        for (int j = 0; j < num_tiles; j++) {
            printf("%s|",render_tile(i, j));
        }
        printf("\n");
    }

    /*
    |0000|0001|0002|0003|
    |0000|0001|0002|0003|
    |0000|0001|0002|0003|
    |0000|0001|0002|0003|
    */
}


int main(int argc, char* argv[]) {

    int game_running = 1;

    //system("clear");
    printf("\x1B[2J");
    while (game_running) {
        render_board(TILE_SIZE);


        int x;
        int y;
        do {
            x = rand() % 4;
            y = rand() % 4;
        } while (current_board[x][y] != 0 && current_board_capacity != TILE_SIZE * TILE_SIZE);
        add_tile(x, y, 2);


        // get user input
        char input;
        input = getchar();
        while (getchar() != '\n');

        if (input == 'd') {
            for (int i = 0; i < TILE_SIZE; i++) {
                while (check_row(i,1)) {
                    shift_row(i,1);
                }
            }
        }
        else if (input == 'a') {
            for (int i = 0; i < TILE_SIZE; i++) {
                while (check_row(i,-1)) {
                    shift_row(i,-1);
                }
            }
        }
        else if (input == 's') {
            for (int i = 0; i < TILE_SIZE; i++) {
                while (check_col(i,1)) {
                    shift_col(i,1);
                }
            }
        }
        else if (input == 'w') {
            for (int i = 0; i < TILE_SIZE; i++) {
                while (check_col(i,-1)) {
                    shift_col(i,-1);
                }
            }
        }
        else if (input == 'q') {
            game_running = 0;
        }

        if (current_board_capacity == TILE_SIZE * TILE_SIZE) {
            game_running = 0;
        }
        //system("clear");
        printf("\x1B[2J");
    }
    printf("game has ended.\n");
    return 0;
}
