#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <QDebug>

#include "Threads/incomingconnectionthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // _incomingConnection = NULL;

    // Connect Connection Widget with the window
    connect(ui->connectionWidget, SIGNAL(askConnection(QString, int, QString)),
            this, SLOT(serverConnection(QString, int, QString)));

    // Configure disconnection of the user
    connect(ui->rightMenuWidget, SIGNAL(askDisconnection()), this, SLOT(serverDisconnection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    //have to disconnect the player before close
    server_disconnection(_socket_descriptor);

    //_incomingConnection->setStop(true);
    //delete _incomingConnection;
    this->close();
}

/**
 * @brief Connects the client to the server.
 */
void MainWindow::serverConnection(QString host, int port, QString pseudo)
{
    _player.name = new char[200];
    strcpy(_player.name, pseudo.toStdString().c_str());

    qDebug() << "initializing the host";
    init_host(_ptr_host, (char*)host.toStdString().c_str(), &_local_addr);

    qDebug() << "Assigning a port to the client";
    assign_port(&_local_addr, port);

    qDebug() << "Creating a socket";
    _socket_descriptor = create_socket();

    qDebug() << "Connecting the client to the server";
    server_connection(_socket_descriptor, _local_addr);

    qDebug() << "Client is connected";

    // We start a thread to listen for all incoming connections
//     _incomingConnection =
//            new IncomingConnectionThread(_socket_descriptor, this);

    // Send the pseudo of the client to the server
    qDebug() << "Sending information to the server" << _player.name;
    frame f = make_frame(_local_addr.sin_addr, _local_addr.sin_addr, CONNECT, _player.name);
    write_to_server(_socket_descriptor, &f);

    /* Listen for all instruction from the server */

    for_listen_server for_server;
    for_server.socket_desc = _socket_descriptor;
    for_server.players = _onlinePlayers;

    if(pthread_create(&_server_thread, NULL, listen_server_instruction, &for_server)){
        perror("[thread] : error");
        return;
    }

    // When the client is connected, display the mainPage
    ui->stackedWidget->slideInIdx(1, SlidingStackedWidget::BOTTOM2TOP);

}

void MainWindow::serverDisconnection()
{
    // cleaning the connection page
    ui->connectionWidget->clean();

    //Advising the server for the disconnection
    frame f = make_frame(_local_addr.sin_addr, _local_addr.sin_addr, DISCONNECT, _player.name);
    write_to_server(_socket_descriptor,&f);

    //disconnection of the client
    server_disconnection(_socket_descriptor);

    //_incomingConnection->setStop(true);

    qDebug() << "Client is disconnected";
    free(_player.name);

    // When the client is disconnected, display the connection page
    ui->stackedWidget->slideInIdx(0, SlidingStackedWidget::TOP2BOTTOM);
}

void MainWindow::on_showHidePushButton_clicked()
{
    QPropertyAnimation * animation = new QPropertyAnimation(ui->rightMenuWidget, "maximumWidth");

    animation->setDuration(1000);
    animation->setStartValue(ui->rightMenuWidget->maximumWidth());

    if(!_rightMenuHidden){
        ui->showHidePushButton->setIcon(QIcon(":/icons/2left"));
        animation->setEndValue(0);
        animation->setEasingCurve(QEasingCurve::InBack);

        _rightMenuHidden = true;
    }
    else{
        animation->setEndValue(314);
        animation->setEasingCurve(QEasingCurve::OutBack);

        ui->showHidePushButton->setIcon(QIcon(":/icons/2right"));

        _rightMenuHidden = false;
    }

    animation->start(QPropertyAnimation::DeleteWhenStopped);
}
