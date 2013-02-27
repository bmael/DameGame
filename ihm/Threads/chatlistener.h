#ifndef CHATLISTENER_H
#define CHATLISTENER_H

#include <QThread>

#ifdef __cplusplus
extern "C" {
#include "../DameGame/include/client.h"
}
#endif

class ChatListener : public QThread
{
    Q_OBJECT
public:
    explicit ChatListener(int socket_descriptor, QObject *parent = 0);
    
    void setStop(bool s);

signals:
    void addMsg(QString);

public slots:

protected:
    virtual void run();

private:
    int _socket_descriptor;
    bool stop;
    
};

#endif // CHATLISTENER_H
