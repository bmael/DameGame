#include "gameboard.h"
#include <stdio.h>


void print_line(int i, int gameboard[10][10]){

    printf(" %2d ", i+1);
    int j;
    for (j=0; j<10 ; j++){
        switch(gameboard[i][j]) {
            case BLACK_CHECKER :
                printf("| X ");
                break;
            case BLACK_DRAUGHT :
                printf("| [X] ");
                break;
            case WHITE_CHECKER :
                printf("| O ");
                break;
            case WHITE_DRAUGHT :
                printf("| [O]");
                break;

            default :
                printf("|   ");
                break;
        }
    }

    printf("| %2d\n", i+1);
    printf("    |---------------------------------------|\n") ;
}

void print_gameboard(int gameboard[10][10]){

    printf("      a   b   c   d   e   f   g   h   i   j  \n") ;
    printf("    |---------------------------------------|\n") ;

    int i;
    for(i=0 ;i<10 ;i++) print_line(i,gameboard) ;

    printf("      a   b   c   d   e   f   g   h   i   j  \n") ;

}

void init_gameboard(checkerboard* game){
    game->nb_black = 20;
    game->nb_white = 20;

    int i, j;

    // EMPTY_CELL for all gameboard cells.
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            game->gameboard[i][j] = EMPTY_CELL;
        }
    }

    // Top of the gameboard is BLACK_CHECKER
    for(i=0; i<4; i++){
        //if i is even, the first cell have to be black
        if(i%2 == 0) { j = 1; }
        else { j = 0; }

        for(j;j<10;j+=2){
            game->gameboard[i][j] = BLACK_CHECKER;
        }
    }

    // Bottom of the gameboard is WHITE_CHECKER
    for(i=6; i<10; i++){
        //if i is even, the first cell have to be black
        if(i%2 == 0) { j = 1; }
        else { j = 0; }

        for(j;j<10;j+=2){
            game->gameboard[i][j] = WHITE_CHECKER;
        }
    }

}

