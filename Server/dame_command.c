#include "dame_command.h"

void send_players_list(int socket_descriptor, player * players, int cpt_players){

    frame f;
    strcpy(f.data_type,SEND_CLIENT_LIST);
    strcpy(f.data, (char*) players);

    printf("[Send_players_list] : sending players list on socket : %d\n", socket_descriptor);
    printf("[Send_players_list] : data sent : %s\n", f.data);

    write_to_client(socket_descriptor, &f);
}


void send_nb_players(int socket_descriptor, int cpt_players){

    /* convert (char*) to int */
    char nbClient[100];
    sprintf(nbClient, "%d", cpt_players);

    frame f;
    strcpy(f.data_type, SEND_NB_CLIENT);
    strcpy(f.data, nbClient);

    printf("[Send_nb_players] : sending the number of players on socket : %d\n", socket_descriptor);

    write_to_client(socket_descriptor, &f);

}

void send_player(int socket_descriptor, player p){
    frame f;
    strcpy(f.data_type, ADD_CLIENT);
    memcpy(f.data, &p, sizeof(p));

    printf("[Send_player] : %s", f.data);

    write_to_client(socket_descriptor, &f);
}

void send_all_players(int socket_descriptor, player * players, int cpt_players){
    int i;
    for(i=0;i<cpt_players;i++){
        send_player(socket_descriptor, players[i]);
    }
}

void send_new_game_request(int socket_descriptor, player from){

    frame f;
    strcpy(f.data_type, SEND_NEW_GAME_REQUEST);
    strcpy(f.data, from.name);
    write_to_client(socket_descriptor, &f);

}

void send_reject_new_game_request(int socket_descriptor, player from){
    frame f;
    strcpy(f.data_type, SEND_REJECT_NEW_GAME_REQUEST);
    strcpy(f.data, from.name);
    write_to_client(socket_descriptor, &f);
}

void send_accept_new_game_request(int socket_descriptor, player from, player * players, int cpt_players){
    frame f;
    strcpy(f.data_type, SEND_ACCEPT_NEW_GAME_REQUEST);
    memcpy(f.data, &from, sizeof(from));
    write_to_client(socket_descriptor, &f);

    frame f2;
    strcpy(f.data_type, CLIENT_BUSY);
    memcpy(f.data, &from, sizeof(from));
    alert_all_client(&f, cpt_players, players);
}

void send_opponent(int socket_descriptor, player opponent){
    frame f;
    strcpy(f.data_type, SEND_OPPONENT);
    memcpy(f.data, &opponent, sizeof(opponent));
    write_to_client(socket_descriptor, &f);
}

void advise_opponent_quit(int socket_descriptor, player quit){
    frame f;
    strcpy(f.data_type, ADVISE_OPPONENT_QUIT);
    memcpy(f.data, &quit, sizeof(quit));
    write_to_client(socket_descriptor, &f);

}

