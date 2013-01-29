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

int main(int argc, char **argv){
	
	int socket_descriptor, 	// descripteur de socket
		longueur;			// longueur d'un buffer utilisé
	sockaddr_in adresse_locale; // adresse de socket local
	hostent *ptr_host; 		// info sur une machine hote
	servent *ptr_service;	// info sur un service
	char buffer[256];
	char *prog;				// nom du programme
	char *host;				// nom de la machine distante
	char *mesg;				// message envoyé

	if(argc!=3){
		perror("usage : client <adresse-serveur> <message-a-transmettre>");
		exit(1);
	}

	prog = argv[0];
	host = argv[1];
	mesg = argv[2];

	printf("nom de l'executable : %s \n", prog);
	printf("adresse du serveur : %s \n", host);
	printf("message envoyé : %s \n", mesg);

	if((ptr_host = gethostbyname(host)) == NULL ){
		perror("impossible de trouver le serveur à partir de son adresse.");
		exit(1);
	}
	
	    printf("[init_host] : %s\n", ptr_host->h_addr);


	/* Copie caractère par caractère des info de ptr_host vers adresse_locale */
	bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
	adresse_locale.sin_family = AF_INET; // ou ptr_host->h_addrtype;

	/* 2 façons de définir le service que l'on va utiliser à distance (le même 
	     que sur le serveur)
	*/
	/***************************************************************************
		Solution 1
	***************************************************************************/
/*	if((ptr_service = getservbyname("irc","tcp")) == NULL){
		perror("erreur : impossible de récupérer le numéro de port du service désiré");
		exit(1);
	}
	adresse_locale.sin_port = htons(ptr_service->s_port);
*/
	/**************************************************************************/
	/***************************************************************************
		Solution 2
	***************************************************************************/
	adresse_locale.sin_port = htons(5000);

	/**************************************************************************/

	printf("numéro de port pour la connexion au serveur : %d \n", ntohs(adresse_locale.sin_port));

	/* Création de la socket */
	if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("erreur : impossible de créer la socket de connexion avec le serveur.");
		exit(1);
	}

	/* Tentative de connexion au serveur dont les infos sont dans l'adresse locale */
	if((connect(socket_descriptor, (sockaddr*)(&adresse_locale), sizeof(adresse_locale))) < 0){
		perror("erreur : impossible de se connecter au serveur.");
		exit(1);
	}

	printf("connexion établie avec le serveur. \n");
	printf("envoi du message au serveur.\n");

	/* Envoi du message vers le serveur */
	if((write(socket_descriptor, mesg, strlen(mesg))) < 0){
		perror("erreur : impossible d'écrire le message destiné au serveur.");
		exit(1);
	}

	sleep(3);

	printf("message envoyé au serveur. \n");

	/* Lecture de la réponse en provenance du serveur */
	while((longueur = read(socket_descriptor, buffer, sizeof(buffer))) > 0){
		printf("réponse du serveur : \n");
		write(1, buffer, longueur);
	}

	printf("\n fin de la récéption. \n");

	close(socket_descriptor);

	printf("connexion avec le serveur fermée, fin du programme.\n");

	exit(0);
}