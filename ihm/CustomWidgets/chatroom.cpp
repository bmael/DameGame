#include "chatroom.h"
#include "ui_chatroom.h"

#include <QDebug>
#include <QScrollBar>

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

void Chatroom::clear()
{
    ui->chatTextBrowser->clear();
    ui->chatTextEdit->clear();
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
    ui->chatTextBrowser->verticalScrollBar()->setValue(ui->chatTextBrowser->verticalScrollBar()->maximum());
}

void Chatroom::on_chatTextEdit_textChanged()
{
    if(ui->chatTextEdit->toPlainText().size() > 1400){
        ui->sendPushButton->setEnabled(false);
    }
    else{
        ui->sendPushButton->setEnabled(true);
    }
}
