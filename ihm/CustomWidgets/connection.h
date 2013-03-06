#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class Connection;
}

class Connection : public QWidget
{
    Q_OBJECT
    
public:
    explicit Connection(QWidget *parent = 0);
    ~Connection();
    
    void clean();

protected:
    void paintEvent(QPaintEvent *); // Override of painEvent.

signals:
    void askConnection(QString host, int port, QString pseudo);

private slots:
    void on_connectPushButton_clicked();

    void on_pseudoLineEdit_textChanged(const QString &arg1);

private:
    Ui::Connection *ui;
};

#endif // CONNECTION_H
