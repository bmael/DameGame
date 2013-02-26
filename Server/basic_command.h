#include "include/frame.h"
#include "include/structures.h"
#include "include/command.h"


/**
 * @brief Reallocates memory for the players and the sockets array. Exit with error 1
 *if it can't reallocates memory.
 * @param players the array of players to reallocate memory
 * @param sockets the array of sockets (int) to reallocate memory
 * @param cpt_max_client after the process this variable contains the new size.
 */
void memory_reallocation(player *players,
                          int *cpt_max_client);

/**
 * @brief Display the online players on the standard output.
 * @param cpt_players number of players to display.
 * @param players the array of players to display.
 * @param sockets the array of sockets to display.
 */
void display_online_players(int cpt_players, player *players);

/**
 * @brief Send a frame on the given socket descriptor.
 * @param socket_descriptor for the sending of the frame.
 * @param f the frame to send.
 */
void write_to_client(int socket_descriptor, frame *f);

/**
 * @brief Process for command CONNECTION. Add a player with his socket into an array stored by the server. Calls @ref memory_reallocation if needed.
 * @param f the frame with the data for the process
 * @param players the players array to modify.
 * @param sockets the sockets array to modify.
 * @param socket_descriptor the socket descriptor of the player to add.
 * @param cpt_players number of player before insertion. This variable is increased by 1 after the process.
 * @param cpt_max_client the number of maximum player that server can store.
 */
void connection(frame * f,
               player *players,
               int socket_descriptor,
               int *cpt_players,
               int cpt_max_client);

/**
 * @brief Process for command DISCONNECTION. Remove a player with its socket from an array stored by the server.
 * @param f the frame with the data for the process.
 * @param players the players array to modify.
 * @param sockets the sockets array to modify.
 * @param cpt_players number of player before deletion. This variable is decreased by 1 after the process.
 */
void disconnection(frame *f, player *players, int *cpt_players);

/**
 * @brief Send an information (determinize by the command) to all the clients.
 * @param command the command to inerpret for the frame generation.
 * @param cpt_players the number of players to advise.
 * @param players the array of players.
 * @param sockets the array of sockets.
 */
void alert_all_client(char * command, int cpt_players, player *players);
