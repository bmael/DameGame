#include "listener.h"

#include <QDebug>
#include <QMessageBox>

Listener::Listener(int socket_descriptor, QObject *parent) :
    QThread(parent), _socket_descriptor(socket_descriptor), stop(false)
{
    qRegisterMetaType<player>("player");
    qRegisterMetaType<checkerboard>("checkerboard");

    start();
}

void Listener::setStop(bool s)
{
    this->stop = s;
    this->players.clear();
}

void Listener::run()
{
    while(!stop){

        frame f;
        read_server_information(_socket_descriptor, &f);

        if(strcmp(f.data_type,PSEUDO_ALREADY_EXISTS) == 0){
            qDebug() << "[PSEUDO_ALREADY_EXISTS] : " << f.data;
            emit pseudoAlreadyExists(QString::fromStdString(f.data));
        }

        if(strcmp(f.data_type,SEND_MSG_CHAT) == 0){
            qDebug() << "[SEND_MSG_CHAT] : " << f.data;
            emit addMsg(QString::fromStdString(f.data));
        }

        if(strcmp(f.data_type,ADD_CLIENT) == 0){
           qDebug() << "[ADD_CLIENT] : " << f.data;
           player ps = *((player *)f.data);
           addPlayer(ps);
       }

        if(strcmp(f.data_type,REMOVE_CLIENT) == 0){
           qDebug() << "[REMOVE_CLIENT] : " << f.data;
           player ps = *((player *)f.data);
           removePlayer(ps);
       }

        if(strcmp(f.data_type,SEND_NEW_GAME_REQUEST) == 0){
            qDebug() << "[ASK_GAME]";
            emit advisePlayerForGame(QString::fromStdString(f.data));
       }

        if(strcmp(f.data_type,SEND_REJECT_NEW_GAME_REQUEST) == 0){
            qDebug() << "[REJECT_GAME]";
            emit advisePlayerForAbortedGame(QString::fromStdString(f.data));
       }

        if(strcmp(f.data_type,SEND_ACCEPT_NEW_GAME_REQUEST) == 0){
            qDebug() << "[ACCEPT_GAME]";
            emit startGame();
       }

        if(strcmp(f.data_type,CLIENT_BUSY) == 0){
            qDebug() << "[Client_busy] : " << f.data;
            setClientBusy(*((player *)f.data));
       }

        if(strcmp(f.data_type,SEND_OPPONENT) == 0){
            qDebug() << "[SEND_OPPONENT] : " << f.data;
            emit setOpponent(*((player *)f.data));
       }

        if(strcmp(f.data_type,ADVISE_OPPONENT_QUIT) == 0){
            qDebug() << "[OPPONENT_QUIT] : " << f.data;
           emit opponentQuit(*((player *)f.data));
       }

        if(strcmp(f.data_type,CLIENT_FREE) == 0){
            qDebug() << "[CLIENT_FREE] : " << f.data;
           emit clientFree(*((player *)f.data));
       }

        if(strcmp(f.data_type,SEND_GAMEBOARD) == 0){
            qDebug() << "[SEND_GAMEBOARD] : " << f.data;
           emit receiveCheckerboard(*((checkerboard*)f.data));
       }

    }
}

void Listener::addPlayer(player p)
{
    players.append(p);
    emit addPlayerToView(p);

}

void Listener::removePlayer(player p)
{
    bool isFind = false;
    int i = 0;
    while(!isFind && i < players.size()){
        if( strcmp(players.at(i).name, p.name) == 0 ){
            isFind = true;
            break;
        }
        i++;
    }

    players.removeAt(i);
    emit removePlayerFromView(p);

}

void Listener::setClientBusy(player p)
{
    bool isFind = false;
    int i = 0;
    while(!isFind && i < players.size()){
        if( strcmp(players.at(i).name, p.name) == 0 ){
            isFind = true;
            break;
        }
        i++;
    }

    emit clientBusy(p);

}

