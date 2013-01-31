#ifndef INCOMINGCONNECTIONTHREAD_H
#define INCOMINGCONNECTIONTHREAD_H

#include <QThread>

#ifdef __cplusplus
extern "C" {
#include "../DameGame/client.h"
}
#endif


class IncomingConnectionThread : public QThread
{
public:
    IncomingConnectionThread(int socket_descriptor, QObject* parent = NULL);
    virtual ~IncomingConnectionThread();

protected:
    virtual void run();

private:
    int _socket_descriptor;
};

#endif // INCOMINGCONNECTIONTHREAD_H
