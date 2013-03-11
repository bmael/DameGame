#ifndef CHECKEROBJECT_H
#define CHECKEROBJECT_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsColorizeEffect>

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

    void setEffectEnabled(bool enable);

signals:
    void clicked(QPointF);
    
public slots:
    

private:
    QGraphicsColorizeEffect * e;
    QPixmap _icon;
    int color;


};

#endif // CHECKEROBJECT_H
