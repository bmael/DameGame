#include "incomingconnectionthread.h"
#include <QDebug>

IncomingConnectionThread::IncomingConnectionThread(int socket_descriptor, QObject *parent):
    QThread(parent), _socket_descriptor(socket_descriptor)
{
    start();
}

IncomingConnectionThread::~IncomingConnectionThread()
{
    exit();
    wait();
}

void IncomingConnectionThread::run()
{
    //Listen for incoming connections
    //TODO
    for(;;){
        qDebug() << "[IncomingConnectionThread]" <<
                QString::fromStdString(read_server_information(_socket_descriptor)).toUtf8();
    }
}
