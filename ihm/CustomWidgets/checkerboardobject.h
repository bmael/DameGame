#ifndef CHECKERBOARDOBJECT_H
#define CHECKERBOARDOBJECT_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


class CheckerBoardObject : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CheckerBoardObject(QGraphicsItem *parent = 0);
    ~CheckerBoardObject();
    
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

signals:
    
public slots:

private:
    QPixmap _icon;
    
};

#endif // CHECKERBOARDOBJECT_H
