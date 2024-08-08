
#ifdef _WIN32
#define CLEAR printf("\033[2J")
#endif

#ifdef linux
#define CLEAR system("clear")
#endif


#define DEBUG

#ifdef DEBUG
 #define DEBUG_PRINT 1
#else
 #define DEBUG_PRINT 0
#endif

#define ASSERT(x) if (!(x)) { printf("Assertion failed: %s\n", #x); exit(1); }

#define TILE_SIZE 4

void add_tile(int x, int y, int value);
int board_full();
int check_rows(int x_direction);
int check_cols(int y_direction);
void shift_row(int x, int x_direction);
void shift_col(int y, int y_direction);
char *render_tile(int x, int y);
void render_board(int num_tiles);
