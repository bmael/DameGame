# define EMPTY_CELL     0
# define BLACK_CHECKER  1
# define BLACK_DRAUGHT  2
# define WHITE_CHECKER -1
# define WHITE_DRAUGHT -2


#include "include/structures.h"	// structures for checkerboard, player, square and movement

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

/**
 * Test if a movement is valid
 * 	Returns 1 if the movement is valid, 0 otherwise
 *
 */
int test_movement(int player_color, movement m, checkerboard * game);

/**
 * Test if a movement is valid, and execute it if it is
 * 	Returns 1 if the movement is valid, 0 otherwise
 *
 */
int test_and_execute_movement(int player_color, movement m, checkerboard * game);

/**
 * Test if a movement is valid, and execute it if it is
 * 	Returns 1 if the movement is valid, 0 otherwise
 *
 */
int test_and_execute_movement_checker(int player_color, movement m, checkerboard * game);

/**
 * Test if a movement is valid, and execute it if it is
 * 	Returns 1 if the movement is valid, 0 otherwise
 *
 */
int test_and_execute_movement_draught(int player_color, movement m, checkerboard * game);

/**
 * Moves a checker
 *
 */
void move_checker(int player_color, movement m, int capture, checkerboard * game);

/**
 * Moves a draught
 * 
 */
void move_draught(int player_color, movement m, int capture, square captured_pos, checkerboard * game);

/**
 * Promote checkers to draught
 * 
 */
void promote_checkers(checkerboard * game, int player_color);

/**
 * Starts a game with the given checkerboard
 *
 */
int start_game(checkerboard * game);

/**
 * Returns 0 if the game is ended, 1 if BLACK is the winner or -1 if it is WHITE
 *
 */
int game_ended(checkerboard * game);
