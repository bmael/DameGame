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
