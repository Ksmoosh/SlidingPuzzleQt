
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

using namespace std;

int SCENE_RECT = 800;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int puzzle_dim;

    QMessageBox dimChooseBox;
    dimChooseBox.setWindowTitle("Witaj w grze!");
    QAbstractButton* button2dim = dimChooseBox.addButton(QObject::tr("2x2"), QMessageBox::YesRole);
    QAbstractButton* button3dim = dimChooseBox.addButton(QObject::tr("3x3"), QMessageBox::YesRole);
    QAbstractButton* button4dim = dimChooseBox.addButton(QObject::tr("4x4"), QMessageBox::YesRole);
    dimChooseBox.setText(QStringLiteral("Witaj! Wybierz wymiary puzzli:"));

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
