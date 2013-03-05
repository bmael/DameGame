
#include "basic_command.h"

/**
 * @brief Constructs a frame with all players and send it to the client.
 * @param socket_descriptor of the client to send the frame.
 * @param players the array of players to send.
 */
void send_players_list(int socket_descriptor, player * players, int cpt_players);

void send_nb_players(int socket_descriptor, int cpt_players);

void send_player(int socket_descriptor, player p);

void send_all_players(int socket_descriptor, player * players, int cpt_players);

void send_new_game_request(int socket_descriptor, player from);

void send_reject_new_game_request(int socket_descriptor, player from);

void send_accept_new_game_request(int socket_descriptor, player from, player * players, int cpt_players);

