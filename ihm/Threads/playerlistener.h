#ifndef PLAYERLISTENER_H
#define PLAYERLISTENER_H

#ifdef __cplusplus
extern "C" {
#include "../DameGame/include/client.h"
}
#endif

#include <QThread>

class PlayerListener : public QThread
{
    Q_OBJECT
public:
    explicit PlayerListener(int socketDescriptor, QObject *parent = 0);

    void setStop(bool s);

signals:
    
public slots:

protected:
    virtual void run();

private:
    void addPlayer(player p);

private:
    int _socket_descriptor;
    bool stop;
    int _nbPlayers;
    QList<player> players;
};

#endif // PLAYERLISTENER_H
