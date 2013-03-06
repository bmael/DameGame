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




void affiche_choixcoup(listeCases* rafle, int n, int couleur, damier* jeu) {
	int ok = 0;
	int i;
	char buffer[50];
	do {
		printf( "Plusieurs coups sont possibles %d : \n",n) ;
		for(i=0 ;i<n ;i++) {
			printf(" %d : ",i+1) ;
			affiche_rafle(rafle[i]) ;
		}
		if(scanf( " %d ",&i) ==1 && i>0 && i<=n) {
			faire_coup(rafle[i-1],couleur,jeu) ;
			ok = 1 ;
		}
		//Vide le tampon
		else fflush(stdin) ;
	} while(ok == 0) ;
}



int test_movement(int player_color, movement m, checkerboard * game) {
    // The selected checker is not a player's checker
    if ( game->gameboard[m.startPoint.line][m.startPoint.column] != player_color ) {
        printf("\tERROR : The selected checker is not one of the player's checkers\n");
        return 0;
    }

    // Square is not empty
    if ( game->gameboard[m.endPoint.line][m.endPoint.column] != EMPTY_CELL ) {
        printf("\tERROR : You can't move your checker to a square that is not empty\n");
        return 0;
    }

    // Wrong line
    if( m.endPoint.line != m.startPoint.line + player_color ) {
		if ( (m.endPoint.line != m.startPoint.line + (player_color*2)) && (game->gameboard[(m.endPoint.line + m.startPoint.line)/2][(m.endPoint.column + m.startPoint.column)/2] != player_color) ) {
			printf("\tINFO : Capturing an opponent checker\n");
			return 1;
		}
        printf("\tERROR : Wrong line\n");
        return 0;
    }

    // Wrong column
    if( (m.endPoint.column != (m.startPoint.column+1)) && (m.endPoint.column != (m.startPoint.column-1)) ) {
		if( (m.endPoint.column == (m.startPoint.column+2)) && (m.endPoint.column != (m.startPoint.column-2)) ) {
			printf("Capturing an opponent checker\n");
			return 0;
		}
        printf("\tERROR : Wrong column\n");
        return 0;
    }

    // Otherwise, the movement is valid
    return 1;
}



int test_and_execute_movement(int player_color, movement m, checkerboard * game) {
    if ( game->gameboard[m.startPoint.line][m.startPoint.column] == player_color ) {
        return test_and_execute_movement_checker(player_color, m, game);
    }
	else if ( game->gameboard[m.startPoint.line][m.startPoint.column] == 2 * player_color ) {
        return test_and_execute_movement_draught(player_color, m, game);
    }
    else {
		printf("\tERROR : Wrong selection\n");
		return 0;
    }
}



int test_and_execute_movement_checker(int player_color, movement m, checkerboard * game) {
	// Square is not empty
    if ( game->gameboard[m.endPoint.line][m.endPoint.column] != EMPTY_CELL ) {
        printf("\tERROR : You can't move your checker to a square that is not empty\n");
        return 0;
    }

    // Wrong line
    if( m.endPoint.line != m.startPoint.line + player_color ) {
		// If trying to capture
		if ( ( (m.endPoint.line == m.startPoint.line + (player_color*2)) || (m.endPoint.line == m.startPoint.line - (player_color*2)) ) &&
			 ( (m.endPoint.column == (m.startPoint.column+2)) || (m.endPoint.column == (m.startPoint.column-2)) ) ) {
				
			if ( (game->gameboard[(m.endPoint.line + m.startPoint.line)/2][(m.endPoint.column + m.startPoint.column)/2] != player_color) &&
				 (game->gameboard[(m.endPoint.line + m.startPoint.line)/2][(m.endPoint.column + m.startPoint.column)/2] != EMPTY_CELL) ) {
				
				printf("\tINFO : Capturing an opponent checker\n");
				move_checker(player_color, m, 1, game);
				return 1;
			}
		}
        printf("\tERROR : Wrong line\n");
        return 0;
    }

    // Wrong column
    if( (m.endPoint.column != (m.startPoint.column+1)) && (m.endPoint.column != (m.startPoint.column-1)) ) {
        printf("\tERROR : Wrong column\n");
        return 0;
    }

    // Otherwise, the movement is valid
    printf("\tINFO : valid movement\n");
    move_checker(player_color, m, 0, game);
    return 1;
}



int test_deplace_dame(damier* jeu, int couleur,deplacement d) {
	int i = m.startPoint.line;
	int j = m.startPoint.column;
	
	while ( i != m.endPoint.line || j != m.endPoint.column ) {
		if( m.endPoint.line > m.startPoint.line ) {
			i++;
		}
		else {
			i--;
		}
		
		if ( m.endPoint.column > m.startPoint.column ) {
			j++;
		}
		else {
			j--;
		}
	}
	if( game->gameboard[i][j] != EMPTY_CELL ) {
		printf("\tERROR : You can't move your draught to a square that is not empty\n");
		return 0;
	}
	
	return 1;
}

int test_and_execute_movement_draught(int player_color, movement m, checkerboard * game) {
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



void move_draught(int player_color, movement m, int capture, square captured_pos, checkerboard * game) {
	game->gameboard[m.startPoint.line][m.startPoint.column] = EMPTY_CELL;
	game->gameboard[m.endPoint.line][m.endPoint.column] = 2 * player_color;
	
	if ( (capture==1) &&
		 ( (game->gameboard[captured_pos.line][captured_pos.column] == -player_color) ||
		   (game->gameboard[captured_pos.line][captured_pos.column] == -player_color * 2) )
	   ) {
		game->gameboard[captured_pos.line][captured_pos.column] = EMPTY_CELL;
		if ( player_color == WHITE_CHECKER ) {
			game->nb_black--;
		}
		else {
			game->nb_white--;
		}
	}
}



void promote_checkers(checkerboard * game, int player_color) {
	int i,j;
	if ( player_color == BLACK_CHECKER ) {
		i=9;
		j=0;
	}
	else {
		i=0;
		j=1;
	}
	for (j ; j < 10 ; j += 2 ) {
		if ( game->gameboard[i][j] == player_color ) {
			game->gameboard[i][j] = 2 * player_color;
		}
	}
}



int is_square_valid(square s) {
	if ( (s.line < 10) && (s.column < 10) ) {
		return 1;
	}
	else {
		printf("\tERROR : Out of bounds square!\n");
		return 0;
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
		do {
			char c;
			do {
				printf("Enter the checker you want to move:");
				scanf("%d%c", &(start.line), &c);
				start.line--;
				start.column = c - 97;
			} while ( !is_square_valid(start) ) ;
			m.startPoint = start;

			do {
				printf("Enter the new position of this checker:");
				scanf("%d%c", &(end.line), &c);
				end.line--;
				end.column = c - 97;
			} while ( !is_square_valid(end) ) ;
			m.endPoint = end;
		}
		while( test_and_execute_movement(player_color, m, game) == 0 );
		
		promote_checkers(game, player_color);
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
