#include "chatlistener.h"

#include <QDebug>

ChatListener::ChatListener(int socket_descriptor, QObject *parent) :
    QThread(parent), _socket_descriptor(socket_descriptor), stop(false)
{
    start();
}

void ChatListener::setStop(bool s)
{
    this->stop = s;
}

void ChatListener::run()
{
    //Listen for incoming connections
    //TODO
    while(!stop){

        frame f;
        read_server_information(_socket_descriptor, &f);
        if(strcmp(f.data_type,SEND_MSG_CHAT) == 0){
            qDebug() << "[SEND_MSG_CHAT] : " << f.data;
            emit addMsg(QString::fromStdString(f.data));
        }
    }
}
