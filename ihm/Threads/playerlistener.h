#ifndef PLAYERLISTENER_H
#define PLAYERLISTENER_H

#include <QThread>

class PlayerListener : public QThread
{
    Q_OBJECT
public:
    explicit PlayerListener(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // PLAYERLISTENER_H
