#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Threads/incomingconnectionthread.h"
#include "Threads/listener.h"

#ifdef __cplusplus
extern "C" {
#include <DameGame/include/client.h>
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

    void createGame(player other);    // Creates a new game between this client and another player.
    void adviseForGame(QString name); // Display a QMessageBox to advise the client about a new game request.
    void adviseForAbortedGame(QString name); // Display a QMessageBox to advise the client about a rejected new game.
    void startGame();                 // Launch the game

signals:
    void askAddMsg(QString);    // Emits when the user wants to send a message on the chatroom

    void askAddPlayer(player);  // Emits when we have to add a new player in our list.
    void askRmPlayer(player);   // Emits when a client is disconnected.

    void askSetBusy(player p);  // Emits when a game is starting

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
    Listener * _listener;

};

#endif // MAINWINDOW_H
