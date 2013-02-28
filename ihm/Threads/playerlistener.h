#ifndef PLAYERLISTENER_H
#define PLAYERLISTENER_H

#ifdef __cplusplus
extern "C" {
#include "../DameGame/include/client.h"
}
#endif

#include <QThread>
#include <QMutex>

class PlayerListener : public QThread
{
    Q_OBJECT
public:
    explicit PlayerListener(int socketDescriptor, QMutex *mutex, QObject *parent = 0);

    void setStop(bool s);

signals:
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
    QMutex * mutex;
};

#endif // PLAYERLISTENER_H
