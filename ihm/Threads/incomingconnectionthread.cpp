#include "incomingconnectionthread.h"
#include <QDebug>

IncomingConnectionThread::IncomingConnectionThread(int socket_descriptor, QObject *parent):
    QThread(parent), _socket_descriptor(socket_descriptor), stop(false)
{
    start();
}

IncomingConnectionThread::~IncomingConnectionThread()
{
    exit();
    wait();
}

void IncomingConnectionThread::setStop(bool s)
{
    this->stop = s;
}

void IncomingConnectionThread::run()
{
    //Listen for incoming connections
    //TODO
    while(!stop){
        frame f ;
        read_server_information(_socket_descriptor, &f);
        if(strcmp(f.data_type,INCOMING_CONNECTION) == 0){
            qDebug() << "[Incoming connection] : " << f.data;
        }
    }
}
