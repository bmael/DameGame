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



int test_movement(int player_color, movement m, checkerboard * game) {
    // The selected checker is not a player's checker
    if ( game->gameboard[m.startPoint.line][m.startPoint.column] != player_color ) {
        printf("The selected checker is not one of the player's checkers\n");
        return 0;
    }

    // Square is not empty
    if ( game->gameboard[m.endPoint.line][m.endPoint.column] != EMPTY_CELL ) {
        printf("You can't move your checker to a square that is not empty\n");
        return 0;
    }

    // Wrong line
    if( m.endPoint.line != m.startPoint.line + player_color ) {
        printf("Wrong line\n");
        return 0;
    }

    // Wrong column
    if( (m.endPoint.column != (m.startPoint.column+1)) && (m.endPoint.column != (m.startPoint.column-1)) ) {
        printf("Wrong column\n");
        return 0;
    }

    // Otherwise, the movement is valid
    return 1;
}



void move_checker(int player_color, movement m, int capture, checkerboard * game) {
    game->gameboard[m.startPoint.line][m.startPoint.column] = EMPTY_CELL;
    game->gameboard[m.endPoint.line][m.endPoint.column] = player_color;

    if ( capture == 1 ) {
        if ( player_color == WHITE_CHECKER ) {
            game->nb_black--;
            game->gameboard[(m.endPoint.line + m.startPoint.line)/2][(m.endPoint.column + m.startPoint.column)/2] = EMPTY_CELL;
        }
        else {
            game->nb_white--;
            game->gameboard[(m.endPoint.line + m.startPoint.line)/2][(m.endPoint.column + m.startPoint.column)/2] = EMPTY_CELL;
        }
    }
}



int start_game(checkerboard * game) {
    movement m;
    square start;
    square end;

    int player_color = WHITE_CHECKER;   // WHITE starts first

    print_gameboard(game->gameboard);
    printf("##### White starts #####\n");

    while ( game_ended(game) == 0 ) {

        printf("Enter the checker you want to move:");
        scanf("%d %d", &(start.line), &(start.column));
        m.startPoint = start;

        printf("Enter the new position of this checker:");
        scanf("%d %d", &(end.line), &(end.column));
        m.endPoint = end;

        move_checker(player_color, m, 0, game);
        print_gameboard(game->gameboard);

        // Changing turn
        if ( player_color == WHITE_CHECKER ) {
            player_color = BLACK_CHECKER;
            printf("##### Black's turn #####\n");
        }
        else {
            player_color = WHITE_CHECKER;
            printf("##### White's turn #####\n");
        }
    }
    return game_ended(game);
}



int game_ended(checkerboard * game) {
    if ( game->nb_white == 0 ) {
        return WHITE_CHECKER;
    }
    if ( game->nb_black == 0 ) {
        return BLACK_CHECKER;
    }

    return 0;
}
