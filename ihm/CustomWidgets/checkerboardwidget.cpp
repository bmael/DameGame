#include "checkerboardwidget.h"
#include "ui_checkerboardwidget.h"

CheckerBoardWidget::CheckerBoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckerBoardWidget)
{
    ui->setupUi(this);

//    init_gameboard(board);

    _scene = new QGraphicsScene(this);

    _checkerboard_o = new CheckerBoardObject;
    _checkerboard_o->setZValue(1);
    _scene->addItem(_checkerboard_o);
    _checkerboard_o->setPos(0,0);



    ui->checkerboardGraphicsView->setScene(_scene);
}

CheckerBoardWidget::~CheckerBoardWidget()
{
    delete ui;
}
