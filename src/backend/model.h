#define STAT_CONT 0
#define STAT_LOSE 1
#define STAT_WIN 2

int mines;
char board[81];
char check[81];
char mark[81];
void init(void);
int check_board(int y, int x);
void mark_board(int y, int x);
