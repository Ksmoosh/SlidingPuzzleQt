#ifndef SQUAREQT_H
#define SQUAREQT_H

#include <QGraphicsRectItem>
#include <QMouseEvent>

class SquareQt: public QGraphicsRectItem
{
public:
//    void mousePressEvent(QMouseEvent * event);
//    void mouseMoveEvent(QMouseEvent *event);
    SquareQt(int rectSize, int positionX, int positionY, bool isMovable, bool isEmpty, int id, SquareQt* emptySquare, QGraphicsTextItem *text=0);
    void move(const QPointF &pos);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    bool movableArea(QPointF *event);
    void setEmptySquarePos(QPointF &pos);
    void setPos(const QPointF &pos);
    QPoint offset;
    QPointF lastMousePos;
    SquareQt* emptySquare;
    QPointF beforeMove;
    QGraphicsTextItem* text;
    int id;
    int size;
    bool isMovable;
    bool isEmpty;
protected:
//    void mousePressEvent(QMouseEvent * click);
//    void mouseMoveEvent(QMouseEvent * event);

};

#endif // SQUAREQT_H
