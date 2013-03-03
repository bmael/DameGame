#include "listener.h"

#include <QDebug>

Listener::Listener(int socket_descriptor, QObject *parent) :
    QThread(parent), _socket_descriptor(socket_descriptor), stop(false)
{
    qRegisterMetaType<player>("player");
    start();
}

void Listener::setStop(bool s)
{
    this->stop = s;
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

    }
}

void Listener::addPlayer(player p)
{
    qDebug() << "[Player_listener] : add player : " << p.name;
    players.append(p);
    emit addPlayerToView(p);

}
