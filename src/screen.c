//#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
        static int last_max = 4;
        static int num = 1;
        if (board_max() > last_max) {
            num++;
            last_max = board_max();
        }
        int tile_num = pow(2, (rand() % num)+1);
        add_tile(x, y, tile_num);
        if (DEBUGGING) {
            printf("tile num %d added at %d, %d\n", tile_num, x, y);
            render_board(TILE_SIZE);
        }
    }

    if (board_full() && !((check_rows(LEFT) || check_rows(RIGHT) || check_cols(UP) || check_cols(DOWN)))) {
        game_running = 0;
    } else if (board_max() == 2048) {
        game_running = 0;
        if (DEBUGGING) printf("2048 has been reached!\n");
    }


}

void update_input() {
    Direction move;
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
        move = LEFT;
        if (DEBUGGING) printf("moving left.\n");
    } else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
        move = RIGHT;
        if (DEBUGGING) printf("moving right.\n");
    } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        move = UP;
        if (DEBUGGING) printf("moving up.\n");
    } else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        move = DOWN;
        if (DEBUGGING) printf("moving down.\n");
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
    DrawRectangleV((Vector2){WIDTH/6.0, HEIGHT/6.0}, (Vector2){450, 450}, LIGHTGRAY);
    // bg of tiles
    for (int i = 1; i <= TILE_SIZE; i++) {
        for (int j = 1; j <= TILE_SIZE; j++) {
            DrawRectangleV((Vector2){((WIDTH/1.45) - j * 110), ((HEIGHT/1.15) - i * 110)}, (Vector2){100, 100}, DARKGRAY);
        }
    }
}

void draw_tiles() {
    // set font
    GetFontDefault();
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            if (current_board[i][j] != 0) {
                //DrawRectangleV((Vector2){((j+1) * 110)+(43), ((i+1) * 110)-(10)}, (Vector2){100, 100}, LIGHTGRAY);
                Color color1, color2;
                if (current_board[i][j] == 2) {
                    color1 = RED;
                    color2 = MAROON;
                } else if (current_board[i][j] == 4) {
                    color1 = ORANGE;
                    color2 = DARKBROWN;
                } else if (current_board[i][j] == 8) {
                    color1 = YELLOW;
                    color2 = GOLD;
                } else if (current_board[i][j] == 16) {
                    color1 = GREEN;
                    color2 = LIME;
                } else if (current_board[i][j] == 32) {
                    color1 = SKYBLUE;
                    color2 = DARKBLUE;
                } else if (current_board[i][j] == 64) {
                    color1 = BLUE;
                    color2 = DARKBLUE;
                } else if (current_board[i][j] == 128) {
                    color1 = PURPLE;
                    color2 = VIOLET;
                } else if (current_board[i][j] == 256) {
                    color1 = MAGENTA;
                    color2 = VIOLET;
                } else if (current_board[i][j] == 512) {
                    color1 = PINK;
                    color2 = MAROON;
                } else {
                    color1 = GRAY;
                    color2 = BLACK;
                }
                //((WIDTH/1.45) - j * 110), ((HEIGHT/1.15) - i * 110)
                DrawRectangleV((Vector2){((j+1) * 110)+43,((i+1) * 110)+7}, (Vector2){100, 100}, color2);
                DrawRectangleV((Vector2){((j+1) * 110)+43, ((i+1) * 110)}, (Vector2){100, 100}, color1);
                DrawText(TextFormat("%d", current_board[i][j]), ((j+1) * 110)+80, ((i+1) * 110)+30, 30, BLACK);
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

void boot_gui(void) {
    InitWindow(WIDTH, HEIGHT, "2048");
    SetTargetFPS(60);

    while (!WindowShouldClose() && game_running) {
        update();
        draw();
    }
    if (DEBUGGING) printf("Game over!\n");
    CloseWindow();
}
