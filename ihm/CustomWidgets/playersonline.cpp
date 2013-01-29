#include "playersonline.h"
#include "ui_playersonline.h"

PlayersOnline::PlayersOnline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayersOnline)
{
    ui->setupUi(this);
}

PlayersOnline::~PlayersOnline()
{
    delete ui;
}
