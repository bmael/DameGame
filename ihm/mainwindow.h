#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Threads/incomingconnectionthread.h"
#include "Threads/chatlistener.h"
#include "Threads/playerlistener.h"

#ifdef __cplusplus
extern "C" {
#include "../DameGame/include/client.h"
}
#endif

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void serverConnection(QString host, int port, QString pseudo);
    void serverDisconnection();

    void on_actionQuit_triggered();
    void on_showHidePushButton_clicked();
    void sendChatMessage(QString msg);
    void addMsg(QString msg);

signals:
    void askAddMsg(QString);

private:
    Ui::MainWindow *ui;
    bool _rightMenuHidden;

    //Client attributes
    int _socket_descriptor;     // descriptor of socket
    sockaddr_in _local_addr;    // local adress of the client
    hostent *_ptr_host; 		// information about host machine
    servent *_ptr_service;      // information about a service

    players_client_thread _players;
    int _nbPlayerMax;   // the number of online players
    player _player; // the player
    player * _onlinePlayers; // List of online players
    pthread_t _server_thread;	// Thread for server

    //Thread for listen incoming connection
    IncomingConnectionThread * _incomingConnection;
    ChatListener * _chatlist;
    PlayerListener * _playerlist;

};

#endif // MAINWINDOW_H
