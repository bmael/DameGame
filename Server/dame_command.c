#include "dame_command.h"

void send_players_list(int socket_descriptor, player * players, int cpt_players){

    frame f;
    strcpy(f.data_type,GET_CLIENT_LIST);
    strcpy(f.data, (char*) players);

    printf("[Send_players_list] : sending players list on socket : %d\n", socket_descriptor);
    printf("[Send_players_list] : data sent : %s", f.data);

        //JUST WHY ??????????????

    write_to_client(socket_descriptor, &f);
}


void send_nb_players(int socket_descriptor, int cpt_players){

    /* convert (char*) to int */
    char nbClient[100];
    sprintf(nbClient, "%d", cpt_players);

    frame f;
    strcpy(f.data_type, GET_NB_CLIENT);
    strcpy(f.data, nbClient);

    printf("[Send_nb_players] : sending the nulber of players on socket : %d\n", socket_descriptor);

    write_to_client(socket_descriptor, &f);

}
