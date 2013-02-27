#include "basic_command.h"

// Reallocation of memory for players and sockets.
void memory_reallocation( player *players,
                          int *cpt_max_client){

    printf("[Memory reallocation] : value of max_client is %d\n",*cpt_max_client);
    *cpt_max_client += 1;
    *cpt_max_client *= 2;
    printf("[Memory reallocation] : new value of max_client is %d\n",*cpt_max_client);

    if(realloc(players, *cpt_max_client * sizeof(player)) == 0){
        perror("[Memory reallocation] : can't (re)allocate memory block for sockets...\n");
        exit(1);
    }
}

void write_to_client(int socket_descriptor, frame *f){
    printf("[write_to_client] : sending : %s - %s to %d\n", f->data_type, f->data, socket_descriptor);
      if((write(socket_descriptor, f, sizeof(frame))) < 0){
        perror("[write_to_client] : can't send the message to the client.");
        exit(1);
    }
//    memset(f,0,sizeof(f));
}

// Displays the online players on the standard output.
void display_online_players(int cpt_players, player * players){

    printf("[Display_online_players]\n");

    printf("\tName           | socket\n");
    printf("\t---------------|---------------\n");

    int i;
    for(i=0; i<cpt_players; i++){
     printf("\t%s",players[i].name);
     printf("\t\t%d\n",players[i].socket);
    }

}

// Process for command CONNECTION.
void connection(frame * f,
                player *players,
                int socket_descriptor,
                int *cpt_players,
                int *cpt_max_client){

    printf("[Connection] : adding client...\n");

    // Reallocation of memory if needed
    if((*cpt_players) == *cpt_max_client-1){
        printf("[Connection] : need memory reallocation...\n");
        memory_reallocation(players, cpt_max_client);
    }

    player to_add;
    memcpy(to_add.name, f->data, 10);
    to_add.socket = socket_descriptor;

    players[*cpt_players] = to_add;

    *cpt_players += 1;

    printf("[Connection] : players array updated\n");

    //send_nb_client(new_socket_descriptor);

    //alert_all_client(CONNECT, *cpt_players, players);

}

// Process for a client disconnection
void disconnection(frame *f, player * players, int *cpt_players){
    printf("[Disconnection] : removing a client.....\n");

    //search the players on the list
    int i = 0;
    int find = 0;
    while((!find) && (i < *cpt_players)){
      if(strcmp(players[i].name, f->data) == 0){find=1;}
      else{i++;}
    }

    if(find){
      //delete the player from the list
      int j;
      for(j = i; j < (*cpt_players)-1; j++){
        players[j] = players[j+1];
      }

      *cpt_players -= 1;
    }

}

// Advise all the connected players of an event
void alert_all_client(char * command, int cpt_players, player * players){

  int i;
  for(i = 0; i<cpt_players; i++){

    if(strcmp(command, CONNECT) == 0){

      frame f;
      strcpy(f.data_type,INCOMING_CONNECTION) ;
      strcpy(f.data , players[cpt_players-1].name);
      write_to_client(players[cpt_players-1].socket, &f);

    }

  }
}

