#ifndef COMMAND_H
#define COMMAND_H

#define CONNECT             "0000"
#define DISCONNECT          "0001"

#define PSEUDO_ALREADY_EXISTS "0002"

#define INCOMING_CONNECTION "0003"
#define GET_NB_CLIENT       "0004"
#define SEND_NB_CLIENT      "0005"
#define GET_CLIENT_LIST     "0006"
#define SEND_CLIENT_LIST    "0007"
#define ADD_CLIENT          "0008"
#define REMOVE_CLIENT       "0009"

#define SEND_MSG_CHAT       "000A"

#define ASK_NEW_GAME        "000B"
#define SEND_NEW_GAME_REQUEST "000C"

#define REJECT_NEW_GAME     "000D"
#define SEND_REJECT_NEW_GAME_REQUEST    "000E"

#define ACCEPT_NEW_GAME     "000F"
#define SEND_ACCEPT_NEW_GAME_REQUEST "0010"
#define CLIENT_BUSY         "0011"
#define SEND_OPPONENT       "0012"

#define OPPONENT_QUIT       "0013"
#define ADVISE_OPPONENT_QUIT "0014"
#define CLIENT_FREE         "0015"

#define SEND_GAMEBOARD      "0016"


#endif
