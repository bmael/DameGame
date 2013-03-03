#include "playersonline.h"
#include "ui_playersonline.h"

#include <QDebug>

PlayersOnline::PlayersOnline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersOnline)
{
    ui->setupUi(this);

    _model = new QStandardItemModel(this);

    ui->listView->setModel(_model);
}

PlayersOnline::~PlayersOnline()
{
    delete ui;
}

void PlayersOnline::clear()
{
    _model->clear();
}

void PlayersOnline::addPlayer(player toAdd)
{
    QStandardItem * item = new QStandardItem(QString::fromStdString(toAdd.name));
    item->setEditable(false);
    item->setIcon(QIcon(":/icons/user"));
    _model->appendRow(item);
}

void PlayersOnline::removePlayer(player toRm)
{

    //    int i = 0;
    //    bool isFind = false;
    //    while(!isFind && i < _model->rowCount()){

    //        if(_model->item(i)->text() == QString::fromStdString(toRm.name)){
    //            isFind = true;
    //            break;
    //        }
    //        i++;
    //    }
    QList<QStandardItem *> itemList = _model->findItems(QString::fromStdString(toRm.name));
    if(!itemList.isEmpty()){
        qDebug() << "PlyaersOnline Widget : rm : " << itemList.at(0)->text();
//        _model->takeItem(i);
        _model->removeRow(itemList.at(0)->row());
       // _model->setRowCount(_model->rowCount()-1);

        //delete itemList.at(0);
    }
}
