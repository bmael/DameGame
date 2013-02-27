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
 * @param ptr_host
 * @param host the address of the host
 */
void init_host(hostent *ptr_host, char * host, sockaddr_in *local_addr);

/**
 * @brief Assigns a port to the client
 * @param local_addr
 */
void assign_port(sockaddr_in *local_addr, int port);

/**
 * @brief Creates the socket descriptor
 * @param socket_descriptor
 */
int create_socket();

/**
 * @brief Connects the client to the server.
 * @param socket_descriptor
 * @param local_addr
 */
void server_connection(int socket_descriptor, sockaddr_in local_addr);

/**
 * @brief Disconnects the client.
 * @param socket_descriptor
 */
void server_disconnection(int socket_descriptor);



/**
 * @brief Send a frame to the server
 * @param socket_descriptor used
 * @param f the frame to send
 */
void write_to_server(int socket_descriptor, frame *f);

/**
 * @brief Read information from the server
 * @param socket_descriptor
 * @param pbuf
 */
frame read_server_information(int socket_descriptor);

/**
 * @brief Listen to interprete the server instruction
 * @param sock the socket to listen
 */
void * listen_server_instruction(void *s);

void display_online_players(player * players, int size);

#endif
