#include "playersonline.h"
#include "ui_playersonline.h"

#include <QDebug>

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
    item->setIcon(QIcon(":/icons/free"));

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
    emit askNewGameWith(p);
}

void PlayersOnline::setBusy(player p)
{
    QList<QStandardItem *> itemList = _model->findItems(QString::fromStdString(p.name));
    if(!itemList.isEmpty()){
        itemList.at(0)->setIcon(QIcon(":/icons/busy"));
    }
}

void PlayersOnline::setFree(player p)
{
    QList<QStandardItem *> itemList = _model->findItems(QString::fromStdString(p.name));
    if(!itemList.isEmpty()){
        itemList.at(0)->setIcon(QIcon(":/icons/free"));
    }
}
