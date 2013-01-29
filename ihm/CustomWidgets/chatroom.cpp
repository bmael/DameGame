#include "chatroom.h"
#include "ui_chatroom.h"

Chatroom::Chatroom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chatroom)
{
    ui->setupUi(this);
}

Chatroom::~Chatroom()
{
    delete ui;
}
