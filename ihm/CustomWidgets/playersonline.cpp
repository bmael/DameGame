#include "playersonline.h"
#include "ui_playersonline.h"

#include <QDebug>
#include <QMessageBox>

PlayersOnline::PlayersOnline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersOnline)
{
    ui->setupUi(this);

    _model = new QStandardItemModel(this);
    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickedItem(QModelIndex)));

    _free = new QStandardItem("free");
    _free->setIcon(QIcon(":/icons/free"));

    _busy = new QStandardItem("busy");
    _busy->setIcon(QIcon(":/icons/busy"));

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

    if(toAdd.color == 0){
        item->setIcon(QIcon(":/icons/free"));
        item->setData("free");
    }
    else{
        item->setIcon(QIcon(":/icons/busy"));
        item->setData("busy");
    }

    _model->appendRow(item);
}

void PlayersOnline::removePlayer(player toRm)
{
    QList<QStandardItem *> itemList = _model->findItems(QString::fromStdString(toRm.name));
    if(!itemList.isEmpty()){
        _model->removeRow(itemList.at(0)->row());
    }
}

void PlayersOnline::doubleClickedItem(QModelIndex i)
{
    player p;
    strcpy(p.name, (char*)_model->item(i.row())->text().toStdString().c_str());
    qDebug() << "[Double_Clicked_item] : icone name : " << _model->item(i.row())->data();
    if(_model->item(i.row())->data() != "busy" ){
        emit askNewGameWith(p);
    }
    else{
        QMessageBox infoBox(QMessageBox::Information,tr("Busy player"),QString(p.name + tr(" is already on a game...")));
        infoBox.exec();
    }
}

void PlayersOnline::setBusy(player p)
{
    QList<QStandardItem *> itemList = _model->findItems(QString::fromStdString(p.name));
    if(!itemList.isEmpty()){
        itemList.at(0)->setIcon(QIcon(":/icons/busy"));
        itemList.at(0)->setData("busy");
    }
}

void PlayersOnline::setFree(player p)
{
    QList<QStandardItem *> itemList = _model->findItems(QString::fromStdString(p.name));
    if(!itemList.isEmpty()){
        itemList.at(0)->setIcon(QIcon(":/icons/free"));
        itemList.at(0)->setData("free");
    }
}
