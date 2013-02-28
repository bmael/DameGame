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

int server_connection(int socket_descriptor, sockaddr_in local_addr){
    int res = -1;
    if((res = connect(socket_descriptor, (sockaddr*)(&local_addr), sizeof(local_addr))) < 0){
        perror("[server_connection] : can't establish a connection with the server");
        //exit(1);
    }   
    return res;
}

void server_disconnection(int socket_descriptor){
    close(socket_descriptor);
}



void write_to_server(int socket_descriptor, frame * f){
    if((write(socket_descriptor, f, sizeof(frame))) < 0){
        perror("[write_to_server] : can't send the message to the server.");
        exit(1);
    }
    //memset(f, 0, sizeof(f));
}


int read_server_information(int socket_descriptor, frame * f){

    int length;
    if((length = read(socket_descriptor, f, sizeof(frame))) <= 0){
        perror("[read_server_information] : Can't read the frame.");
        //exit(1);
    }


    return length;
}

void * listen_server_instruction(void *s){
//      int length;

      /* cast */     
      players_client_thread *tmp = (players_client_thread *) s;
      players_client_thread _players = *tmp;

      for(;;){

//        while ( (length = read(_players.me.socket, &f, sizeof(frame))) > 0 ) {
//            write(1, &f, length);
//        }

//        if ( (length = read(_players.me.socket, &f, sizeof(frame))) <= 0 ) {
//            perror("[Listen_server_instruction] : can't read the frame.");
//            exit(1);
//        }
          printf("Info player me : %s", _players.me.name);
        frame f;
        read_server_information(_players.me.socket, &f);

//        /* action : INCOMING_CONNECTION */
//        if(strcmp(f.data_type, INCOMING_CONNECTION) == 0){
//            nbCLient = atoi(f.data);
//            frame f2 = make_frame(f.dest,f.src,GET_CLIENT_LIST,"");
//            write_to_server(new_socket_descriptor, &f2);
//            printf("Command : %s, Value : %d", GET_NB_CLIENT, nbPlayers);
//        }

        /* action : GET_NB_CLIENT */
        if(strcmp(f.data_type, GET_NB_CLIENT) == 0){

            _players.nbPlayers = atoi(f.data);

            printf("[Listen_server_instruction] : GET_NB_CLIENT %d\n", _players.nbPlayers);

//            frame f2 = make_frame(f.dest,f.src,GET_CLIENT_LIST,"");
            frame f2;
            memset(&f2, 0, sizeof(frame));
            strcpy(f2.data_type, GET_CLIENT_LIST);
            write_to_server(_players.me.socket, &f2);


        }

        /* action : GET_CLIENT_LIST */
        if(strcmp(f.data_type, GET_CLIENT_LIST) == 0){
            printf("[Listen_server_instruction] : GET_CLIENT_LIST %s\n", f.data);
            //memcpy(_players.other_players, f.data, _players.nbPlayers * sizeof(player));
            player * tmpplayers = calloc(_players.nbPlayers, sizeof(player));
            memcpy(tmpplayers, f.data, _players.nbPlayers * sizeof(player));

           printf("other players : %s",(char*)_players.other_players);
//            printf("[thread] : other players : %s", tmpplayers[0].name);
//           printf("nbPOlayers : %d", _players.nbPlayers);
           //printf("player : %s", _players.other_players[0].name);
           //display_online_players(_players.other_players, _players.nbPlayers);
        }

        /* action : GET_CLIENT_LIST */
        if(strcmp(f.data_type, SEND_MSG_CHAT) == 0){
            printf("[Listen_server_instruction] : SEND_MSG_CHAT %s\n", f.data);

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


