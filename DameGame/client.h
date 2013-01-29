#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>





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
 * @brief Copies the host information into the the local adress
 * @param ptr_host
 * @param local_addr
 */
void cpy_hostinfo(hostent *ptr_host, sockaddr_in *local_addr);


/**
 * @brief Assigns a port to the client
 * @param local_addr
 */
void assign_port(sockaddr_in *local_addr, int port);

/**
 * @brief Creates the socket descriptor
 * @param socket_descriptor
 */
void create_socket(int * socket_descriptor);

/**
 * @brief Connects the client to the server.
 */
void server_connection(int socket_descriptor, sockaddr_in local_addr);



#endif
