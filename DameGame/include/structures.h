/* *****************************************************************************
 * File structures.h
 * Project DameGame
 * Maël BARBIN - Julien BIZEUL
 * M1 ALMA - Université de Nantes
 * 2012-2013
 *
 *  Defines some structures very useful for our game
 ******************************************************************************/


typedef struct {
    int gameboard[10][10];  // State of the gameboard
    int nb_black;           // number of black
    int nb_white;           // number of white
} checkerboard;

typedef struct {
    char * name;    // Player's name
    int color;      // Color of his checkers
} player;


