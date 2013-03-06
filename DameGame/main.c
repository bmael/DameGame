#include <stdio.h>
#include <stdlib.h>

#include "gameboard.h"



int main(void)
{

    checkerboard * game = (checkerboard *) calloc(sizeof(checkerboard), 1);
    init_gameboard(game);

    start_game(game);

    print_gameboard(game->gameboard);

    printf("%d pions blancs\n", game->nb_white);
    printf("%d pions noirs\n", game->nb_black);
	
	free(game);

    return 0;
}

