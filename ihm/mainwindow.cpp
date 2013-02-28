#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <QDebug>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // _incomingConnection = NULL;
    _nbPlayerMax = 3;
    _players.other_players = (player*)calloc(_nbPlayerMax, sizeof(player));
    _players.nbPlayers = 0;


    // Connect Connection Widget with the window
    connect(ui->connectionWidget, SIGNAL(askConnection(QString, int, QString)),
            this, SLOT(serverConnection(QString, int, QString)));

    // Configure disconnection of the user
    connect(ui->rightMenuWidget, SIGNAL(askDisconnection()), this, SLOT(serverDisconnection()));
    connect(ui->rightMenuWidget, SIGNAL(askSendMessage(QString)), this, SLOT(sendChatMessage(QString)));

    //Chatroom
    connect(this, SIGNAL(askAddMsg(QString)), ui->rightMenuWidget, SIGNAL(addMsg(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    //have to disconnect the player before close
    server_disconnection(_socket_descriptor);

    this->close();
}

/**
 * @brief Connects the client to the server.
 */
void MainWindow::serverConnection(QString host, int port, QString pseudo)
{
    strcpy(_player.name, pseudo.toStdString().c_str());

    qDebug() << "[Server_connection] : initializing the host";
    init_host(_ptr_host, (char*)host.toStdString().c_str(), &_local_addr);

    qDebug() << "[Server_connection] : Assigning a port to the client";
    assign_port(&_local_addr, port);

    qDebug() << "[Server_connection] : Creating a socket";
    _socket_descriptor = create_socket();

    qDebug() << "[Server_connection] : Connecting the client to the server";
    if(server_connection(_socket_descriptor, _local_addr) >= 0){

        _player.socket = _socket_descriptor;

        qDebug() << "[Server_connection] : Client is connected";

        // Send the pseudo of the client to the server
        qDebug() << "[Server_connection] : Sending information to the server" << _player.name;
        frame f = make_frame(_local_addr.sin_addr, _local_addr.sin_addr, CONNECT, _player.name);
        write_to_server(_player.socket, &f);

        /* Listen for all instruction from the server */
        _players.me = _player;


        //qDebug() << "Other_players : " << _players.other_players[0].name;

    //    if(pthread_create(&_server_thread, NULL, listen_server_instruction, &_players)){
    //        perror("[Server_connection] : Problem on the thread");
    //        return;
    //    }

        // Start the listener for the chatroom
       _chatlist = new ChatListener(_player.socket, this);
       connect(_chatlist, SIGNAL(addMsg(QString)), this, SLOT(addMsg(QString)));

       // Start the listener for the players list
       //_playerlist = new PlayerListener(_player.socket, this);

        // When the client is connected, display the mainPage
        ui->stackedWidget->slideInIdx(1, SlidingStackedWidget::BOTTOM2TOP);
    }
    else{
        QMessageBox errorBox(QMessageBox::Question,tr("error"),tr("Can't establish the connection with the server."),QMessageBox::Cancel);
        errorBox.exec();
    }

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

    _chatlist->setStop(true);
    _playerlist->setStop(true);

    qDebug() << "Client is disconnected";

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

void MainWindow::sendChatMessage(QString msg)
{
    qDebug() << msg;
    char data[sizeof(DATA_SIZE)] = "\0";
    strcat(data, "[");
    strcat(data, _player.name);
    strcat(data, "] : ");
    strcat(data, msg.toStdString().c_str());
    frame f = make_frame(_local_addr.sin_addr, _local_addr.sin_addr, SEND_MSG_CHAT, data);
    write_to_server(_player.socket, &f);
}

void MainWindow::addMsg(QString msg)
{
    qDebug() << "ADDING MSG : " << msg;
    askAddMsg(msg);
}
