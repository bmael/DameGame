#ifndef PLAYERSONLINE_H
#define PLAYERSONLINE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>

#include <DameGame/include/structures.h>


namespace Ui {
class PlayersOnline;
}

class PlayersOnline : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlayersOnline(QWidget *parent = 0);
    ~PlayersOnline();

    void clear();

signals:
    void askNewGameWith(player p);

public slots:
    void addPlayer(player toAdd);
    void removePlayer(player toRm);
    void setBusy(player p);
    void setFree(player p);

private slots:
    void doubleClickedItem(QModelIndex i);

private:
    Ui::PlayersOnline *ui;

    QStandardItemModel * _model;
    QStandardItem * _free;
    QStandardItem * _busy;

};

#endif // PLAYERSONLINE_H
