#include "client.h"




void init_host(hostent * ptr_host, char * host, sockaddr_in *local_addr){

    if((ptr_host = gethostbyname(host)) == NULL ){
            perror("[init_host] : can't find the server with the given host");
            exit(1);
        }
        bcopy((char*)ptr_host->h_addr, (char*)&local_addr->sin_addr, ptr_host->h_length);
        local_addr->sin_family = AF_INET; // or ptr_host->h_addrtype;
}

void assign_port(sockaddr_in *local_addr, int port){
    local_addr->sin_port = htons(port);
}

int create_socket(){
    int socket_descriptor;
    if((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("[create_socket] : Can't create the connection server socket.");
        exit(1);
    }
    return socket_descriptor;

}

void server_connection(int socket_descriptor, sockaddr_in local_addr){
    if(connect(socket_descriptor, (sockaddr*)(&local_addr), sizeof(local_addr)) < 0){
        perror("[server_connection] : can't establish a connection with the server");
        exit(1);
    }   
}

void server_disconnection(int socket_descriptor){
    close(socket_descriptor);
}



void write_to_server(int socket_descriptor, frame * f){
    if((write(socket_descriptor, (char*) f, sizeof(frame))) < 0){
        perror("[write_to_server] : can't send the message to the server.");
        exit(1);
    }
}


frame read_server_information(int socket_descriptor){
    char buffer[sizeof(frame)];
    int length;
    if((length = read(socket_descriptor, buffer, sizeof(frame))) > 0){
        printf("answer of the server : \n");
        write(1, buffer, length);
    }

    frame f;
    f = *(frame *)buffer;

    return f;
}

void * listen_server_instruction(void *s){
      int length;

      printf("[listen_server_instruction]\n");

      /* cast */
      for_listen_server *for_server = (for_listen_server *) s;
      int new_socket_descriptor = for_server->socket_desc;
      player * players = for_server->players;

      int nbCLient;

      for(;;){
        char buffer[sizeof(frame)];
        if ( (length = read(new_socket_descriptor, buffer, sizeof(frame))) <= 0 ) {
          write(1, buffer, length);
          return;
        }

        frame f;
        f = *(frame *)buffer;


        /* action : INCOMING_CONNECTION */
        if(strcmp(f.data_type, INCOMING_CONNECTION) == 0){
            nbCLient = atoi(f.data);
            frame f2 = make_frame(f.dest,f.src,GET_CLIENT_LIST,"");
            write_to_server(new_socket_descriptor, &f2);
            printf("Command : %s, Value : %d", GET_NB_CLIENT, nbCLient);
        }

        /* action : GET_NB_CLIENT */
        if(strcmp(f.data_type, GET_NB_CLIENT) == 0){
            nbCLient = atoi(f.data);
            frame f2 = make_frame(f.dest,f.src,GET_CLIENT_LIST,"");
            write_to_server(new_socket_descriptor, &f2);
            printf("Command : %s, Value : %d", GET_NB_CLIENT, nbCLient);
        }

        /* action : GET_CLIENT_LIST */
        if(strcmp(f.data_type, GET_CLIENT_LIST) == 0){
            players = (player *) f.data;
            display_online_players(players, nbCLient);
        }


      }
}

void display_online_players(player * players, int size){

  printf("Players Online\n");
  printf("---------------\n");

  int i;
  for(i=0; i<size; i++){
   printf("-- %s\n",players[i].name);
  }


}


