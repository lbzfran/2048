//#include <windows.h>
#include <stdio.h>
#include "board.h"
#include "../include/raylib.h"

#define WIDTH 860
#define HEIGHT 640

void init() {

}

void update() {

    if (IsKeyPressed(KEY_A)) {
        printf("A key is pressed\n");
    }
    else if (IsKeyPressed(KEY_D)) {
        printf("D key is pressed\n");
    }
    else if (IsKeyPressed(KEY_W)) {
        printf("W key is pressed\n");
    }
    else if (IsKeyPressed(KEY_S)) {
        printf("S key is pressed\n");
    }

}

void draw() {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleV((Vector2){100, 100}, (Vector2){100, 100}, RED);
    EndDrawing();
}

//int main(int argc, char* argv[]) {
//
//    int x;
//    int y;
//    int board_moved_lastturn = 1;
//    int game_running = 1;
//
//    //system("clear");
//    printf("\x1B[2J");
//    while (game_running) {
//
//        if (board_moved_lastturn) {
//            board_moved_lastturn = 0;
//            do {
//                x = rand() % 4;
//                y = rand() % 4;
//            } while (current_board[x][y] != 0 && !board_full());
//            // FIXME: give ability to adapt number based on highest number on board.
//            add_tile(x, y, 2);
//            if (DEBUG_PRINT) printf("tile added at %d, %d\n", x, y);
//        }
//
//        if (board_full() && ((check_rows(1) || check_rows(-1) || check_cols(1) || check_cols(-1)))) {
//            // FIXME: add another check to see if no more moves are possible.
//            game_running = 0;
//            CLEAR;
//            break;
//        } else if (board_max() == 2048) {
//            game_running = 0;
//            CLEAR;
//            printf("You have reached 2048!\n");
//            break;
//        } else {
//            render_board(TILE_SIZE);
//        }
//
//        // get user input
//        char input;
//        input = getchar();
//        while (getchar() != '\n');
//
//        if (input == 'd') {
//            if (check_rows(1)) {
//                board_moved_lastturn = 1;
//                for (int i = 0; i < TILE_SIZE; i++) {
//                    shift_row(i,1);
//                }
//            }
//        }
//        else if (input == 'a') {
//            if (check_rows(-1)) {
//                board_moved_lastturn = 1;
//                for (int i = 0; i < TILE_SIZE; i++) {
//                    shift_row(i,-1);
//                }
//            }
//        }
//        else if (input == 's') {
//            if (check_cols(1)) {
//                board_moved_lastturn = 1;
//                for (int i = 0; i < TILE_SIZE; i++) {
//                    shift_col(i,1);
//                }
//            }
//        }
//        else if (input == 'w') {
//            if (check_cols(-1)) {
//                board_moved_lastturn = 1;
//                for (int i = 0; i < TILE_SIZE; i++) {
//                    shift_col(i,-1);
//                }
//            }
//        }
//        else if (input == 'q') {
//            game_running = 0;
//        }
//        CLEAR;
//    }
//    printf("game has ended.\n");
//    render_board(TILE_SIZE);
//    return 0;
//}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Hello, World!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        update();
        // draw();
        // render();
    }

    CloseWindow();
    return 0;
}
