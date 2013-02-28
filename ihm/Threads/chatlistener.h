#ifndef CHATLISTENER_H
#define CHATLISTENER_H

#include <QThread>
#include <QMutex>

#ifdef __cplusplus
extern "C" {
#include "../DameGame/include/client.h"
}
#endif

class ChatListener : public QThread
{
    Q_OBJECT
public:
    explicit ChatListener(int socket_descriptor, QMutex * mutex, QObject *parent = 0);
    
    void setStop(bool s);

signals:
    void addMsg(QString);

public slots:

protected:
    virtual void run();

private:
    int _socket_descriptor;
    bool stop;
    QMutex * mutex;
    
};

#endif // CHATLISTENER_H
