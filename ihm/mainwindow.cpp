#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect Connection Widget with the window
    connect(ui->connectionWidget, SIGNAL(askConnection(QString, int)), this, SLOT(serverConnection(QString, int)));

    // Configure disconnection of the user
    connect(ui->rightMenuWidget, SIGNAL(askDisconnection()), this, SLOT(serverDisconnection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

/**
 * @brief Connects the client to the server.
 */
void MainWindow::serverConnection(QString host, int port)
{
    host = "localhost";

    //TODO integrate the client/server code for connection
    qDebug() << "initializing the host";
    qDebug() << "local_addresse : " << QString(_local_addr.sin_family) << " | "
             << QString(_local_addr.sin_port) << " | ";
    init_host(_ptr_host, (char*)host.toStdString().c_str(), &_local_addr);

    qDebug() << "local_addresse : " << QString(_local_addr.sin_family) << " | "
             << QString(_local_addr.sin_port) << " | ";

    qDebug() << "Assigning a port to the client";
    assign_port(&_local_addr, port);

    qDebug() << "Creating a socket";
    create_socket(&_socket_descriptor);

    qDebug() << "Connecting the client to the server";
    qDebug() << "socket_descriptor : " << _socket_descriptor;
    qDebug() << "local_addresse : " << QString(_local_addr.sin_family) << " | "
             << QString(_local_addr.sin_port) << " | ";

    server_connection(_socket_descriptor, _local_addr);

    qDebug() << "Client is connected";


    // When the client is connected, display the mainPage
    ui->stackedWidget->slideInIdx(1, SlidingStackedWidget::BOTTOM2TOP);

}

void MainWindow::serverDisconnection()
{
    // TODO integrate the client/server code for disconnection

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
