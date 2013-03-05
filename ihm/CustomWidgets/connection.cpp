#include "connection.h"
#include "ui_connection.h"

#include <QPainter>

Connection::Connection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connection)
{
    ui->setupUi(this);
    ui->pseudoLineEdit->setFocus();
}

Connection::~Connection()
{
    delete ui;
}

/**
  * @brief Override paintEvent for MapMenu. Need it to apply a css to a QWidget.
  */
void Connection::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Connection::on_connectPushButton_clicked()
{
    emit askConnection(ui->serverLineEdit->text(),
                       ui->portLineEdit->text().toInt(),
                       ui->pseudoLineEdit->text());
}


void Connection::clean()
{
//    ui->serverLineEdit->clear();
//    ui->portLineEdit->clear();
    ui->pseudoLineEdit->clear();
}
