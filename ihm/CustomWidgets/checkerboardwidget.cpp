#include "checkerboardwidget.h"
#include "ui_checkerboardwidget.h"

#include <QDebug>
#include <QGraphicsEffect>


CheckerBoardWidget::CheckerBoardWidget(QWidget *parent) :
    QWidget(parent), player_color(BLACK_CHECKER),
    ui(new Ui::CheckerBoardWidget)
{
    ui->setupUi(this);

    firstClick = QPointF(-1,-1);
    secondClick = QPointF(-1,-1);

    init();

}

CheckerBoardWidget::~CheckerBoardWidget()
{
    delete board;
    delete ui;
}

void CheckerBoardWidget::move()
{
    movement m;
    m.startPoint.line = firstClick.y();
    m.startPoint.column = firstClick.x();
    m.endPoint.line = secondClick.y();
    m.endPoint.column = secondClick.x();

    qDebug() << "[Move] ";
    qDebug() << "[MOVEMENT] : start (" << m.startPoint.line << ", " << m.startPoint.column << ")";
    qDebug() << "[MOVEMENT] : end (" << m.endPoint.line << ", " << m.endPoint.column << ")";


    if(test_and_execute_movement(player_color, m, board) != 0){
        //Valid movement, do it for gui
        qDebug() << "movement is ok";
        //_scene->removeItem(_scene->itemAt(firstClick.x()*CELL_SIZE, firstClick.y()*CELL_SIZE));
//        whites.clear();
//        blacks.clear();
//        empties.clear();
        clearList();

        qDebug() << "size of list : " << whites.size();

        _scene->update(QRectF(firstClick.x()*CELL_SIZE, firstClick.y()*CELL_SIZE, CELL_SIZE, CELL_SIZE));
        placeChecker();

        //Change palyer
//        if(player_color<0){
//            player_color = WHITE_CHECKER;
//        }else{
//            player_color = BLACK_CHECKER;
//        }
        qDebug() << "next player is " << player_color;

    }
}

void CheckerBoardWidget::init()
{
    _scene = new QGraphicsScene(this);

    _checkerboard_o = new CheckerBoardObject;

    board =  (checkerboard *) calloc(sizeof(checkerboard), 1);
    init_gameboard(board);

    //TODO fill QList
    placeChecker();

    ui->checkerboardGraphicsView->setScene(_scene);

}

void CheckerBoardWidget::placeChecker()
{
    _checkerboard_o->setZValue(1);
    _scene->addItem(_checkerboard_o);
    _checkerboard_o->setPos(0,0);

    int i;
    int j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(board->gameboard[i][j] == BLACK_CHECKER){
                CheckerObject * black = new CheckerObject(BLACK_CHECKER);
                connect(black, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
                black->setPos(CELL_SIZE*j, CELL_SIZE*i);
                black->setZValue(2);
                blacks.append(black);
                _scene->addItem(black);
            }

            if(board->gameboard[i][j] == WHITE_CHECKER){
                CheckerObject * white = new CheckerObject(WHITE_CHECKER);
                connect(white, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
                white->setPos(CELL_SIZE*j, CELL_SIZE*i);
                white->setZValue(2);
                blacks.append(white);
                _scene->addItem(white);
            }

            if(board->gameboard[i][j] == EMPTY_CELL){
                CheckerObject * empty = new CheckerObject(EMPTY_CELL);
                connect(empty, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
                empty->setPos(CELL_SIZE*j, CELL_SIZE*i);
                empty->setZValue(2);
                empties.append(empty);
                _scene->addItem(empty);
            }
        }
    }
}

void CheckerBoardWidget::clearList()
{
    foreach(CheckerObject * o, whites){
        _scene->removeItem(o);
    }
    foreach(CheckerObject * o, blacks){
        _scene->removeItem(o);
    }
    foreach(CheckerObject * o, empties){
        _scene->removeItem(o);
    }
            whites.clear();
            blacks.clear();
            empties.clear();

}

void CheckerBoardWidget::itemClicked(QPointF p)
{
    // If we do the first click
    if(firstClick.x() == -1){
        firstClick = QPointF(p.x()/CELL_SIZE, p.y()/CELL_SIZE);
    }else{
        // We do the second click
        if(firstClick.x() != -1 && secondClick.x() == -1){
            secondClick = QPointF(p.x()/CELL_SIZE, p.y()/CELL_SIZE);
            move();
        }
        else{
            firstClick = QPointF(p.x()/CELL_SIZE, p.y()/CELL_SIZE);
            secondClick = QPointF(-1,-1);
        }
    }
    qDebug() << "First : " << firstClick;
    qDebug() << "Second : " << secondClick;
}
