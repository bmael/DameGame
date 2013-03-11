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
    _listener = NULL;

    /* Opponent player */
    strcpy(_opponent_player.name , "");

    /* player */
    strcpy(_player.name, "");
    _player.color = 0;

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
    connect(this, SIGNAL(askRmPlayer(player)), ui->rightMenuWidget, SIGNAL(rmPlayerFromView(player)));
    connect(ui->rightMenuWidget, SIGNAL(askNewGameWith(player)), this, SLOT(createGame(player)));
    connect(this, SIGNAL(askSetBusy(player)), ui->rightMenuWidget, SIGNAL(askSetBusy(player)));
    connect(this, SIGNAL(askSetFree(player)), ui->rightMenuWidget, SIGNAL(askSetFree(player)));

    //Checkerboard
    connect(this, SIGNAL(initGame(player, player)), ui->checkerboardwidget, SLOT(init(player, player)));
    connect(ui->checkerboardwidget, SIGNAL(sendCheckerboard(checkerboard)), this, SLOT(sendCheckerboard(checkerboard)));
    connect(ui->checkerboardwidget, SIGNAL(sendWinner(player)), this, SLOT(adviseWinner(player)));
    //connect(this, SIGNAL(changePlayerTurn(int)), ui->checkerboardwidget, SLOT(changePlayer(int)));

}

/**
 * @brief Destructor of the \ref MainWindow.
 */
MainWindow::~MainWindow()
{
    if(_listener != NULL){
        stopListeners();
        delete _listener;
    }

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

    ui->rightMenuWidget->clear();

    frame f ;
    //Advise the opponent if the client is in a game
    if(strlen(_opponent_player.name) != 0){
        qDebug() << "PPPPPPPPPPPPPPPPPPPPP I'm quit the game";
        strcpy(f.data_type, OPPONENT_QUIT);
        memcpy(f.data, &_opponent_player, sizeof(_opponent_player));
        write_to_server(_player.socket, &f);
    }

    ui->checkerboardwidget->clear();

    //Advising the server for the disconnection
    f = make_frame(_local_addr.sin_addr, _local_addr.sin_addr, DISCONNECT, _player.name);
    write_to_server(_player.socket,&f);

    //disconnection of the client
    server_disconnection(_player.socket);


    stopListeners(); // Stop all listeners threads

    qDebug() << "Client is disconnected";

    // When the client is disconnected, display the connection page
    ui->stackedWidget->slideInIdx(0, SlidingStackedWidget::TOP2BOTTOM);
}

void MainWindow::pseudoAlreadyExists(QString pseudo)
{
    QMessageBox box(QMessageBox::Information,tr("Pseudo already exists"),QString(tr("Pseudo ") + pseudo + tr(" already exists. Please choose another.")));
    box.exec();

    this->serverDisconnection();
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
    char data[DATA_SIZE] = "\0";
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
    // Start a thread for listening server requests.
    _listener = new Listener(_player.socket, this);

    connect(_listener, SIGNAL(pseudoAlreadyExists(QString)), this, SLOT(pseudoAlreadyExists(QString)));

    connect(_listener, SIGNAL(addMsg(QString)), this, SLOT(addMsg(QString)));

    connect(_listener, SIGNAL(addPlayerToView(player)), this, SIGNAL(askAddPlayer(player)));
    connect(_listener, SIGNAL(removePlayerFromView(player)), this, SIGNAL(askRmPlayer(player)));

    connect(_listener,  SIGNAL(advisePlayerForGame(QString)), this, SLOT(adviseForGame(QString)));
    connect(_listener, SIGNAL(advisePlayerForAbortedGame(QString)), this, SLOT(adviseForAbortedGame(QString)));

    connect(_listener, SIGNAL(startGame()), this, SLOT(startGame()));

    connect(_listener, SIGNAL(clientBusy(player)), ui->rightMenuWidget, SIGNAL(askSetBusy(player)));
    connect(_listener, SIGNAL(clientFree(player)), ui->rightMenuWidget, SIGNAL(askSetFree(player)));

    connect(_listener, SIGNAL(setOpponent(player)), this, SLOT(setOpponent(player)));
    connect(_listener, SIGNAL(opponentQuit(player)), this, SLOT(opponentQuit(player)));

    connect(_listener, SIGNAL(receiveCheckerboard(checkerboard)), ui->checkerboardwidget, SLOT(receiveCheckerboard(checkerboard)));
    connect(_listener, SIGNAL(receiveWinner(player)), this, SLOT(displayWinner(player)));
}

/**
 * @brief Stops all listeners thread (chat, online players).
 * @pre @ref startListener have to be called before this function otherwise generate
 * a segmentation fault.
 */
void MainWindow::stopListeners()
{
    _listener->setStop(true);
}

/**
 * @brief Creates a new game with another player.
 * @param player other - Other player for playing
 */
void MainWindow::createGame(player other)
{
    if(strcmp(_player.name, other.name) != 0 && _player.color == 0 && strlen(_opponent_player.name) == 0 ){
        qDebug() << "[Create_game] : creating game with " << other.name;

        QMessageBox box(QMessageBox::Information,tr("Starting a game"),QString(tr("Are you sure to start a game with ") + other.name), QMessageBox::Yes | QMessageBox::No);
        int res = box.exec();
        switch(res){
            case QMessageBox::Yes:

                frame f;
                strcpy(f.data_type, ASK_NEW_GAME);
                strcpy(f.data, other.name);
                write_to_server(_player.socket, &f);

                QMessageBox infoBox(QMessageBox::Information,
                                tr("Request sent"),
                                QString(tr("Waiting for confirmation by ") + other.name));
                infoBox.exec();

                break;

        }

    }

}

void MainWindow::adviseForGame(QString name)
{
    QMessageBox infoBox(QMessageBox::Information,
                    tr("Game"),
                    QString(name + tr(" wants to play with you.\nDo you accept ?")),
                    QMessageBox::Yes | QMessageBox::No);
    int res = infoBox.exec();
    frame f;
    switch(res){
        case QMessageBox::No:

            strcpy(f.data_type, REJECT_NEW_GAME);
            strcpy(f.data, (char*)name.toStdString().c_str());
            write_to_server(_player.socket, &f);
            break;

        case QMessageBox::Yes:
        qDebug() << "[Info_box] : Game is accepted";
            strcpy(f.data_type, ACCEPT_NEW_GAME);
            strcpy(f.data, (char*)name.toStdString().c_str());
            write_to_server(_player.socket, &f);
            break;
    }
}

void MainWindow::adviseForAbortedGame(QString name)
{
    QMessageBox infoBox(QMessageBox::Information,
                    tr("Game"),
                    QString(name + tr(" don't accept your game.")));
    infoBox.exec();

}

void MainWindow::startGame()
{
    qDebug() << "[start_game] : starting the game";
    emit askSetBusy(_player);

}

void MainWindow::setOpponent(player p)
{
    qDebug() << "[set_opponent] : player " << p.name;
    _opponent_player = p;

    if(_opponent_player.color == WHITE_CHECKER){
        _player.color = BLACK_CHECKER;
    }else{
        _player.color = WHITE_CHECKER;
    }

    qDebug() << "_player.color : " << _player.color;
    qDebug() << "_popponent_player : " << _opponent_player.color;

    emit initGame(_player, _opponent_player);
}

void MainWindow::opponentQuit(player p)
{
    strcpy(_opponent_player.name, "");
    QMessageBox infoBox(QMessageBox::Information,
                        tr("Opponent quit"),
                        QString(p.name + tr(" has been disconnected from the server.")));
    infoBox.exec();

    ui->checkerboardwidget->clear();

    emit askSetFree(_player);


}

void MainWindow::sendCheckerboard(checkerboard c)
{

    board_frame bf;
    bf.board = c;
    bf.receiver = _opponent_player;

    frame f;
    strcpy(f.data_type, SEND_GAMEBOARD);
    memcpy(f.data, &bf, sizeof(bf));

    write_to_server(_player.socket, &f);
}

void MainWindow::adviseWinner(player p)
{
    QMessageBox infoBox(QMessageBox::Information,
                        tr("And the winner is..."),
                        QString(p.name + tr(" wins this game.")));
    infoBox.exec();

    frame f;
    strcpy(f.data_type, SEND_WINNER);
    strcpy(f.data, _opponent_player.name);

    write_to_server(_player.socket, &f);

}

void MainWindow::displayWinner(player p)
{
    QMessageBox infoBox(QMessageBox::Information,
                        tr("And the winner is..."),
                        QString(p.name + tr(" wins this game.")));
    infoBox.exec();
}
