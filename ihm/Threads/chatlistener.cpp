#include "chatlistener.h"

#include <QDebug>

ChatListener::ChatListener(int socket_descriptor, QMutex *mutex, QObject *parent) :
    QThread(parent), _socket_descriptor(socket_descriptor), stop(false)
{
    this->mutex = mutex;
    start();
}

void ChatListener::setStop(bool s)
{
    this->stop = s;
}

void ChatListener::run()
{
    while(!stop){

        mutex->lock();
        frame f;
        qDebug() << "[Chat_listener]";
        read_server_information(_socket_descriptor, &f);
        if(strcmp(f.data_type,SEND_MSG_CHAT) == 0){
            qDebug() << "[SEND_MSG_CHAT] : " << f.data;
            emit addMsg(QString::fromStdString(f.data));
        }
        memset(&f, 0, sizeof(f));
        mutex->unlock();
    }
}
