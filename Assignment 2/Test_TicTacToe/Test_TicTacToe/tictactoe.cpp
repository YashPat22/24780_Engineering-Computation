//
//  tictactoe.cpp
//  Test_TicTacToe
//
//  Created by Yash Patawari on 9/11/22.
//

#include <stdio.h>

void PrintBoard(char board[])
{
    for(int y=0; y<3; ++y)
    {
        for(int x=0; x<3; ++x)
        {
            int i=y*3+x;
            printf("%c",board[i]);
            if(x<2)
            {
                printf("|");
            }
        }
        printf("\n");
        if(y<2)
        {
            printf("-+-+-\n");
        }
    }
}

bool CheckWinner(char mark,char board[])
{
    if((board[0]==mark && board[1]==mark & board[2]==mark) ||
       (board[3]==mark && board[4]==mark & board[5]==mark) ||
       (board[6]==mark && board[7]==mark & board[8]==mark) ||

       (board[0]==mark && board[3]==mark & board[6]==mark) ||
       (board[1]==mark && board[4]==mark & board[7]==mark) ||
       (board[2]==mark && board[5]==mark & board[8]==mark) ||

       (board[0]==mark && board[4]==mark & board[8]==mark) ||
       (board[2]==mark && board[4]==mark & board[6]==mark))
    {
        return true;
    }
    return false;
}

int main(void)
{
    char board[9];
    for(auto &b : board)
    {
        b=' ';
    }

    char turn='X';
    for(;;)
    {
        PrintBoard(board);
        if(true==CheckWinner('O',board))
        {
            printf("O wins!\n");
            break;
        }
        else if(true==CheckWinner('X',board))
        {
            printf("X wins!\n");
            break;
        }

        printf("%c's turn.\n",turn);
        printf("Enter X Y:");

        int x,y;
        scanf("%d%d",&x,&y);

        if(0<=x && x<3 && 0<=y && y<3)
        {
            if(' '==board[y*3+x])
            {
                board[y*3+x]=turn;
                if('X'==turn)
                {
                    turn='O';
                }
                else
                {
                    turn='X';
                }
            }
            else
            {
                printf("Column is already used.\n");
            }
        }
        else
        {
            printf("Enter between 0 and 2.\n");
        }
    }

    return 0;
}
