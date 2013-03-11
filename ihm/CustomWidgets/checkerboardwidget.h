#ifndef CHECKERBOARDWIDGET_H
#define CHECKERBOARDWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QList>


#include "checkerboardobject.h"
#include "checkerobject.h"

#ifdef __cplusplus
extern "C" {
#include <DameGame/gameboard.h>
#include <DameGame/include/structures.h>
#include <DameGame/include/client.h>
}
#endif

#define CELL_SIZE 50

namespace Ui {
class CheckerBoardWidget;
}

class CheckerBoardWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CheckerBoardWidget(QWidget *parent = 0);
    ~CheckerBoardWidget();

    void move();
    void clear();

private:
    void loadInformation();
    void placeCheckers();
    void clearLists();
    void preventAction(int color);

signals:
    void sendCheckerboard(checkerboard);

public slots:
    void init(player p, player opponent);
    void receiveCheckerboard(checkerboard c);
    void changePlayer();

private slots:
    void itemClicked(QPointF p);

private:
    Ui::CheckerBoardWidget *ui;

    int player_color;

    QGraphicsScene * _scene;

    QGraphicsPixmapItem * white_player;
    QGraphicsPixmapItem * black_player;

    QGraphicsTextItem * white_name;
    QGraphicsTextItem * black_name;

    QGraphicsTextItem * turn_player;

    CheckerBoardObject * _checkerboard_o;

    QList<CheckerObject*> whites;
    QList<CheckerObject*> blacks;
    QList<CheckerObject*> empties;

    checkerboard board;

    player _player;
    player _opponent_player;

    QPointF firstClick;
    QPointF secondClick;


};

#endif // CHECKERBOARDWIDGET_H
