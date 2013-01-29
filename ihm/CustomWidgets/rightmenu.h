#ifndef LEFTMENU_H
#define LEFTMENU_H

#include <QWidget>

namespace Ui {
class RightMenu;
}

class RightMenu : public QWidget
{
    Q_OBJECT
    
public:
    explicit RightMenu(QWidget *parent = 0);
    ~RightMenu();
    
signals:
    void askDisconnection();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RightMenu *ui;

};

#endif // LEFTMENU_H
