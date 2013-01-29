#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>

namespace Ui {
class Chatroom;
}

class Chatroom : public QWidget
{
    Q_OBJECT
    
public:
    explicit Chatroom(QWidget *parent = 0);
    ~Chatroom();
    
private:
    Ui::Chatroom *ui;
};

#endif // CHATROOM_H
