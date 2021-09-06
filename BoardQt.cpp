#include "SquareQt.h"
#include "BoardQt.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtWidgets>
#include <QtCore>

BoardQt::BoardQt(int scene_rect, int side_squares) :
    rect_size(scene_rect / side_squares), num_squares(side_squares * side_squares), side(side_squares) {   }

QVector<SquareQt*> BoardQt::setupSquares(QGraphicsScene *scene)
{
    int offsetX = 0;
    int offsetY = 0;
//    int side = 4;
//    int RECT_SIZE = scene_rect / side;
    SquareQt * rect;
    QGraphicsTextItem *text;
    //
    int movable1 = 1;
    int movable2 = 4;
    //
    QVector<SquareQt*> squares(this->num_squares);
    for(int i = 0; i < this->num_squares; i++)
    {
        text = new QGraphicsTextItem();
        if(i == movable1 or i == movable2)
            rect = new SquareQt(this->rect_size, offsetX, offsetY, true, false, i, this->emptySquare, text);
        else if(i == 0)
        {
            rect = new SquareQt(this->rect_size, offsetX, offsetY, false, true, i, this->emptySquare, text);
            this->emptySquare = rect;
        }
        else
            rect = new SquareQt(this->rect_size, offsetX, offsetY, false, false, i, this->emptySquare, text);
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
