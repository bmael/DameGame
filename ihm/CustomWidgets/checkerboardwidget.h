#ifndef CHECKERBOARDWIDGET_H
#define CHECKERBOARDWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QList>


#include "checkerboardobject.h"
#include "checkerobject.h"

#define CELL_SIZE 75

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
    Ui::CheckerBoardWidget *ui;

    QGraphicsScene * _scene;

    CheckerBoardObject * _checkerboard_o;

    QList<CheckerObject*> whites;
    QList<CheckerObject*> blacks;

};

#endif // CHECKERBOARDWIDGET_H
