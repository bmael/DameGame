#include "chat_command.h"

void send_msg_chat(frame f, player * players, int cpt_players){

    display_online_players(cpt_players, players);

    int i;
    for(i=0; i< cpt_players; i++){

          frame f2;
          strcpy(f2.data_type,f.data_type) ;
          strcpy(f2.data , f.data);
          write_to_client(players[i].socket, &f);

    }
}
