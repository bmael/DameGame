#include "chatroom.h"
#include "ui_chatroom.h"

#include <QDebug>

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

void Chatroom::on_sendPushButton_clicked()
{
    if(!ui->chatTextEdit->toPlainText().isEmpty()){
        emit sendMessage(ui->chatTextEdit->toPlainText());
        ui->chatTextEdit->clear();
    }
}

void Chatroom::addText(QString msg)
{
    qDebug() << "ADDING " << msg << "to ihm";
    ui->chatTextBrowser->setText(ui->chatTextBrowser->toPlainText()+ "\n" + msg);
}
