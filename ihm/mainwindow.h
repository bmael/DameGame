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
    void serverConnection(QString host, int port, QString pseudo); //Connects the client to the server
    void serverDisconnection();             // Disconnects the client from the server

    void on_actionQuit_triggered();         // Quits clearly the application
    void on_showHidePushButton_clicked();   // Shows or hides the right menu
    void sendChatMessage(QString msg);      // Sends a message on the chatroom
    void addMsg(QString msg);               // Adds a message on the chatroom

signals:
    void askAddMsg(QString);    // Emits when the user wants to send a message on the chatroom

private:
    void startListeners();      // Starts all listeners threads
    void stopListeners();       // Stops all listeners threads

private:
    /* UI attributes */
    Ui::MainWindow *ui;
    bool _rightMenuHidden;

    /* Client attributes */
    sockaddr_in _local_addr;    // local adress of the client
    hostent *_ptr_host; 		// information about host machine
    servent *_ptr_service;      // information about a service

    player _player;             // the player

    /* Threads */
    ChatListener * _chatlist;       // Manages the chatroom
    PlayerListener * _playerlist;   // Manages the online players list

};

#endif // MAINWINDOW_H
