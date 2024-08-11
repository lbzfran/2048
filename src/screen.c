//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int board_moved_lastturn = 1;
int game_running = 1;

void update_board() {
    static int x, y;
    if (board_moved_lastturn) {
        board_moved_lastturn = 0;
        do {
            x = rand() % 4;
            y = rand() % 4;
        } while (current_board[x][y] != 0 && !board_full());
        // FIXME: give ability to adapt number based on highest number on board.
        add_tile(x, y, 2);
        if (DEBUGGING) {
            printf("tile added at %d, %d\n", x, y);
            render_board(TILE_SIZE);
        }
    }

    if (board_full() && ((check_rows(1) || check_rows(-1) || check_cols(1) || check_cols(-1)))) {
        // FIXME: add another check to see if no more moves are possible.
        game_running = 0;
    } else if (board_max() == 2048) {
        game_running = 0;
        if (DEBUGGING) printf("2048 has been reached!\n");
    }


}

void update_input() {
    Direction move;
    if (IsKeyPressed(KEY_A)) {
        move = LEFT;
        if (DEBUGGING) printf("Key A pressed.\n");
    } else if (IsKeyPressed(KEY_D)) {
        move = RIGHT;
        if (DEBUGGING) printf("Key D pressed.\n");
    } else if (IsKeyPressed(KEY_W)) {
        move = UP;
        if (DEBUGGING) printf("Key W pressed.\n");
    } else if (IsKeyPressed(KEY_S)) {
        move = DOWN;
        if (DEBUGGING) printf("Key S pressed.\n");
    } else if (IsKeyPressed(KEY_Q)) {
        game_running = 0;
        if (DEBUGGING) printf("Key Q pressed.\n");
    } else {
        return;
    }

    if ((move == LEFT || move == RIGHT) && check_rows(move)) {
        board_moved_lastturn = 1;
        for (int i = 0; i < TILE_SIZE; i++) {
            shift_row(i,move);
        }
    } else if ((move == UP || move == DOWN) && check_cols(move)) {
        board_moved_lastturn = 1;
        for (int i = 0; i < TILE_SIZE; i++) {
            shift_col(i,move);
        }
    }
}

void update() {
    update_board();
    update_input();
}

void draw_board() {
    // board
    DrawRectangleV((Vector2){100, 100}, (Vector2){450, 450}, BEIGE);
    // bg of tiles
    // can put in for loop maybe
    for (int i = 1; i <= TILE_SIZE; i++) {
        for (int j = 1; j <= TILE_SIZE; j++) {
            DrawRectangleV((Vector2){(j * 110), (i * 110)}, (Vector2){100, 100}, DARKGRAY);
        }
    }
}

void draw_tiles() {
    // set font
    GetFontDefault();
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            if (current_board[i][j] != 0) {
                DrawRectangleV((Vector2){((j+1) * 110), ((i+1) * 110)}, (Vector2){100, 100}, LIGHTGRAY);
                DrawText(TextFormat("%d", current_board[i][j]), ((j+1) * 110) + 45, ((i+1) * 110) + 35, 30, BLACK);
            }
        }
    }
}

void draw() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    draw_board();
    draw_tiles();

    EndDrawing();
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Hello, World!");
    SetTargetFPS(60);

    while (!WindowShouldClose() && game_running) {
        update();
        draw();
    }
    if (DEBUGGING) printf("Game over!\n");
    CloseWindow();
    return 0;
}
