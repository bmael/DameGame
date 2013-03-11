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

        clearLists();   // Clear all the gui gameboard

        placeCheckers(); // Reconstruct the new GUI gameboard

        //Check if there is a winner
        if(game_ended(&board) == BLACK_CHECKER){
            _player.color == BLACK_CHECKER ? emit sendWinner(_player) : emit sendWinner(_opponent_player);
        }
        if(game_ended(&board) == WHITE_CHECKER){
            _player.color == WHITE_CHECKER ? emit sendWinner(_opponent_player) : emit sendWinner(_player);
        }


        preventAction(player_color);
        changePlayer();

//        qDebug() << "ppppppppppppppppppppppppppppppp" << (char *) board;
        emit sendCheckerboard(board);


    }
}

void CheckerBoardWidget::clear()
{
    _scene->clear();
}

void CheckerBoardWidget::loadInformation()
{
    white_player = new QGraphicsPixmapItem(QPixmap(":/icons/whitechecker"));
    black_player = new QGraphicsPixmapItem(QPixmap(":/icons/blackchecker"));

    if(_player.color == WHITE_CHECKER){
        white_name = new QGraphicsTextItem(_player.name);
        black_name = new QGraphicsTextItem(_opponent_player.name);
        turn_player = new QGraphicsTextItem(QString(QString::fromStdString(_player.name) + tr(" turn")));
    }
    else{
        white_name = new QGraphicsTextItem(_opponent_player.name);
        black_name = new QGraphicsTextItem(_player.name);
        turn_player = new QGraphicsTextItem(QString(QString::fromStdString(_opponent_player.name) + tr(" turn")));
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

}

void CheckerBoardWidget::init(player p, player opponent)
{
    _scene = new QGraphicsScene(this);

//    pwhite = p;
//    pblack = opponent;
    _player = p;
    _opponent_player = opponent;

    loadInformation();

    _checkerboard_o = new CheckerBoardObject;
    _checkerboard_o->setZValue(1);
    _scene->addItem(_checkerboard_o);
    _checkerboard_o->setPos(0,0);

    init_gameboard(&board);
    placeCheckers();

    ui->checkerboardGraphicsView->setScene(_scene);

}

void CheckerBoardWidget::receiveCheckerboard(checkerboard c)
{
    board = c;
    clearLists();
    //this->clear();
    changePlayer();
    placeCheckers();
}

void CheckerBoardWidget::placeCheckers()
{

    qDebug() << "color that have to play : " << player_color;

    int i;
    int j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if(board.gameboard[i][j] == BLACK_CHECKER){
                CheckerObject * black = new CheckerObject(BLACK_CHECKER);
                if(player_color == BLACK_CHECKER && _player.color == BLACK_CHECKER)
                    connect(black, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
                black->setPos(CELL_SIZE*j, CELL_SIZE*i);
                black->setZValue(2);
                blacks.append(black);
                _scene->addItem(black);
            }

            if(board.gameboard[i][j] == WHITE_CHECKER){
                CheckerObject * white = new CheckerObject(WHITE_CHECKER);
                if(player_color == WHITE_CHECKER && _player.color == WHITE_CHECKER)
                    connect(white, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
                white->setPos(CELL_SIZE*j, CELL_SIZE*i);
                white->setZValue(2);
                blacks.append(white);
                _scene->addItem(white);
            }

            if(board.gameboard[i][j] == EMPTY_CELL){
                CheckerObject * empty = new CheckerObject(EMPTY_CELL);
                if(_player.color == player_color)
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

void CheckerBoardWidget::preventAction(int color)
{
    if(color == WHITE_CHECKER){
        foreach(CheckerObject * o, whites){
            disconnect(o, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
        }
    }else{
        foreach(CheckerObject * o, blacks){
            disconnect(o, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
        }
    }

    foreach(CheckerObject * o, empties){
        disconnect(o, SIGNAL(clicked(QPointF)), this, SLOT(itemClicked(QPointF)));
    }

}

void CheckerBoardWidget::changePlayer()
{
    qDebug() << "[CHANGE PLAYER]";
    if(player_color == BLACK_CHECKER){
        player_color = WHITE_CHECKER;   
    }else{
        player_color = BLACK_CHECKER;
    }

    if(player_color == _player.color){
        turn_player->setPlainText(QString(QString::fromStdString(_player.name) + tr(" turn")));
    }
    else{
        turn_player->setPlainText(QString(QString::fromStdString(_opponent_player.name) + tr(" turn")));
    }

}

void CheckerBoardWidget::itemClicked(QPointF p)
{
    // If we do the first click
    if(firstClick.x() == -1){
        firstClick = QPointF(p.x()/CELL_SIZE, p.y()/CELL_SIZE);
        CheckerObject * it = (CheckerObject *)_scene->itemAt(firstClick.x()*CELL_SIZE, firstClick.y()*CELL_SIZE);
        it->setEffectEnabled(true);
    }else{
        // We do the second click
        if(firstClick.x() != -1 && secondClick.x() == -1){
            secondClick = QPointF(p.x()/CELL_SIZE, p.y()/CELL_SIZE);
            CheckerObject * it = (CheckerObject *)_scene->itemAt(firstClick.x()*CELL_SIZE, firstClick.y()*CELL_SIZE);
            it->setEffectEnabled(false);

            it = (CheckerObject *)_scene->itemAt(secondClick.x()*CELL_SIZE, secondClick.y()*CELL_SIZE);
            it->setEffectEnabled(false);

            move();
        }
        else{
            firstClick = QPointF(p.x()/CELL_SIZE, p.y()/CELL_SIZE);
            secondClick = QPointF(-1,-1);
        }
    }
}
