#include "checkerboardwidget.h"
#include "ui_checkerboardwidget.h"

CheckerBoardWidget::CheckerBoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckerBoardWidget)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(this);

    _checkerboard_o = new CheckerBoardObject;
    _checkerboard_o->setZValue(1);
    _scene->addItem(_checkerboard_o);



    ui->checkerboardGraphicsView->setScene(_scene);
}

CheckerBoardWidget::~CheckerBoardWidget()
{
    delete ui;
}
