#include "checkerboardobject.h"

CheckerBoardObject::CheckerBoardObject(QGraphicsItem *parent) :
    QGraphicsObject(parent), _icon(":/icons/checkerboard")
{

}

CheckerBoardObject::~CheckerBoardObject()
{
}

QRectF CheckerBoardObject::boundingRect() const
{
    return QRectF(0, 0, 500, 500);
}

void CheckerBoardObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(QPointF(0,0), _icon);
}
