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

    _incomingConnection = NULL;

    // Connect Connection Widget with the window
    connect(ui->connectionWidget, SIGNAL(askConnection(QString, int, QString)),
            this, SLOT(serverConnection(QString, int, QString)));

    // Configure disconnection of the user
    connect(ui->rightMenuWidget, SIGNAL(askDisconnection()), this, SLOT(serverDisconnection()));

}

MainWindow::~MainWindow()
{
    delete _incomingConnection;
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    //have to disconnect the player before close

    server_disconnection(_socket_descriptor);

    delete _incomingConnection;

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

    qDebug() << "Client addr : " << inet_ntoa(_local_addr.sin_addr);
    qDebug() << "Socket created : " << _socket_descriptor;

    qDebug() << "Creating a socket";
    _socket_descriptor = create_socket();

    qDebug() << "Connecting the client to the server";
    server_connection(_socket_descriptor, _local_addr);

    qDebug() << "Client is connected";

    // We start a thread to listen for all incoming connections
     _incomingConnection =
            new IncomingConnectionThread(_socket_descriptor);

    // Send the pseudo of the client to the server
    qDebug() << "player : " << _player.name;


    frame f;
    f.src = _local_addr.sin_addr;
    f.dest = _local_addr.sin_addr;
    strcpy(f.data_type,CONNECT);
    strcpy(f.data, _player.name);

    write_to_server(_socket_descriptor, &f);
    qDebug() << "information sent...";

    // When the client is connected, display the mainPage
    ui->stackedWidget->slideInIdx(1, SlidingStackedWidget::BOTTOM2TOP);

}

void MainWindow::serverDisconnection()
{
    // cleaning the connection page
    ui->connectionWidget->clean();

//    char action[256] = "removeClient:";
//    send_client_information(_socket_descriptor, strcat(action,_player.name));
    server_disconnection(_socket_descriptor);

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
