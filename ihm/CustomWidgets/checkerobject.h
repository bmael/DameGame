#ifndef CHECKEROBJECT_H
#define CHECKEROBJECT_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QMouseEvent>

class CheckerObject : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CheckerObject(int color, QGraphicsItem *parent = 0);
    ~CheckerObject();

    void setIcon();
    void setColor(int color);
    
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked(QPointF);
    
public slots:
    

private:
    QPixmap _icon;
    int color;


};

#endif // CHECKEROBJECT_H
