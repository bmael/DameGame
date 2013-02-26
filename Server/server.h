#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>	/* pour les sockets */
#include <sys/socket.h>
#include <netdb.h>			/* pour hostent, servent */
#include <string.h>			/* pour bcopy, ... */

#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

#include "basic_command.h"
#include "include/command.h"

#define TAILLE_MAX_NOM 256
#define PORT 5000       // can be changed if you type a port number before the execution

typedef struct in_addr in_addr;
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;

/******************************** GLOBALS *************************************/

int cpt_max_client = 3;		/* Size of the max client for the realloc function */

player *players;		/* Array of connected players */
int cpt_players = 0;		/* Number of connected players */
pthread_mutex_t players_mutex;

int *sockets;

/******************************************************************************/


/**
 * @brief Interprete the action wanted by the client and execute it.
 * @param sock
 */
void * client_manager_cmd(void * sock);


/**
 * @brief Send the online players list to a client
 * @param socket_descriptor the socket descriptor of the client 
 */
void send_nb_client(int socket_descriptor);

