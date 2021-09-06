#ifndef BOARDQT_H
#define BOARDQT_H

#include <QVector>
#include "SquareQt.h"

class BoardQt
{
public:
    BoardQt(int scene_rect, int side);
    QVector<SquareQt*> setupSquares(QGraphicsScene *scene);
    QVector<SquareQt*> squares;
    SquareQt* emptySquare;
    int rect_size;
    int side;
    int num_squares;
};

#endif // BOARDQT_H
