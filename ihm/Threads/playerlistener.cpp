#include "playerlistener.h"

#include <QDebug>

PlayerListener::PlayerListener(int socketDescriptor, QObject *parent) :
    QThread(parent), _socket_descriptor(socketDescriptor), stop(false), _nbPlayers(0)
{
    start();
}

void PlayerListener::setStop(bool s)
{
    this->stop = s;
}

void PlayerListener::run()
{
    qDebug() << "Thread started";

    while(!stop){

        frame f ;
        read_server_information(_socket_descriptor, &f);
        if(strcmp(f.data_type,ADD_CLIENT) == 0){
           qDebug() << "[Player_listner] : " << f.data;
           player ps = *(player *)f.data;
           addPlayer(ps);
       }

    }
}

void PlayerListener::addPlayer(player p)
{
    qDebug() << "[Player_listener] : add player : " << p.name;
    players.append(p);

}
