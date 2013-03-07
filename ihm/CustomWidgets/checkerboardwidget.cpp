#include "checkerboardwidget.h"
#include "ui_checkerboardwidget.h"

#include <QDebug>
#include <QGraphicsEffect>


CheckerBoardWidget::CheckerBoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckerBoardWidget),  player_color(WHITE_CHECKER)
{
    ui->setupUi(this);

    firstClick = QPointF(-1,-1);
    secondClick = QPointF(-1,-1);

    //init();

}

CheckerBoardWidget::~CheckerBoardWidget()
{
//    delete board;
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


    if(test_and_execute_movement(player_color, m, &board) != 0){
        //Valid movement, do it for gui
        qDebug() << "movement is ok";

        clearLists();

        placeCheckers();

        //Change palyer
        //changePlayer();

//        qDebug() << "ppppppppppppppppppppppppppppppp" << (char *) board;
        emit sendCheckerboard(board);


    }
}

void CheckerBoardWidget::clear()
{
    _scene->clear();
}

void CheckerBoardWidget::init(player white, player black)
{
    _scene = new QGraphicsScene(this);

    QGraphicsItem * white_player = new QGraphicsPixmapItem(QPixmap(":/icons/whitechecker"));
    QGraphicsItem * black_player = new QGraphicsPixmapItem(QPixmap(":/icons/blackchecker"));

    QGraphicsItem * white_name = new QGraphicsTextItem(white.name);
    QGraphicsItem * black_name = new QGraphicsTextItem(black.name);

    QGraphicsItem * turn_player;
    if(player_color == WHITE_CHECKER) {
        turn_player = new QGraphicsTextItem(QString(QString::fromStdString(white.name) + tr(" turn")));
    }else{
        turn_player = new QGraphicsTextItem(QString(QString::fromStdString(black.name) + tr(" turn")));
    }

    white_player->setPos(-200,0);
    white_name->setPos(-150,0);

    black_player->setPos(-200, 50);
    black_name->setPos(-150,50);

    turn_player->setPos(-200, 100);

    _scene->addItem(white_player);
    _scene->addItem(white_name);

    _scene->addItem(black_player);
    _scene->addItem(black_name);

    _scene->addItem(turn_player);

    init_gameboard(&board);

    //TODO fill QList
    placeCheckers();

    ui->checkerboardGraphicsView->setScene(_scene);

}

void CheckerBoardWidget::receiveCheckerboard(checkerboard c)
{
    board = c;
    this->clear();
    placeCheckers();
}

void CheckerBoardWidget::placeCheckers()
{
    _checkerboard_o = new CheckerBoardObject;
    _checkerboard_o->setZValue(1);
    _scene->addItem(_checkerboard_o);
    _checkerboard_o->setPos(0,0);

    int i;
    int j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(board.gameboard[i][j] == BLACK_CHECKER){
                CheckerObject * black = new CheckerObject(BLACK_CHECKER);
                connect(black, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
                black->setPos(CELL_SIZE*j, CELL_SIZE*i);
                black->setZValue(2);
                blacks.append(black);
                _scene->addItem(black);
            }

            if(board.gameboard[i][j] == WHITE_CHECKER){
                CheckerObject * white = new CheckerObject(WHITE_CHECKER);
                connect(white, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
                white->setPos(CELL_SIZE*j, CELL_SIZE*i);
                white->setZValue(2);
                blacks.append(white);
                _scene->addItem(white);
            }

            if(board.gameboard[i][j] == EMPTY_CELL){
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

void CheckerBoardWidget::clearLists()
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

void CheckerBoardWidget::changePlayer(int color)
{
    if(player_color == BLACK_CHECKER){
        player_color = WHITE_CHECKER;
    }else{
        player_color = BLACK_CHECKER;
    }
    if ( player_color == color ) {
        qDebug() << "MYYYYYY TUUUUURRRRRRNNNNNNNNNN";
    }
    else{
        foreach(CheckerObject * o, whites){
            disconnect(o, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
        }
        foreach(CheckerObject * o, blacks){
            disconnect(o, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
        }
        foreach(CheckerObject * o, empties){
            disconnect(o, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
        }
    }
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
