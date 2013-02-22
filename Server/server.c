/*----------------------------------------------
Serveur à lancer avant le client
------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>	/* pour les sockets */
#include <sys/socket.h>
#include <netdb.h>			/* pour hostent, servent */
#include <string.h>			/* pour bcopy, ... */

#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

#include "include/structures.h"
#include "include/command.h"
#include "include/frame.h"

#include "server.h"

#define TAILLE_MAX_NOM 256
#define PORT 5000

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;

int cpt_max_client = 3;		/* Size of the max client for the realloc function */

player *players;		/* Array of connected players */
int cpt_players = 0;		/* Number of connected players */
pthread_mutex_t players_mutex;

int *sockets;



void display_online_players(){
 
  printf("Players Online\n");
  printf("---------------\n");
 
  int i;
  for(i=0; i<cpt_players; i++){
   printf("-- %s\n",players[i].name); 
  }
  
  printf("Server can talk \n");
  printf("---------------\n");
 
  for(i=0; i<cpt_players; i++){
   printf("-- %d\n",sockets[i]); 
  }
    
}

void * client_manager_cmd(void * sock){
  int longueur;
  
  /* cast of sock */
  int *tmp = (int*) sock;
  int nouv_socket_descriptor = *tmp;
  
  printf("Socket : %d\n", nouv_socket_descriptor);

  for(;;){
    char buffer[sizeof(frame)];
    if ( (longueur = read(nouv_socket_descriptor, buffer, sizeof(frame))) <= 0 ) {
      write(1, buffer, longueur);
      return;
    }
   
    frame f;
    f = *(frame *)buffer;
    printf("connection or somethiong else....\n");
    printf("Type : %s\n", f.data_type);
    printf("Message from client : %s\n", f.data);
    
    
    /* action : CONNECTION */
    if(strcmp(f.data_type, CONNECT) == 0){
      
      	pthread_mutex_lock(&players_mutex);
	printf("adding client...\n");
      
      // Reallocation of memory if needed
	if(cpt_players-1 == cpt_max_client){
	 cpt_max_client *= 2;
	 realloc(sockets, cpt_max_client * sizeof(int));
	 realloc(players, cpt_max_client * sizeof(player));
	}
	
	player to_add;
	to_add.name = f.data;

	players[cpt_players] = to_add;
 	sockets[cpt_players] = nouv_socket_descriptor;
	
	cpt_players++;
	
	/* Advising all client that there is an incoming connection */
	alert_all_client(CONNECT);
	pthread_mutex_unlock(&players_mutex);
	
    } // END CONNECTION
    
    /* action : DISCONNECTION */
    if(strcmp(f.data_type, DISCONNECT) == 0){
      
	pthread_mutex_lock(&players_mutex);
	printf("removing a client.....\n");
            	
	//search the players on the list
	int i = 0;
	int find = 0;
	while((!find) && (i < cpt_players)){	  
	  if(strcmp(players[i].name, f.data) == 0){find=1;}
	  else{i++;}
	}
	
	if(find){
	  //delete the player from the list
	  int j;
	  for(j = i; j < cpt_players-1; j++){
	    players[j] = players[j+1];
	   sockets[j] = sockets[j+1];
	  }

	  cpt_players--;
	  
	}
	
	pthread_mutex_unlock(&players_mutex);
	
    }// END DISCONNECTION

    
    display_online_players();
    
  }

  close(nouv_socket_descriptor);

  
  
}

void alert_all_client(char * command){
  
  printf("Command to execute : %s\n", command);
  
  int client_socket_descriptor;
  int i;
  for(i = 0; i<cpt_players; i++){
    client_socket_descriptor = sockets[i];
    
    if(strcmp(command, CONNECT) == 0){
      printf("---> advising the client[%d]\n", i);
      printf("---> with socket : %d", client_socket_descriptor);
      
      frame f;
      strcpy(f.data_type,INCOMING_CONNECTION) ;
      strcpy(f.data , players[cpt_players-1].name);
      
      if((write(client_socket_descriptor, (char*)&f, sizeof(frame)) < 0)){
	  perror("[Server_incomingConnection] : Can't write the message to send to the client");
	  exit(1);
      }
      printf("Incoming connection : advising client : %d\n", client_socket_descriptor);
    }
  }


}




/*------------------------------------------------------------*/

/*------------------------------------------------------------*/
int main(int argc, char **argv) {
  
  int socket_descriptor,		/* Descripteur de socket */
      nouv_socket_descriptor,		/* [nouveau] descripteur de socket */
      longueur_adresse_courante;	/* Longueur d'adresse courante d'un client */
  sockaddr_in adresse_locale,		/* Structure d'adresse locale */
	adresse_client_courant;		/* Adresse client courant */
  
  hostent* ptr_hote;			/* Les infos récupérées sur la machine hôte */
  servent* ptr_service;			/* Les infos récupérées sur le service de la machine */
  char machine[TAILLE_MAX_NOM];	/* Nom de la machine locale */
  
  gethostname(machine, TAILLE_MAX_NOM);	/* Récupération du nom de la machine */
	printf("Nom de la machine : %s\n",machine);
  pthread_t nouveau_client;	/* Thread for each client */

  /* Allocation of memory for players */
  players = calloc(cpt_max_client, sizeof(player));
  sockets = calloc(cpt_max_client, sizeof(int));
	
  /* Récupération de la structure d'adresse en récupérant le nom */
  if ( (ptr_hote = gethostbyname(machine)) == NULL ) {
    perror("erreur : impossible de trouver le serveur à partir de son nom.");
    exit(1);
  }

	printf("IP de la machine : %s\n",inet_ntoa(*(struct in_addr*)ptr_hote->h_addr));
  
  /* Initialisation de la structure adresse_locale avec les infos récupérées */


  /* Copie de ptr_hote vers adresse_locale */
  bcopy((char*)ptr_hote->h_addr, (char*)&adresse_locale.sin_addr, ptr_hote->h_length);
  adresse_locale.sin_family = ptr_hote->h_addrtype;	/* ou AF_INET */
  adresse_locale.sin_addr.s_addr = INADDR_ANY;	/* ou AF_INET */
  


  /* 2 façons de définir le service que l'on va utiliser à distance */
  /* Commenter l'une où l'autre des 2 solutions */
  
  /*------------------------------------------------------------*/
  /* SOLUTION 1 : utiliser un service existant, par ex. "irc"	  */
  /*------------------------------------------------------------*/
//   if ( (ptr_service = getservbyname("irc", "tcp")) == NULL ) {
//     perror("erreur : impossible de récupérer le numéro de port du service désiré.");
//     exit(1);
//   }
//   adresse_locale.sin_port = htons(ptr_service->s_port);
  
  /*------------------------------------------------------------*/
  /* SOLUTION 2 : Utiliser un nouveau numéro de port            */
  /*------------------------------------------------------------*/
  int port = PORT;
  
  if(argc > 1){
    port = atoi(argv[1]);
  }
  
  adresse_locale.sin_port = htons(port);
  
  /*------------------------------------------------------------*/
  
  printf("Numéro de port pour la connexion au serveur : %d \n", ntohs(adresse_locale.sin_port) /*ntohs(ptr_service->s_port)*/);
  
 	

  /* Création de la socket */
  if ( (socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
    perror("Erreur : impossible de créer la socket de connexion avec le client.");
    exit(1);
  }
  
  /* Association du socket socket_descriptor à la structure d'adresse adresse_locale */
  if ( (bind(socket_descriptor, (sockaddr*)(&adresse_locale), sizeof(adresse_locale))) < 0 ) {
    perror("Erreur : impossible de lier la socket à l'adresse de connexion.");
    exit(1);
  }
  
	printf("Address server : %s \n", inet_ntoa(adresse_locale.sin_addr));

  /* Initialisation de la file d'écoute */
  listen(socket_descriptor,5);
  
  /* Attente des connexions et traitement des données reçues */
  for (;;) {
    longueur_adresse_courante = sizeof(adresse_client_courant);
    /* adresse_client_courant sera renseigné par accept via les infos du connect */
    if ( (nouv_socket_descriptor = accept(socket_descriptor, (sockaddr*)(&adresse_client_courant), &longueur_adresse_courante)) < 0 ) {
      perror("impossible d'accepter la connexion avec le client");
      exit(1);
    }
    
	/* Adding the client to players */
	if(pthread_create(&nouveau_client, NULL, client_manager_cmd, &nouv_socket_descriptor)){
		perror("problème sur le thread");
		return 1;
	}
	
	

  }
  
    close(socket_descriptor);

}
