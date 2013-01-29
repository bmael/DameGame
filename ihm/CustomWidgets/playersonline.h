#ifndef PLAYERSONLINE_H
#define PLAYERSONLINE_H

#include <QWidget>

namespace Ui {
class PlayersOnline;
}

class PlayersOnline : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlayersOnline(QWidget *parent = 0);
    ~PlayersOnline();
    
private:
    Ui::PlayersOnline *ui;
};

#endif // PLAYERSONLINE_H
