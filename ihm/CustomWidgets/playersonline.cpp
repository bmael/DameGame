#include "playersonline.h"
#include "ui_playersonline.h"

PlayersOnline::PlayersOnline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersOnline)
{
    ui->setupUi(this);


    ui->listView->setModel(&_model);

}

PlayersOnline::~PlayersOnline()
{
    delete ui;
}

void PlayersOnline::addPlayer(player *toAdd)
{
    _players.append(QString(toAdd->name));
}
