#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#include "command.h"
#include "frame.h"
#include "structures.h"


typedef struct sockaddr 	sockaddr;
typedef struct sockaddr_in 	sockaddr_in;
typedef struct hostent 		hostent;
typedef struct servent 		servent;


/**
 * @brief Initializes the host
 * @param hostent * ptr_host - information about host
 * @param char * host - the address of the host
 * @param sockaddr_in * local_addr - the local addressof the client.
 */
void init_host(hostent *ptr_host, char * host, sockaddr_in *local_addr);

/**
 * @brief Assigns a port to the client
 * @param sockaddr_in * local_addr - the local address of the client
 * @param int port - the port used by the server.
 */
void assign_port(sockaddr_in *local_addr, int port);

/**
 * @brief Creates the socket descriptor
 * @return int res - if res is greater than 0 it is the socket descriptor otherwise, create_socket return an error.
 */
int create_socket();

/**
 * @brief Connects the client to the server.
 * @param int socket_descriptor - the socket descriptor used by the client.
 * @param sockaddr_in local_addr - the local address of the client.
 */
int server_connection(int socket_descriptor, sockaddr_in local_addr);

/**
 * @brief Disconnects the client.
 * @param int socket_descriptor - the socket descriptor used by the client to disconnect
 */
void server_disconnection(int socket_descriptor);



/**
 * @brief Sends a frame to the server
 * @param int socket_descriptor - the socket descriptor used for the communication with the server.
 * @param frame * f - the frame to send
 */
void write_to_server(int socket_descriptor, frame *f);

/**
 * @brief Read information from the server
 * @param int socket_descriptor - the socket descriptor to read.
 * @param frame * f - the frame where is stored the result of the reading.
 */
int read_server_information(int socket_descriptor, frame *f);

/**
 * @brief Listen to interprete the server instruction
 * @param sock the socket to listen
 */
void * listen_server_instruction(void *s);

/**
 * @brief Displays all players on the standard output
 * @attention Do not working
 * @param player * players - the array of players to display
 * @param int size - the size of the array.
 */
void display_online_players(player * players, int size);

#endif
