#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <QDebug>

#include <QMessageBox>

/**
 * @brief Constructs and initialize the \ref MainWindow.
 * @param QWidget parent - the parent of the \ref MainWindow (0 by default).
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Init Threads */
    _chatlist = NULL;
    _playerlist = NULL;

    mutex = new QMutex();

    // Connect Connection Widget with the window
    connect(ui->connectionWidget, SIGNAL(askConnection(QString, int, QString)),
            this, SLOT(serverConnection(QString, int, QString)));

    // Configure disconnection of the user
    connect(ui->rightMenuWidget, SIGNAL(askDisconnection()), this, SLOT(serverDisconnection()));
    connect(ui->rightMenuWidget, SIGNAL(askSendMessage(QString)), this, SLOT(sendChatMessage(QString)));

    //Chatroom
    connect(this, SIGNAL(askAddMsg(QString)), ui->rightMenuWidget, SIGNAL(addMsg(QString)));

    //Online players
    connect(this, SIGNAL(askAddPlayer(player)), ui->rightMenuWidget, SIGNAL(addPlayerToView(player)));

}

/**
 * @brief Destructor of the \ref MainWindow.
 */
MainWindow::~MainWindow()
{
    if(_chatlist != NULL && _playerlist != NULL) stopListeners();
    if(_chatlist != NULL) delete _chatlist;
    if(_playerlist != NULL) delete _playerlist;

    delete mutex;
    delete ui;
}

/**
 * @brief Quits the application.
 * @post The client is also disconnected from the server.
 */
void MainWindow::on_actionQuit_triggered()
{
    //have to disconnect the player before close
    server_disconnection(_player.socket);

    this->close();
}

/**
 * @brief Connects the client to the server.
 * @param QString host - the host name
 * @param int port - the port used by the server
 * @param QString pseudo - the client's name
 */
void MainWindow::serverConnection(QString host, int port, QString pseudo)
{
    strcpy(_player.name, pseudo.toStdString().c_str());
    init_host(_ptr_host, (char*)host.toStdString().c_str(), &_local_addr);
    assign_port(&_local_addr, port);

    _player.socket = create_socket();

    // Have to test if the client can be connect to the server
    if(server_connection(_player.socket, _local_addr) >= 0){

        qDebug() << "[Server_connection] : Client is connected";

        startListeners(); // Have to start listeners threads

        // Ask to the server to add the new client into its array of players
        qDebug() << "[Server_connection] : Sending information to the server" << _player.name;
        frame f = make_frame(_local_addr.sin_addr, _local_addr.sin_addr, CONNECT, _player.name);
        write_to_server(_player.socket, &f);

        // When the client is connected, display the mainPage of the application
        ui->stackedWidget->slideInIdx(1, SlidingStackedWidget::BOTTOM2TOP);
    }
    else{
        //Connection is impossible
        QMessageBox errorBox(QMessageBox::Question,tr("error"),tr("Can't establish the connection with the server."),QMessageBox::Cancel);
        errorBox.exec();
    }

}

/**
 * @brief Disconnects the client from the server.
 * @pre The client have to be connected before to call this method.
 */
void MainWindow::serverDisconnection()
{
    // cleaning the connection page
    ui->connectionWidget->clean();

    //Advising the server for the disconnection
    frame f = make_frame(_local_addr.sin_addr, _local_addr.sin_addr, DISCONNECT, _player.name);
    write_to_server(_player.socket,&f);

    //disconnection of the client
    server_disconnection(_player.socket);

    stopListeners(); // Stop all listeners threads

    qDebug() << "Client is disconnected";

    // When the client is disconnected, display the connection page
    ui->stackedWidget->slideInIdx(0, SlidingStackedWidget::TOP2BOTTOM);
}

/**
 * @brief Shows or hides the right menu with an animation
 * according to the value of \ref _rightMenuHidden attribute.
 */
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

/**
 * @brief Sends to the server the message to send to all clients.
 * This message is formatted like that : "[player_name] : msg".
 * @param QString msg - the message to send.
 */
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

/**
 * @brief Emits \ref askAddMsg(QString) to add a message on the chatroom.
 * @param QString msg - the message to add.
 */
void MainWindow::addMsg(QString msg)
{
    qDebug() << "ADDING MSG : " << msg;
    askAddMsg(msg);
}

/**
 * @brief Instanciates and starts all listeners thread (chat, online players).
 * @pre The client have to be connected before to call this function.
 */
void MainWindow::startListeners()
{
    // Start the listener for the chatroom
   _chatlist = new ChatListener(_player.socket, mutex, this);
   connect(_chatlist, SIGNAL(addMsg(QString)), this, SLOT(addMsg(QString)));

   // Start the listener for the players list
   _playerlist = new PlayerListener(_player.socket, mutex, this);
   connect(_playerlist, SIGNAL(addPlayerToView(player)), this, SIGNAL(askAddPlayer(player)));
}

/**
 * @brief Stops all listeners thread (chat, online players).
 * @pre @ref startListener have to be called before this function otherwise generate
 * a segmentation fault.
 */
void MainWindow::stopListeners()
{
    _chatlist->setStop(true);
    _playerlist->setStop(true);
}
