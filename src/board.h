
#define ASSERT(x) if (!(x)) { printf("Assertion failed: %s\n", #x); exit(1); }
#define TILE_SIZE 4

void add_tile(int x, int y, int value);
int check_row(int x, int x_direction);
int check_col(int y, int y_direction);
void shift_row(int x, int x_direction);
void shift_col(int y, int y_direction);
char *render_tile(int x, int y);
void render_board(int num_tiles);
