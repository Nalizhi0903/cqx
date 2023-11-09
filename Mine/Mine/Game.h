#ifndef _GAME_H_
#define _GAME_H_

#include "utili.h"

#define COL 9
#define ROW 9
#define ROWS ROW+2
#define COLS COL+2

//定义游戏等级
#define EASY_MINE_COUNT 15

void InitBoard(char board[ROWS][COLS], int col, char set);
void DisplayBoard(char board[ROWS][COLS], int row, int col);
void SetMine(char mine[ROWS][COLS], int row, int col);
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
int GetMineCount(char mine[ROWS][COLS], int row, int col);
void StartGame();

#endif 