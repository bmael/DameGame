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

private:
    void init();
    
private:
    Ui::CheckerBoardWidget *ui;

    QGraphicsScene * _scene;

    CheckerBoardObject * _checkerboard_o;

    QList<CheckerObject*> whites;
    QList<CheckerObject*> blacks;

    checkerboard * board;

};

#endif // CHECKERBOARDWIDGET_H
