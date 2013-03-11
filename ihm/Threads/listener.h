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
    void pseudoAlreadyExists(QString);

    void addMsg(QString);

    void addPlayerToView(player p);
    void removePlayerFromView(player p);

    void advisePlayerForGame(QString n);
    void advisePlayerForAbortedGame(QString n);
    void clientBusy(player p);
    void clientFree(player p);
    void startGame();

    void setOpponent(player p);
    void opponentQuit(player p);

    void receiveCheckerboard(checkerboard c);
    void receiveWinner(player p);


public slots:

protected:
    virtual void run();

private:
    void addPlayer(player p);
    void removePlayer(player p);

    void setClientBusy(player p);



private:
    int _socket_descriptor;
    bool stop;

    QList<player> players;
    
};

#endif // LISTENER_H
