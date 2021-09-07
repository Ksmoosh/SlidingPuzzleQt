#include "SquareQt.h"
#include "BoardQt.h"
#include "puzzleBoard.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtWidgets>
#include <QtCore>

BoardQt::BoardQt(int scene_rect, int side_squares) :
    QObject(), rect_size(scene_rect / side_squares), num_squares(side_squares * side_squares), side(side_squares) {   }

QVector<SquareQt*> BoardQt::setupSquares(QGraphicsScene *scene, PuzzleBoard &board)
{
    int offsetX = 0;
    int offsetY = 0;
    SquareQt * rect;
    QGraphicsTextItem *text;
    this->emptySquare = new SquareQt(this->rect_size, offsetX, offsetY, false, true, 0);
    QVector<SquareQt*> squares(board.randomBoard.size());
    for(int i = 0; i < board.randomBoard.size(); i++)
    {
        text = new QGraphicsTextItem();
        if(board.is_movable(i))
            rect = new SquareQt(this->rect_size, offsetX, offsetY, true, false, board.randomBoard[i].get_id(), i, this->emptySquare, text);
        else if(board.randomBoard[i].get_id() == 0)
        {
//            rect = new SquareQt(this->rect_size, offsetX, offsetY, false, true, board.randomBoard[i].get_id(), this->emptySquare, text);
            this->emptySquare->setEmptySquare(this->emptySquare);
            this->emptySquare->setText(text);
            this->emptySquare->setPos(QPointF(offsetX, offsetY));
            this->emptySquare->setPosition(i);
            rect = this->emptySquare;
        }
        else
            rect = new SquareQt(this->rect_size, offsetX, offsetY, false, false, board.randomBoard[i].get_id(), i, this->emptySquare, text);
        squares[i] = rect;
        scene->addItem(rect);
        scene->addItem(text);
        if ((i+1) % side == 0)
        {
            offsetX = 0;
            offsetY += this->rect_size;
        }
        else
        {
            offsetX += this->rect_size;
        }
    }
    return squares;
}

void BoardQt::updateBoard(int move)
{
    qDebug() << this->puzzle->get_movables();
    this->puzzle->switchSquares(this->puzzle->puzzleBoard, move);
    this->puzzle->set_movables(this->puzzle->puzzleBoard);
    qDebug() << this->puzzle->get_movables();
    for(int i = 0; i < this->squares.size(); i++)
    {

    }
}
