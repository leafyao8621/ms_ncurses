#include <ncurses.h>
#include "../backend/model.h"

int my, mx, starty, startx;
int x, y;

void print_board(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            mvprintw(i + starty, (j << 1) + startx, "%-2c", mark[i * 9 + j] ?  'f' : check[i * 9 + j] ? board[i * 9 + j] : '_');
        }
    }
}

void show_board(void) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            mvprintw(i + starty, (j << 1) + startx, "%-2c", board[i * 9 + j]);
        }
    }
}

int handle(int key) {
    int stat = STAT_CONT;
    switch (key) {
    case KEY_LEFT:
    case 'a':
        x -= x ? 1 : 0;
        break;
    case KEY_RIGHT:
    case 'd':
        x += x < 8 ? 1 : 0;
        break;
    case KEY_UP:
    case 'w':
        y -= y ? 1 : 0;
        break;
    case KEY_DOWN:
    case 's':
        y += y < 8 ? 1 : 0;
        break;
    case '1':
    case 'j':
        stat = check_board(y, x);
        print_board();
        break;
    case '2':
    case 'k':
        mark_board(y, x);
        print_board();
        break;
    }
    mvprintw(0, 0, "mines: %2d\n", mines);
    move(y + starty, (x << 1) + startx);
    return stat;
}
int main() {
    WINDOW* w = initscr();
    noecho();
    keypad(stdscr, TRUE);
    cbreak();
    getmaxyx(w, my, mx);
    starty = (my - 9) >> 1;
    startx = (mx - 18) >> 1;
    x = y = 0;
    init();
    print_board();
    move(starty, startx);
    int stat;
    while (!(stat = handle(getch())));
    show_board();
    clear();
    mvprintw(my >> 1, (mx - 8) >> 1, "You %4s", stat == STAT_WIN ? "won" : "lost");
    mvprintw((my >> 1) + 1, (mx - 13) >> 1, "%s", "Press any key");
    getch();
    endwin();
}
