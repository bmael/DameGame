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

#define TAILLE_MAX_NOM 256

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;

/*------------------------------------------------------------*/
void * renvoi (void * sock) {
  char buffer[256];
  int longueur;

  printf("In a thread \n");
  
  /* cast du soc */
  int *tmp = (int*) sock;
  int nouv_socket_descriptor = *tmp;
  
  printf("Socket : %d\n", nouv_socket_descriptor);
  
  
//  if ( (longueur = read(nouv_socket_descriptor, buffer, sizeof(buffer))) <= 0 ) {
//    return;
//  }
  
//  printf("Message lu : %s \n", buffer);
  
//  buffer[0] = 'R';
//  buffer[1] = 'E';
//  buffer[longueur] = '#';
//  buffer[longueur+1] = '\0';
  
//  printf("Message après traitement : %s \n", buffer);
  
//  printf("Renvoi de message traité.\n");
  

  /* Mise en attente du programme pour simuler un délai de transmission */
//  sleep(3);
  
//  write(nouv_socket_descriptor, buffer, strlen(buffer)+1);
//  printf("Message envoyé.\n");

//  close(nouv_socket_descriptor);

  return;
}
/*------------------------------------------------------------*/

/*------------------------------------------------------------*/
int main(int argc, char **argv) {
  
  int socket_descriptor,				/* Descripteur de socket */
      nouv_socket_descriptor,			/* [nouveau] descripteur de socket */
      longueur_adresse_courante;		/* Longueur d'adresse courante d'un client */
  sockaddr_in adresse_locale,			/* Structure d'adresse locale */
	      adresse_client_courant;	/* Adresse client courant */
  
  hostent* ptr_hote;				/* Les infos récupérées sur la machine hôte */
  servent* ptr_service;			/* Les infos récupérées sur le service de la machine */
  char machine[TAILLE_MAX_NOM];	/* Nom de la machine locale */
  
  gethostname(machine, TAILLE_MAX_NOM);	/* Récupération du nom de la machine */

	pthread_t nouveau_client;

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
    
	/* Traitement du message */
	printf("reception d'un message.\n");
	if(pthread_create(&nouveau_client, NULL, renvoi,  &nouv_socket_descriptor)){
		perror("problème sur le thread");
		return 1;
	}
  }
  
    close(socket_descriptor);

}
