#include "checkerobject.h"

CheckerObject::CheckerObject(int color, QGraphicsItem *parent) :
    QGraphicsObject(parent), color(color)
{
    setIcon();
}

CheckerObject::~CheckerObject()
{
}

void CheckerObject::setIcon()
{
    switch(color){
        case 1:
            _icon = QPixmap(":/icons/blackchecker");
            break;
        case -1:
            _icon = QPixmap(":/icons/whitechecker");
            break;
    }
}

void CheckerObject::setColor(int color)
{
    this->color = color;
    setIcon();
}

QRectF CheckerObject::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void CheckerObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(QPointF(0, 0), _icon);
}

