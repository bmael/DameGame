#include "rightmenu.h"
#include "ui_rightmenu.h"

#include <QDebug>
#include <QPropertyAnimation>

/**
 * @brief Constructs a new RightMenu widget.
 * @param parent
 */
RightMenu::RightMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RightMenu)
{
    ui->setupUi(this);

    /* Chatroom */
    connect(ui->chatroomWidget, SIGNAL(sendMessage(QString)), this, SIGNAL(askSendMessage(QString)));
    connect(this, SIGNAL(addMsg(QString)), ui->chatroomWidget, SLOT(addText(QString)));

    /* Online players */
    connect(this, SIGNAL(addPlayerToView(player)), ui->playersOnlineWidget, SLOT(addPlayer(player)));
    connect(this, SIGNAL(rmPlayerFromView(player)), ui->playersOnlineWidget, SLOT(removePlayer(player)));

    connect(ui->playersOnlineWidget, SIGNAL(askNewGameWith(player)), this, SIGNAL(askNewGameWith(player)));
    connect(this, SIGNAL(askSetBusy(player)), ui->playersOnlineWidget, SLOT(setBusy(player)));
}

/**
 * @brief Destroys the RightMenu
 */
RightMenu::~RightMenu()
{
    delete ui;
}

void RightMenu::clear()
{
    ui->chatroomWidget->clear();
    ui->playersOnlineWidget->clear();
}





void RightMenu::on_pushButton_clicked()
{
    emit askDisconnection();
}
