#ifndef SQUAREQT_H
#define SQUAREQT_H

#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QObject>

class SquareQt: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    SquareQt(int rectSize, int positionX, int positionY, bool isMovable, bool isEmpty, int id, int position=0, SquareQt* emptySquare=0, QGraphicsTextItem *text=0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    int get_position();

    void setText(QGraphicsTextItem *text);
    void setEmptySquare(SquareQt *emptySquare);
    void setAsMovable();
    void setAsNonMovable();
    void setEmptySquarePos(QPointF &pos);
    void setPos(const QPointF &pos);
    void setPosition(int position);

    void move(const QPointF &pos);
    bool movableArea();
    bool moveVertical;

signals:
    void moveMade(int move);

private:
    SquareQt* emptySquare;
    QGraphicsTextItem* text;
    QPointF beforeMove;
    QPoint offset;
    QPointF lastMousePos;
    int size;
    int id;
    int position;
    bool isMovable;
    bool isEmpty;

};

#endif // SQUAREQT_H
