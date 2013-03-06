#include "connection.h"
#include "ui_connection.h"

#include <QPainter>

Connection::Connection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connection)
{
    ui->setupUi(this);
    ui->pseudoLineEdit->setFocus();
    ui->pseudoError->hide();
    ui->connectPushButton->setEnabled(false);
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
    ui->pseudoLineEdit->clear();
}

void Connection::on_pseudoLineEdit_textChanged(const QString &arg1)
{

    if(ui->pseudoLineEdit->text().size() > 10){
        ui->pseudoError->show();
        ui->connectPushButton->setEnabled(false);

    }else{
        if(ui->pseudoLineEdit->text().size() > 0){
            ui->pseudoError->hide();
            ui->connectPushButton->setEnabled(true);
        }else{
            if(ui->pseudoLineEdit->text().isEmpty()){
                ui->pseudoError->hide();
                ui->connectPushButton->setEnabled(false);
            }
        }
    }

}
