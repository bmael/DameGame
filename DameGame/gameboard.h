# define EMPTY_CELL     0
# define BLACK_CHECKER  1
# define BLACK_DRAUGHT  2
# define WHITE_CHECKER -1
# define WHITE_DRAUGHT -2


#include "structures.h"

/**
 * Prints a line of the gameboard
 *
 */
void print_line(int i, int gameboard[10][10]);

/**
 * Prints all the gameboard
 *
 */
void print_gameboard(int gameboard[10][10]);

/**
 * Itializes the gameboard
 *
 */
void init_gameboard(checkerboard* game);
