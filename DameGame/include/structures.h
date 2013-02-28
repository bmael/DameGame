/* *****************************************************************************
 * File structures.h
 * Project DameGame
 * Maël BARBIN - Julien BIZEUL
 * M1 ALMA - Université de Nantes
 * 2012-2013
 *
 *  Defines some structures very useful for our game
 ******************************************************************************/
#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct {
    int gameboard[10][10];  // State of the gameboard
    int nb_black;           // number of black
    int nb_white;           // number of white
} checkerboard;

typedef struct {
    char name[10];    // Player's name
    int socket;     // Player's socket
    int color;      // Color of his checkers
} player;

#endif // STRUCTURE_H
