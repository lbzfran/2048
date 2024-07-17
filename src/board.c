
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(x) if (!(x)) { printf("Assertion failed: %s\n", #x); exit(1); }

#define TILE_SIZE 4

static int current_board[TILE_SIZE][TILE_SIZE] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {4,0,0,4}
};
static int current_board_capacity = 0;


void add_tile(int x, int y, int value) {
    // add a tile to the board at position x, y with value.
    current_board[x][y] = value;
    current_board_capacity++;
}

void shift_row(int x, int x_direction) {
    for (int i = 0; i < TILE_SIZE-1; i++) {
        if (current_board[x][i] != 0) {
            if (current_board[x][i] == current_board[x][i + x_direction]) {
                current_board[x][i + x_direction] *= 2;
                current_board[x][i] = 0;
            } else {
                current_board[x][i + x_direction] = current_board[x][i];
                current_board[x][i] = 0;
            }
        }
            /*if (current_board[x][i] == current_board[x][i + x_direction]) {
                current_board[x][i + x_direction] *= 2;
                current_board[x][i] = 0;
            }*/

    }

}


char *render_tile(int x, int y) {
    // given some coordinate in board, return its string representation.
    static char tile[4];
    for  (int i = 0; i < 4; i++) {
        tile[i] = '0';
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

    int row_size = num_tiles * 5 + 1;

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

    while (game_running) {
        render_board(TILE_SIZE);

        // get user input
        char input;
        scanf("%c", &input);
        if (input == 'r') {
            for (int i = 0; i < TILE_SIZE; i++) {
                shift_row(i,1);
            }
        }
        else if (input == 'l') {
            for (int i = 0; i < TILE_SIZE; i++) {
                shift_row(i,-1);
            }
        }
        else if (input == 'q') {
            game_running = 0;
        }
        else {
            printf("Invalid input\n");
        }
        printf("\n");
    }
    return 0;
}
