/*----------------------------------------------
Serveur à lancer avant le client
------------------------------------------------*/




#include "server.h"







void send_nb_client(int socket_descriptor){
//  in_addr address;
//  address.s_addr=inet_addr("127.0.0.1");
  
//  char nbClient[100];
//  sprintf(nbClient, "%d", cpt_players);
  
//  frame f = make_frame(address, address,GET_NB_CLIENT, nbClient );
//  printf("sending information to the client...\n");
//  write_to_client(socket_descriptor, &f);
//  printf("Information sent : %s", f.data);
  
}



void * client_manager_cmd(void * sock){
  int longueur;
  
  /* cast of sock */
  int *tmp = (int*) sock;
  int new_socket_descriptor = *tmp;
  
  for(;;){
    char buffer[sizeof(frame)];
    if ( (longueur = read(new_socket_descriptor, buffer, sizeof(frame))) <= 0 ) {
      write(1, buffer, longueur);
      return;
    }
   
    frame f;
    f = *(frame *)buffer;
    printf("[Server] : Frame read...\n");
    printf("[Server] : Type : %s\n", f.data_type);
    printf("[Server] : Data : %s\n", f.data);
    
    
    /* action : CONNECTION */
    if(strcmp(f.data_type, CONNECT) == 0){
      
      	pthread_mutex_lock(&players_mutex);
      
        connection(&f,
                 players,
                 new_socket_descriptor,
                 &cpt_players,
                 cpt_max_client);
		
        pthread_mutex_unlock(&players_mutex);

        display_online_players(cpt_players, players);

	
    } // END CONNECTION
    
    /* action : DISCONNECTION */
    if(strcmp(f.data_type, DISCONNECT) == 0){
      
	pthread_mutex_lock(&players_mutex);

    disconnection(&f, players, &cpt_players);
	
	pthread_mutex_unlock(&players_mutex);
    display_online_players(cpt_players, players);

	
    }// END DISCONNECTION
    
    /* action : GET_CLIENT_LIST */
    if(strcmp(f.data_type, GET_CLIENT_LIST) == 0){
        in_addr address;
	address.s_addr=inet_addr("127.0.0.1");
  
       frame f = make_frame(address, address,GET_CLIENT_LIST, (char*) players);
       write_to_client(new_socket_descriptor, &f);
    }

    
    
  }

  close(new_socket_descriptor);

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
  pthread_t nouveau_client;	/* Thread for each client */

  printf("Server name : %s\n",machine);

  /* Allocation of memory for players */
  players = calloc(cpt_max_client, sizeof(player));
	
  /* Récupération de la structure d'adresse en récupérant le nom */
  if ( (ptr_hote = gethostbyname(machine)) == NULL ) {
      perror("[Server] : can't find the server with its name");
    exit(1);
  }
  
  /* Copy ptr_hote to adresse_locale */
  bcopy((char*)ptr_hote->h_addr, (char*)&adresse_locale.sin_addr, ptr_hote->h_length);
  adresse_locale.sin_family = ptr_hote->h_addrtype;	/* or AF_INET */
  adresse_locale.sin_addr.s_addr = INADDR_ANY;	/* or AF_INET */
  
  /* Use the port define by the macro PORT or the custom port typed by the user */
  int port = PORT;
  if(argc > 1){
    port = atoi(argv[1]);
  } 
  adresse_locale.sin_port = htons(port);
    
  printf("[Server] : Using port : %d \n", ntohs(adresse_locale.sin_port));
  
  /* Creating socket*/
  if ( (socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
      perror("[Server] : Can't create the connection socket with the client.");
      exit(1);
  }
  
  /* Binding the socket descriptor */
  if ( (bind(socket_descriptor,
             (sockaddr*)(&adresse_locale),
             sizeof(adresse_locale))) < 0 ){
    perror("[Server] : Can't bind the socket with the connection address.");
    exit(1);
  }
  
  /* Initialisation de la file d'écoute */
  listen(socket_descriptor,5);
  
  /* Attente des connexions et traitement des données reçues */
  for (;;) {
    longueur_adresse_courante = sizeof(adresse_client_courant);
    /* adresse_client_courant sera renseigné par accept via les infos du connect */
    if ( (nouv_socket_descriptor = accept(socket_descriptor,
                                          (sockaddr*)(&adresse_client_courant),
                                          &longueur_adresse_courante)) < 0 ) {
      perror("[Server] : Impossible to accept the connection with the client.");
      exit(1);
    }
    
	/* Adding the client to players */
	if(pthread_create(&nouveau_client, NULL, client_manager_cmd, &nouv_socket_descriptor)){
        perror("[Server] : Problem on the thread");
		return 1;
	}
	
	

  }
  
    close(socket_descriptor);

}
