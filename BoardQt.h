#ifndef BOARDQT_H
#define BOARDQT_H

#include <QVector>
#include <QObject>
#include "SquareQt.h"
#include "puzzle.h"

/*
 * Ta klasa odpowiada za porozumiewanie się obiektów klasy Puzzle oraz SquareQt
 *
 * Każdy ruch w UI musi zostać przekazany do logiki puzzli i tabela stanu gry musi
 * zostać odpowiednio zaktualizowana. Po zaktualizowaniu stanu gry, informacja ta
 * jest przekazywana do każdego z SquareQt, stąd przykładowo wiadome jest, który
 * kwadrat może się ruszać po planszy.
 *
 * Klasa ta posiada również slot pod sygnał wysyłany przez SquareQt. Sygnał ten
 * jest informacją o zmianie stanu planszy i rozkazem do jej aktualizacji po
 * stronie logiki gry.
*/
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
