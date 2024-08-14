#include <stdio.h>
#include <string.h>
#include "board.h"
#include "screen.h"

int main(int argc, char *argv[]) {

    if ((argc < 2) || (strcmp(argv[1], "gui")) == 0) {
        boot_gui();
    }
    else if (strcmp(argv[1], "cli") == 0) {
        boot_cli();
    }
    else {
        printf("Usage: 2048 [gui|cli]\n");
    }
    return 0;
}
