#include "playersonline.h"
#include "ui_playersonline.h"

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

void PlayersOnline::addPlayer(player toAdd)
{
    QStandardItem * item = new QStandardItem(QString::fromStdString(toAdd.name));
    _model->appendRow(item);
}
