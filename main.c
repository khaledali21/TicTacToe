#include "main.h"
uint8_t board[9];
uint8_t turn;
uint8_t gameStatus;
int main(void){
    srand(time(NULL)); //to generate different sequences
    initBoard();
    printBoard();
    while(gameStatus){
        gameMove();
    }
    return 0;
}

void initBoard(void){
    //Clear Board and Ask for whom to start
    uint8_t index = 0;
    for(index = 0; index < 9; ++index)
    {
        board[index] = '-';
    }
    uint8_t ans;
    gameStatus = GAMEON;
    printf("Do you want to play first [Y/N]? ");
    while (1)
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
    }

}
void printBoard(void){
    int index = 0;
    printf("Board: \n");
    for(index = 0; index < 9; index+=3)
    {
        printf("\n %c | %c | %c\n", board[index], board[index+1], board[index+2]);
    }
}
void gameMove(void){
    int8_t move = -1;
    if(turn == PLAYER){
    while (move < 1 || move > 9)
        {
           getPlayerMove(&move);
        }
        board[move-1] = 'O';
    }
    else if(turn == COMPUTER){
        while (move < 1 || move > 9)
        {
            move = getComputerMove();
        }
        board[move] = 'X';
    }
    printBoard();
    int8_t status = checkForWin();
    switch (status)
    {
    case PLAYER:
        printf("You Win.");
        gameStatus = GAMEOVER;
        break;
    case COMPUTER:
        printf("You Lose.");
        gameStatus = GAMEOVER;
        break;
    case DRAW:
        printf("The game is a Draw.");
        gameStatus = GAMEOVER;
        break;
    default:
        turn = !turn;
        break;
    }
}
void getPlayerMove(int8_t* playerMove){
        printf("Please Enter a move from 1 to 9: ");
        while (1)
        {
            scanf("%d", playerMove);
            fflush(stdin);
            if(*playerMove < 1 || *playerMove > 9){
                printf("Move out of range, Please Enter a move from 1 to 9: ");
            }
            else if (board[*playerMove-1] != '-')
            {
                printf("Square is not empty, Please Enter a different move from 1 to 9: ");
            }
            else{
                break;
            }         
        }
}
int8_t checkForWin(void){
    // int8_t winner = (turn == PLAYER? 'O' : 'X');
    //check for 3 in a row
    int8_t index = 0;
    for(index = 0; index < 9; index += 3){
        if(board[index] != '-' && board[index] == board[index + 1] && board[index] == board[index + 2])
        {
            return board[index] == 'O'? PLAYER : COMPUTER;
        }
    }
    //Check for 3 in a column
    for(index = 0; index < 3; index++){
        if(board[index] != '-' && board[index] == board[index + 3] && board[index] == board[index + 6])
        {
            return board[index] == 'O'? PLAYER : COMPUTER;
        }
    }
    //check for 3 in a diagonal
    if(board[4] != '-' &&
     ((board[4] == board[0] && board[4] == board[8])|| (board[4] == board[2] && board[4] == board[6]))){
        return board[4] == 'O'? PLAYER : COMPUTER;
     }
    //check for draw
    for(index = 0; index < 9; index++){
        if(board[index] == '-'){
            return 2;
        }
    }
    return DRAW;
}
int8_t getComputerMove(void){
    uint8_t availableMoves[9];
    uint8_t index = 0;
    int8_t computerMove = -1;
    uint8_t lastEmpty = 0;
    for(index = 0; index < 9; index++){
        if(board[index] == '-'){
            availableMoves[lastEmpty++] = index;
        }
    }
    //Smart Computer
    int8_t status;
    for(index = 0; index < lastEmpty; index++){
        //Computer goes for the win    
        board[availableMoves[index]] = 'X';
        status = checkForWin();
        board[availableMoves[index]] = '-';        
        if(status == COMPUTER)
        {
            return availableMoves[index];
        }      
    }
    for(index = 0; index < lastEmpty; index++){
        //computer goes for the block
        board[availableMoves[index]] = 'O';
        status = checkForWin();
        board[availableMoves[index]] = '-';        
        if(status == PLAYER)
        {
            return availableMoves[index];
        }      
    }
    //Dummy Computer
    computerMove = rand() % lastEmpty;
    computerMove = availableMoves[computerMove];
    return computerMove;
}