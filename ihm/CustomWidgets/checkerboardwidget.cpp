#include "checkerboardwidget.h"
#include "ui_checkerboardwidget.h"

CheckerBoardWidget::CheckerBoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckerBoardWidget)
{
    ui->setupUi(this);

    init();



}

CheckerBoardWidget::~CheckerBoardWidget()
{
    delete board;
    delete ui;
}

void CheckerBoardWidget::init()
{
    _scene = new QGraphicsScene(this);

    _checkerboard_o = new CheckerBoardObject;
    _checkerboard_o->setZValue(1);
    _scene->addItem(_checkerboard_o);
    _checkerboard_o->setPos(0,0);

    ui->checkerboardGraphicsView->setScene(_scene);

    board =  (checkerboard *) calloc(sizeof(checkerboard), 1);
    init_gameboard(board);

    //TODO fill QList
    int i;
    int j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(board->gameboard[i][j] == BLACK_CHECKER){
                CheckerObject * black = new CheckerObject(BLACK_CHECKER);
                black->setPos(CELL_SIZE*j, CELL_SIZE*i);
                black->setZValue(2);
                blacks.append(black);
                _scene->addItem(black);
            }

            if(board->gameboard[i][j] == WHITE_CHECKER){
                CheckerObject * white = new CheckerObject(WHITE_CHECKER);
                white->setPos(CELL_SIZE*j, CELL_SIZE*i);
                white->setZValue(2);
                blacks.append(white);
                _scene->addItem(white);
            }
        }
    }
}
