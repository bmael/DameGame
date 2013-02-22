#ifndef INCOMINGCONNECTIONTHREAD_H
#define INCOMINGCONNECTIONTHREAD_H

#include <QThread>

#ifdef __cplusplus
extern "C" {
#include "../DameGame/include/client.h"
}
#endif


class IncomingConnectionThread : public QThread
{
public:
    IncomingConnectionThread(int socket_descriptor, QObject* parent = 0);
    virtual ~IncomingConnectionThread();

    void setStop(bool s);

protected:
    virtual void run();

private:
    int _socket_descriptor;
    bool stop;
};

#endif // INCOMINGCONNECTIONTHREAD_H
