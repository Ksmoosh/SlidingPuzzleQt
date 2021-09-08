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
    void solvedPopup();

    QVector<SquareQt*> squares;
    SquareQt* emptySquare;
    Puzzle *puzzle;
public slots:
    void updateBoard(int move);
private:
    int rect_size;
    int side;
    int num_squares;
};

#endif // BOARDQT_H
