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

private:
    void placeCheckers();
    void clearLists();
    void changePlayer();

public slots:
    void init();

private slots:
    void itemClicked(QPointF p);

private:
    Ui::CheckerBoardWidget *ui;

    int player_color;

    QGraphicsScene * _scene;

    CheckerBoardObject * _checkerboard_o;

    QList<CheckerObject*> whites;
    QList<CheckerObject*> blacks;
    QList<CheckerObject*> empties;


    checkerboard * board;

    QPointF firstClick;
    QPointF secondClick;


};

#endif // CHECKERBOARDWIDGET_H
