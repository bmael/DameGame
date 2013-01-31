#ifndef PLAYERSONLINE_H
#define PLAYERSONLINE_H

#include <QWidget>
#include <QStringListModel>

#include "../DameGame/structures.h"

namespace Ui {
class PlayersOnline;
}

class PlayersOnline : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlayersOnline(QWidget *parent = 0);
    ~PlayersOnline();

public slots:
    void addPlayer(player * toAdd);
    
private:
    Ui::PlayersOnline *ui;

    QStringListModel _model;
    QStringList _players;

};

#endif // PLAYERSONLINE_H
