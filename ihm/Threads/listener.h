#ifndef LISTENER_H
#define LISTENER_H

#include <QThread>

#ifdef __cplusplus
extern "C" {
#include "../DameGame/include/client.h"
}
#endif

class Listener : public QThread
{
    Q_OBJECT
public:
    explicit Listener(int socket_descriptor, QObject *parent = 0);
    
    void setStop(bool s);

signals:
    void addMsg(QString);
    void addPlayerToView(player p);

public slots:

protected:
    virtual void run();

private:
    void addPlayer(player p);

private:
    int _socket_descriptor;
    bool stop;

    QList<player> players;
    
};

#endif // LISTENER_H
