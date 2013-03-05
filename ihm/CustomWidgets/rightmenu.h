#ifndef RIGHTMENU_H
#define RIGHTMENU_H

#include <QWidget>

#include <DameGame/include/structures.h>

namespace Ui {
class RightMenu;
}

class RightMenu : public QWidget
{
    Q_OBJECT
    
public:
    explicit RightMenu(QWidget *parent = 0);
    ~RightMenu();

    void clear();
    
signals:
    void askDisconnection();

    void askSendMessage(QString);
    void addMsg(QString);

    void addPlayerToView(player);
    void rmPlayerFromView(player);

    void askNewGameWith(player);

private slots:
    void on_pushButton_clicked();

private:
    Ui::RightMenu *ui;

};

#endif // RIGHTMENU_H
