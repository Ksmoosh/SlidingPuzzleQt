
#include "mainwindow.h"
#include "SquareQt.h"
#include "BoardQt.h"
#include <QApplication>
#include <QMouseEvent>
#include <QVector>
#include <QObject>
#include <QMessageBox>
#include <QPushButton>

#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <memory>

#include "square.h"
#include "puzzleBoard.h"
#include "puzzle.h"

//#include "main.moc"

using namespace std;

int SCENE_RECT = 800;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int puzzle_dim;
    //MainWindow w;
    //w.show();

    QMessageBox dimChooseBox;
    dimChooseBox.setWindowTitle("Witaj w grze!");
    QAbstractButton* button2dim = dimChooseBox.addButton(QObject::tr("2x2"), QMessageBox::YesRole);
    QAbstractButton* button3dim = dimChooseBox.addButton(QObject::tr("3x3"), QMessageBox::YesRole);
    QAbstractButton* button4dim = dimChooseBox.addButton(QObject::tr("4x4"), QMessageBox::YesRole);
    dimChooseBox.setText(QStringLiteral("Witaj! Wybierz wymiary puzzli:"));
//    dimChooseBox.setStandardButtons(QMessageBox::Ok);
//    dimChooseBox.setButtonText(QMessageBox::Ok, QObject::tr("Zakończ"));
//    dimChooseBox.setDefaultButton(QMessageBox::Ok);
    dimChooseBox.exec();
    if(dimChooseBox.clickedButton()==button2dim)
    {
        puzzle_dim = 2;
    }
    else if(dimChooseBox.clickedButton()==button3dim)
    {
        puzzle_dim = 3;
    }
    else if(dimChooseBox.clickedButton()==button4dim)
    {
        puzzle_dim = 4;
    }
    else
    {
        QCoreApplication::quit();
    }

    // setting up scene
    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCENE_RECT, SCENE_RECT);

    // setting up view
    QGraphicsView * view = new QGraphicsView();
    view->setFixedSize(SCENE_RECT, SCENE_RECT);

    BoardQt *board = new BoardQt(SCENE_RECT, puzzle_dim);

    Puzzle *puzzle = new Puzzle(puzzle_dim);
    board->puzzle = puzzle;
    board->puzzle->setup_board();

    QVector<SquareQt*> squares = board->setupSquares(scene, board->puzzle->puzzleBoard);
    for(int i=0; i < squares.size(); i++)
    {
        QObject::connect(squares[i], &SquareQt::moveMade,
                         board, &BoardQt::updateBoard);
    }
    board->squares = squares;

    view->setScene(scene);
    view->show();
    return a.exec();
}

//#include <QtWidgets>

//class Steer : public QGraphicsView
//{
//public:
//    Steer()
//    {
//        scene = new QGraphicsScene;
//        p1 = new QGraphicsRectItem;

//        //add player
//        p1->setRect(0, 0, 10, 80);
//        p1->setX(760);
//        p1->setY(160);

//        //add scene
//        scene->setSceneRect(0, 0, 800, 400);

//        //add moveable item
//        scene->addItem(p1);

//        //set scene
//        this->setScene(scene);
//        this->show();
//    }

//protected:
//    void mousePressEvent(QMouseEvent * click)
//    {
//        if (p1->contains(p1->mapFromScene(click->localPos()))) {
//            lastMousePos = click->pos();
//        } else {
//            lastMousePos = QPoint(-1, -1);
//        }
//    }

//    void mouseMoveEvent(QMouseEvent * event)
//    {
//        if(!(event->buttons() & Qt::LeftButton)) {
//            return;
//        }

//        if (lastMousePos == QPoint(-1, -1)) {
//            return;
//        }

//        p1->setPos(p1->pos() + (event->localPos() - lastMousePos));
//        lastMousePos = event->pos();
//    }

//private:
//    QGraphicsScene *scene;
//    QGraphicsRectItem *p1;

//    QPoint lastMousePos;
//};

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    Steer w;
//    w.show();

//    return a.exec();
//}
