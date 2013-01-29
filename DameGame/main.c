#include <stdio.h>
#include <stdlib.h>

#include "gameboard.h"

int main(void)
{

    checkerboard * game = (checkerboard *) calloc(sizeof(checkerboard), 1);
    init_gameboard(game);
    print_gameboard(game->gameboard);

    return 0;
}

