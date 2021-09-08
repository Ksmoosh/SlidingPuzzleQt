#ifndef SQUAREQT_H
#define SQUAREQT_H

#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QObject>

class SquareQt: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
//    void mousePressEvent(QMouseEvent * event);
//    void mouseMoveEvent(QMouseEvent *event);
    SquareQt(int rectSize, int positionX, int positionY, bool isMovable, bool isEmpty, int id, int position=0, SquareQt* emptySquare=0, QGraphicsTextItem *text=0);
    void move(const QPointF &pos);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void setText(QGraphicsTextItem *text);
    void setEmptySquare(SquareQt *emptySquare);
    void setAsMovable();
    void setAsNonMovable();
    bool movableArea(QPointF *event);
    bool moveVertical;
    void setEmptySquarePos(QPointF &pos);
    void setPos(const QPointF &pos);
    void setPosition(int position);
    QPoint offset;
    QPointF lastMousePos;
    SquareQt* emptySquare;
    QPointF beforeMove;
    QGraphicsTextItem* text;
    int position;
    int id;
    int size;
    bool isMovable;
    bool isEmpty;
signals:
    void moveMade(int move);
protected:
//    void mousePressEvent(QMouseEvent * click);
//    void mouseMoveEvent(QMouseEvent * event);

};

#endif // SQUAREQT_H
