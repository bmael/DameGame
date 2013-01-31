/*----------------------------------------------
Serveur à lancer avant le client
------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>	/* pour les sockets */
#include <sys/socket.h>
#include <netdb.h>			/* pour hostent, servent */
#include <string.h>			/* pour bcopy, ... */

#include <pthread.h>

#include "structures.h"
#include "server.h"

#define TAILLE_MAX_NOM 256

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;

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

void * client_manager(void * sock){
  char buffer[256];
  int longueur;
  
  /* cast of sock */
  int *tmp = (int*) sock;
  int nouv_socket_descriptor = *tmp;
  
  for(;;){
    
    if ( (longueur = read(nouv_socket_descriptor, buffer, sizeof(buffer))) <= 0 ) {
      return;
    }
    
    
    /* Add a client to the players list */
    if(strstr(buffer,"addClient:")){
	pthread_mutex_lock(&players_mutex);
	printf("adding client...\n");
      
	char player_name[200];
	strtok(buffer, ":");
	strcpy(player_name, strtok(NULL, ":"));
	
	player to_add;
	to_add.name = player_name;
	
	players[cpt_players] = to_add;
	sockets[cpt_players] = nouv_socket_descriptor;
	
	cpt_players++;
	
	display_online_players();

	
	/* Advising all client that there is an incoming connection */
	alert_all_client("incomingConnection");
	pthread_mutex_unlock(&players_mutex);
	
	
    }
        
    /* Remove a client from the player list */
    if(strstr(buffer,"removeClient:")){
      
      	pthread_mutex_lock(&players_mutex);
	printf("removing a client.....\n");
      
	char player_name[200];
	strtok(buffer, ":");
	strcpy(player_name, strtok(NULL, ":"));
      
	//search the players on the list
	int i = 0;
	int find = 0;
	while((!find) && (i < cpt_players)){	  
	  if(strcmp(players[i].name,player_name) == 0){find=1;}
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
	
    }

    display_online_players();
  }
  
  close(nouv_socket_descriptor);
 
}


void alert_all_client(char * command){
  
  printf("Command to execute : %s\n", command);
  
  int socket_descriptor;
  int i;
  for(i = 0; i<cpt_players; i++){
    socket_descriptor = sockets[i];
    
    if(strcmp(command,"incomingConnection") == 0){
      printf("---> advising the client[%d]\n", i);
      printf("---> with socket : %d", socket_descriptor);
      if((write(socket_descriptor, players[cpt_players-1].name, strlen(players[cpt_players-1].name))) < 0){
	  perror("[Server_incomingConnection] : Can't write the message to send to the client");
	  exit(1);
      }
      printf("Incoming connection : advising client : %d\n", socket_descriptor);
    }
    
    socket_descriptor = 0;

  }

  close(socket_descriptor);

}


/*------------------------------------------------------------*/

/*------------------------------------------------------------*/
int main(int argc, char **argv) {
  
  int socket_descriptor,		/* Descripteur de socket */
      nouv_socket_descriptor,		/* [nouveau] descripteur de socket */
      longueur_adresse_courante;	/* Longueur d'adresse courante d'un client */
      sockaddr_in adresse_locale,	/* Structure d'adresse locale */
      adresse_client_courant;		/* Adresse client courant */
  
  hostent* ptr_hote;			/* Les infos récupérées sur la machine hôte */
  servent* ptr_service;			/* Les infos récupérées sur le service de la machine */
  char machine[TAILLE_MAX_NOM];	/* Nom de la machine locale */
  
  gethostname(machine, TAILLE_MAX_NOM);	/* Récupération du nom de la machine */

  pthread_t nouveau_client;	/* Thread for each client */

  /* Allocation of memory for players */
  players = calloc(3, sizeof(player));
  sockets = calloc(3, sizeof(int));
	
  /* Récupération de la structure d'adresse en récupérant le nom */
  if ( (ptr_hote = gethostbyname(machine)) == NULL ) {
    perror("erreur : impossible de trouver le serveur à partir de son nom.");
    exit(1);
  }
  
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
  adresse_locale.sin_port = htons(5000);
  
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
	if(pthread_create(&nouveau_client, NULL, client_manager, &nouv_socket_descriptor)){
		perror("problème sur le thread");
		return 1;
	}
	
	

  }
  
    close(socket_descriptor);

}
