#include "checkerobject.h"

#include <QDebug>

CheckerObject::CheckerObject(int color, QGraphicsItem *parent) :
    QGraphicsObject(parent), color(color)
{
    e = new QGraphicsColorizeEffect();
    e->setColor(QColor(255,255,255,20));
    this->setGraphicsEffect(e);
    this->setEffectEnabled(false);

    setIcon();
}

CheckerObject::~CheckerObject()
{
}

void CheckerObject::setIcon()
{
    switch(color){
        case 2:
            _icon = QPixmap(":/icons/blackdaughter");
            break;

        case 1:
            _icon = QPixmap(":/icons/blackchecker");
            break;

        case 0:
            _icon = QPixmap();
            break;

        case -1:
            _icon = QPixmap(":/icons/whitechecker");
            break;

        case -2:
            _icon = QPixmap(":/icons/whitedaughter");
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

void CheckerObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(QPointF(this->x(), this->y()));
}

void CheckerObject::setEffectEnabled(bool enable)
{
    this->graphicsEffect()->setEnabled(enable);
}

