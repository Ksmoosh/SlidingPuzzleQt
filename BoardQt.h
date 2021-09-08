#ifndef BOARDQT_H
#define BOARDQT_H

#include <QVector>
#include <QObject>
#include "SquareQt.h"
#include "puzzle.h"

class BoardQt : public QObject
{
    Q_OBJECT
public:
    BoardQt(int scene_rect, int side);
    QVector<SquareQt*> setupSquares(QGraphicsScene *scene, PuzzleBoard &randomBoard);
    QVector<SquareQt*> squares;
    SquareQt* emptySquare;
    void solvedPopup();
    int rect_size;
    int side;
    int num_squares;
    Puzzle *puzzle;
public slots:
    void updateBoard(int move);
};

#endif // BOARDQT_H
