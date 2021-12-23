#include <stdio.h>
#include <stdint.h>
#include "main.h"
uint8_t board[9];
uint8_t turn;
uint8_t gameStatus;
void main(void){
    initBoard();
    printBoard();
    uint8_t ans;
    printf("Do you want to play first? [Y/N]");
    do
    {
        scanf("%c", &ans);
        if(ans == 'Y' || ans == 'y'){
            turn = PLAYER;
            break;
        }
        else if(ans == 'N' || ans == 'n'){
            turn = COMPUTER;
            break;
        }
        else{
            printf("Invalid answer, please answer with Y or N.");
        }
    } while (1);

    while(gameStatus){
        gameMove(turn);
    }
}

void initBoard(void){
    uint8_t index = 0;
    for(index = 0; index < 9; ++index)
    {
        board[index] = '-';
    }

}
void printBoard(void){
    int index = 0;
    for(index = 0; index < 9; index+=3)
    {
        printf("\n%c | %c | %c\n", board[index], board[index+1], board[index+2]);
    }
}