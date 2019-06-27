#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "model.h"

int cnt;

void init(void) {
    mines = 10;
    cnt = 0;
    memset(board, 0, 81);
    memset(check, 0, 81);
    memset(mark, 0, 81);
    srand(time(0));
    for (int cnt = 0; cnt < 10; cnt++) {
        int ind;
        do {
            ind = rand() / ((double)RAND_MAX) * 81;
        } while(board[ind]);
        board[ind] = '*';
    }
    for (int i = 0; i < 81; i++) {
        if (!board[i]) {
            int row = i / 9;
            int col = i % 9;
            int cnt = 0;
            for (int j = ((row - 1) >= 0 ? row - 1 : 0); j < ((row + 2) < 10 ? row + 2 : 9); j++) {
                for (int k = ((col - 1) >= 0 ? col - 1 : 0); k < ((col + 2) < 10 ? col + 2 : 9); k++) {
                    if (board[j * 9 + k] == '*') cnt++;
                }
            }
            board[i] = cnt + '0';
        }
    }
}

int check_board(int y, int x) {
    static char stack[81];
    int ind = 0;
    if (board[y * 9 + x] == '*') return STAT_LOSE;
    if (cnt == 71) return STAT_WIN;
    if (mark[y * 9 + x]) return STAT_CONT;
    if (check[y * 9 + x]) return STAT_CONT;
    cnt++;
    stack[ind++] = y * 9 + x;
    check[y * 9 + x] = 1;
    while (ind) {
        int temp = stack[--ind];
        if (board[temp] == '0') {
            int row = temp / 9;
            int col = temp % 9;
            for (int j = ((row - 1) >= 0 ? row - 1 : 0); j < ((row + 2) < 10 ? row + 2 : 9); j++) {
                for (int k = ((col - 1) >= 0 ? col - 1 : 0); k < ((col + 2) < 10 ? col + 2 : 9); k++) {
                    if (!check[j * 9 + k]) {
                        check[j * 9 + k] = 1;
                        cnt++;
                        stack[ind++] = j * 9 + k;
                    }
                }
            }
        }
    }
    if (cnt == 71) return STAT_WIN;
    return STAT_CONT;
}

void mark_board(int y, int x) {
    if (!check[y * 9 + x]) {
        mines += mark[y * 9 + x] ? 1 : -1;
        mark[y * 9 + x] = !mark[y * 9 + x];
    }
}
