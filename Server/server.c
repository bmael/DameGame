/*----------------------------------------------
Server to start before the clients
------------------------------------------------*/




#include "server.h"

void * client_manager_cmd(void * sock){
  int longueur;
  
  /* cast of sock */
  int *tmp = (int*) sock;
  int new_socket_descriptor = *tmp;
  
  for(;;){
    frame f;
    if ( (longueur = read(new_socket_descriptor, &f, sizeof(frame))) <= 0 ) {
      write(1, &f, longueur);
      return;
    }
   

    printf("[Server] : Frame read...\n");
    printf("[Server] : Type : %s\n", f.data_type);
    printf("[Server] : Data : %s\n", f.data);
    
    pthread_mutex_lock(&players_mutex);
    
    /* action : CONNECTION */
    if(strcmp(f.data_type, CONNECT) == 0){
      
      
        connection(&f,
                 players,
                 new_socket_descriptor,
                 &cpt_players,
                 &cpt_max_client);
		
        send_all_players(new_socket_descriptor, players, cpt_players);

        display_online_players(cpt_players, players);
	
    } // END CONNECTION
    
    /* action : DISCONNECTION */
    if(strcmp(f.data_type, DISCONNECT) == 0){
      
        disconnection(&f, players, &cpt_players);
        display_online_players(cpt_players, players);

	
    }// END DISCONNECTION

    /* action : GET_CLIENT_LIST */
    if(strcmp(f.data_type, GET_CLIENT_LIST) == 0){
        send_players_list(new_socket_descriptor, players, cpt_players);
    }

    /* action : SEND_MSG_CHAT */
    if(strcmp(f.data_type, SEND_MSG_CHAT) == 0){
        send_msg_chat(f, players, cpt_players);
    }

    /* action : ASK_NEW_GAME */
    if(strcmp(f.data_type, ASK_NEW_GAME) == 0){

        int j = 0;
        int ok = 0;
        while((!ok) && (j < cpt_players)){
            if(players[j].socket == new_socket_descriptor){ok = 1;}
            else{j++;}
        }

        //search the players on the list
        int i = 0;
        int find = 0;
        while((!find) && (i < cpt_players)){
          if(strcmp(players[i].name, f.data) == 0){find=1;}
          else{i++;}
        }
        if(find){
            send_new_game_request(players[i].socket, players[j]);
        }

    }

    /* action : REJECT_NEW_GAME */
    if(strcmp(f.data_type, REJECT_NEW_GAME) == 0){
        int j = 0;
        int ok = 0;
        while((!ok) && (j < cpt_players)){
            if(players[j].socket == new_socket_descriptor){ok = 1;}
            else{j++;}
        }

        //search the players on the list
        int i = 0;
        int find = 0;
        while((!find) && (i < cpt_players)){
          if(strcmp(players[i].name, f.data) == 0){find=1;}
          else{i++;}
        }
        if(find){
            send_reject_new_game_request(players[i].socket, players[j]);
        }
    }

    /* action : ACCEPT_NEW_GAME */
    if(strcmp(f.data_type, ACCEPT_NEW_GAME) == 0){

        //the player whose accept invitation
        int j = 0;
        int ok = 0;
        while((!ok) && (j < cpt_players)){
            if(players[j].socket == new_socket_descriptor){ok = 1;}
            else{j++;}
        }

        //search the players whose ask to play
        int i = 0;
        int find = 0;
        while((!find) && (i < cpt_players)){
          if(strcmp(players[i].name, f.data) == 0){find=1;}
          else{i++;}
        }
        if(find){
            players[j].color = -1;
            printf("Player %s has %d color\n", players[j].name, players[j].color);
            players[i].color = 1;
                        printf("Player %s has %d color\n", players[i].name, players[i].color);

            send_accept_new_game_request(new_socket_descriptor, players[j], players, cpt_players);
            send_accept_new_game_request(players[i].socket, players[i], players, cpt_players);

            send_opponent(players[i].socket, players[j]);
            send_opponent(players[j].socket, players[i]);
        }
    }

    /* action : OPPONENT_QUIT */
    if(strcmp(f.data_type, OPPONENT_QUIT) == 0){

        //the player whose quit the game
        int j = 0;
        int ok = 0;
        while((!ok) && (j < cpt_players)){
            if(players[j].socket == new_socket_descriptor){ok = 1;}
            else{j++;}
        }

        //the player to advise
        int i = 0;
        int find = 0;
        while((!find) && (i < cpt_players)){
          if(strcmp(players[i].name, f.data) == 0){find=1;}
          else{i++;}
        }
        if(find){

            players[j].color = 0;
            players[i].color = 0;

            advise_opponent_quit(players[i].socket, players[j]);
            frame f2;
            strcpy(f2.data_type, CLIENT_FREE);
            memcpy(f2.data, &players[i], sizeof(players[i]));
            alert_all_client(&f2, cpt_players, players);

        }

    }
    
        /* action : OPPONENT_QUIT */
    if(strcmp(f.data_type, SEND_GAMEBOARD) == 0){
      
        //char tmp[sizeof(checkerboard)];
	board_frame bf = *((board_frame *)f.data);
	
	frame f2;
	strcpy(f2.data_type, SEND_GAMEBOARD);
	memcpy(f2.data, &bf.board, sizeof(bf.board));
	write_to_client(bf.receiver.socket, &f2);
	
    }

    pthread_mutex_unlock(&players_mutex);

    
  }

  close(new_socket_descriptor);

}







/*------------------------------------------------------------*/

/*------------------------------------------------------------*/
int main(int argc, char **argv) {
  
  int socket_descriptor,		/* Descripteur de socket */
      new_socket_descriptor,		/* [nouveau] descripteur de socket */
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
  printf("Size of player : %lu", sizeof(player));
  players = malloc(cpt_max_client * sizeof(player));
	
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
    if ( (new_socket_descriptor = accept(socket_descriptor,
                                          (sockaddr*)(&adresse_client_courant),
                                          &longueur_adresse_courante)) < 0 ) {
      perror("[Server] : Impossible to accept the connection with the client.");
      exit(1);
    }
    
    /* Creating a thread for this client */
    if(pthread_create(&nouveau_client, NULL, client_manager_cmd, &new_socket_descriptor)){
        perror("[Server] : Problem on the thread");
		return 1;
	}
	
  }
  
    close(socket_descriptor);
    free(players);

}
