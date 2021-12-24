#ifndef __MAIN__
#define __MAIN__
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define EASY_MODE 1
#define HARD_MODE 2
#define GAME_IN_PLAY 2
#define PLAYER 0
#define COMPUTER 1
#define GAMEON 1
#define GAMEOVER 0
#define DRAW -1
void initBoard(void);
void printBoard(void);
void gameMove(void);
void getPlayerMove(int8_t*);
int8_t checkForWin(void);
int8_t getComputerMove(void);
#endif