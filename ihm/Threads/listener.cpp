#include "listener.h"

#include <QDebug>
#include <QMessageBox>

Listener::Listener(int socket_descriptor, QObject *parent) :
    QThread(parent), _socket_descriptor(socket_descriptor), stop(false)
{
    qRegisterMetaType<player>("player");
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
            emit clientBusy(*((player *)f.data));
       }

    }
}

void Listener::addPlayer(player p)
{
    qDebug() << "[Player_listener] : add player : " << p.name;
    players.append(p);
    emit addPlayerToView(p);

}

void Listener::removePlayer(player p)
{
    qDebug() << "[Player_listener] : remove player : " << p.name;
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

