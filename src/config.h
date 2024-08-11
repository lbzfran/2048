#ifndef CONFIG_H
# define CONFIG_H

// game config stuff
# define TILE_SIZE 4 // determines length of rows/cols
# define WIDTH 860
# define HEIGHT 640

// context-cracking and debug tools
# define ENABLE_ASSERT
# define DEBUGGING true
//# define CLI_MODE

# ifdef _WIN32
   #include "../include/raylib.h"
#  ifdef CLI_MODE
#   define CLEAR printf("\033[2J")
#  endif
# elif __linux__
   #include <raylib.h>
#  ifdef CLI_MODE
#   define CLEAR system("clear")
#  endif
# endif

# ifdef ENABLE_ASSERT
#  define ASSERT(c) if (!(c)) { printf("[-] Assertion failed at line %d.\n", __LINE__); exit(1); }
# else
#  define ASSERT(c)
# endif

# ifndef CLI_MODE
#  define CLEAR
# endif

#endif
