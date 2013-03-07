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

    void clear();
    
private slots:
    void on_sendPushButton_clicked();
    void addText(QString msg);

    void on_chatTextEdit_textChanged();

signals:
    void sendMessage(QString);

private:
    Ui::Chatroom *ui;
};

#endif // CHATROOM_H
