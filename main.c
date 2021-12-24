#include "main.h"
uint8_t gau8_board[9];
uint8_t gu8_turn;
uint8_t gu8_gameStatus;
uint8_t gu8_mode;
int main(void){
    srand(time(NULL)); //to generate different sequences
    initBoard();
    printBoard();
    while(gu8_gameStatus){
        gameMove();
    }
    return 0;
}
/*
    brief: this function is used to clear the Board and Ask for whom to start and what difficulty
*/
void initBoard(void){
    uint8_t u8_index = 0;
    for(u8_index = 0; u8_index < 9; ++u8_index)
    {
        gau8_board[u8_index] = '-';
    }
    uint8_t u8_ans;
    gu8_gameStatus = GAMEON;
    printf("Choose Difficulty: 1)Easy. 2)Hard.\n");
    while(1){
    scanf("%d", &gu8_mode);
    fflush(stdin);
    if(gu8_mode == 1 || gu8_mode == 2){
        break;
    }
    else{
        printf("Invalid Input, Please Type 1 for easy or 2 for hard.");
    }
    }
    printf("Do you want to play first [Y/N]? ");
    while (1)
    {
        scanf("%c", &u8_ans);
        fflush(stdin);
        if(u8_ans == 'Y' || u8_ans == 'y'){
            gu8_turn = PLAYER;
            break;
        }
        else if(u8_ans == 'N' || u8_ans == 'n'){
            gu8_turn = COMPUTER;
            break;
        }
        else{
            printf("Invalid answer, please answer with Y or N: ");
        }
    }

}
/*
    brief: this function is used to print the board
*/
void printBoard(void){
    uint8_t u8_index = 0;
    printf("\n Board: \n");
    for(u8_index = 0; u8_index < 9; u8_index+=3)
    {
        printf("\n %c | %c | %c\n", gau8_board[u8_index], gau8_board[u8_index+1], gau8_board[u8_index+2]);
    }
}
/*
    brief: this function is the base of the game and gets called for each move until the game ends
*/
void gameMove(void){
    int8_t s8_move = -1;
    if(gu8_turn == PLAYER){
    while (s8_move < 1 || s8_move > 9)
        {
           getPlayerMove(&s8_move);
        }
        gau8_board[s8_move-1] = 'O';
    }
    else if(gu8_turn == COMPUTER){
        while (s8_move < 0 || s8_move > 8)
        {
            s8_move = getComputerMove();
        }
        gau8_board[s8_move] = 'X';
    }
    printBoard();
    int8_t s8_status = checkForWin();
    switch (s8_status)
    {
    case PLAYER:
        printf("You Win.");
        gu8_gameStatus = GAMEOVER;
        break;
    case COMPUTER:
        printf("You Lose.");
        gu8_gameStatus = GAMEOVER;
        break;
    case DRAW:
        printf("The game is a Draw.");
        gu8_gameStatus = GAMEOVER;
        break;
    default:
        gu8_turn = !gu8_turn;
        break;
    }
}
/*
    brief: this function is used to get the player's next move
    param. : (input) pointer to signed integer to register the player move to
*/
void getPlayerMove(int8_t* ps8_playerMove){
    if(ps8_playerMove != NULL){

        printf("Please Enter a move from 1 to 9: ");
        int8_t s8_checkInput;
        while (1)
        {
            s8_checkInput = scanf("%d", ps8_playerMove);
            fflush(stdin);
            if(s8_checkInput != 1){
                printf("Ivalid Input, Please Enter a move from 1 to 9: ");
            }
            else if(*ps8_playerMove < 1 || *ps8_playerMove > 9){
                printf("Move out of range, Please Enter a move from 1 to 9: ");
            }
            else if (gau8_board[*ps8_playerMove-1] != '-')
            {
                printf("Square is not empty, Please Enter a different move from 1 to 9: ");
            }
            else{
                break;
            }         
        }
    }
    else{
        printf("\nThere's an error, please restart.");
    }
}
/*
    brief: this function is used to check all possible combinations for the win
*/
int8_t checkForWin(void){
    //check for 3 in a row
    uint8_t u8_index = 0;
    for(u8_index = 0; u8_index < 9; u8_index += 3){
        if(gau8_board[u8_index] != '-' && gau8_board[u8_index] == gau8_board[u8_index + 1] && gau8_board[u8_index] == gau8_board[u8_index + 2])
        {
            return gau8_board[u8_index] == 'O'? PLAYER : COMPUTER;
        }
    }
    //Check for 3 in a column
    for(u8_index = 0; u8_index < 3; u8_index++){
        if(gau8_board[u8_index] != '-' && gau8_board[u8_index] == gau8_board[u8_index + 3] && gau8_board[u8_index] == gau8_board[u8_index + 6])
        {
            return gau8_board[u8_index] == 'O'? PLAYER : COMPUTER;
        }
    }
    //check for 3 in a diagonal
    if(gau8_board[4] != '-' &&
     ((gau8_board[4] == gau8_board[0] && gau8_board[4] == gau8_board[8])|| (gau8_board[4] == gau8_board[2] && gau8_board[4] == gau8_board[6]))){
        return gau8_board[4] == 'O'? PLAYER : COMPUTER;
     }
    //check for draw
    for(u8_index = 0; u8_index < 9; u8_index++){
        if(gau8_board[u8_index] == '-'){
            return GAME_IN_PLAY;
        }
    }
    return DRAW;
}
/*
    brief: this function is used to determine the computer's next smart move
    return: a signed integer holds the computer's next move
*/
int8_t getComputerMove(void){
    uint8_t au8_availableMoves[9];
    uint8_t u8_index = 0;
    int8_t s8_computerMove = -1;
    uint8_t u8_lastEmpty = 0;
    for(u8_index = 0; u8_index < 9; u8_index++){
        if(gau8_board[u8_index] == '-'){
            au8_availableMoves[u8_lastEmpty++] = u8_index;
        }
    }
    //Smart Computer
    int8_t s8_status;
    for(u8_index = 0; u8_index < u8_lastEmpty; u8_index++){
        //Computer goes for the win    
        gau8_board[au8_availableMoves[u8_index]] = 'X';
        s8_status = checkForWin();
        gau8_board[au8_availableMoves[u8_index]] = '-';        
        if(s8_status == COMPUTER)
        {
            return au8_availableMoves[u8_index];
        }      
    }
    for(u8_index = 0; u8_index < u8_lastEmpty; u8_index++){
        //computer goes for the block
        gau8_board[au8_availableMoves[u8_index]] = 'O';
        s8_status = checkForWin();
        gau8_board[au8_availableMoves[u8_index]] = '-';        
        if(s8_status == PLAYER)
        {
            return au8_availableMoves[u8_index];
        }      
    }
    if(gu8_mode == HARD_MODE){
    //Computer goes for better moves
    uint8_t au8_bestMoves[4];
    uint8_t u8_lastBestMove = 0;
    for(u8_index =0; u8_index <u8_lastEmpty; u8_index++)
    {
        //check for center(Best move) then check for corners(Second Best)
        if(au8_availableMoves[u8_index] == 4)
        {
            return au8_availableMoves[u8_index];
        }
        else if(au8_availableMoves[u8_index] % 2 == 0){
            au8_bestMoves[u8_lastBestMove++] = au8_availableMoves[u8_index];
        }
    }
    //Dummy Computer
    if(u8_lastBestMove > 0){
        s8_computerMove = rand() % u8_lastBestMove;
        s8_computerMove = au8_bestMoves[s8_computerMove];
        return s8_computerMove;
    }
    }
    s8_computerMove = rand() % u8_lastEmpty;
    s8_computerMove = au8_availableMoves[s8_computerMove];
    return s8_computerMove;
}