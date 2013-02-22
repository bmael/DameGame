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
 * @brief Make a frame
 * @param src the source address
 * @param dest the destination address
 * @param datatype the type of the frame
 * @param data the data to send with the frame
 * @return
 */
frame make_frame(in_addr src, in_addr dest, char * datatype, char * data);

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

#endif
