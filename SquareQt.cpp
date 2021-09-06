#include "SquareQt.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtWidgets>
#include <QtCore>

SquareQt::SquareQt(int rectSize, int positionX, int positionY, bool isMovable, bool isEmpty, int id, SquareQt* emptySquare, QGraphicsTextItem *text) : QGraphicsRectItem()
{
    this->id = id;
    this->isMovable = isMovable;
    this->isEmpty = isEmpty;
    this->size = rectSize;
    this->emptySquare = emptySquare;
    this->text = text;
    this->setRect(0, 0, rectSize, rectSize);
    this->setX(positionX);
    this->setY(positionY);
    if(!this->isEmpty)
        text->setPlainText(QString::number(this->id));
    text->setFont(QFont("Arial", 35));
    text->setPos(positionX, positionY);
    this->setParentItem(text);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent);
//    this->setRect(text->boundingRect());
//    this->paint()
    if(isMovable)
    {
        this->setBrush(QBrush(QColor(0, 0, 255, 255)));
        this->setFlag(QGraphicsItem::ItemIsMovable);
    }
    else if(isEmpty)
    {
        this->setBrush(QBrush(QColor(255, 0, 0, 50)));
    }
    else
    {
        this->setBrush(QBrush(QColor(255, 0, 0, 255)));
    }
}

//void SquareQt::setEmptySquarePos(QPointF &pos)
//{
//    this->emptySquarePos=pos;
//}

bool SquareQt::movableArea(QPointF *point)
{
    // Make sure that the square is moving only horizontally or diagonally
    // and through allowed areas
    if ((this->emptySquare->contains(QPointF(point->x(), point->y() + this->size))
            && this->emptySquare->contains(QPointF(point->x(), point->y()))) ||
        (this->emptySquare->contains(QPointF(point->x() + this->size, point->y()))
            && this->emptySquare->contains(QPointF(point->x(), point->y())))) {
        qDebug() << "gello";
        return true;//TODO dont move to the field of another movable square
    }
    else {
        qDebug() << "kokokokko";
        return false;
    }
}

void SquareQt::setPos(const QPointF &pos)
{
    QGraphicsRectItem::setPos(pos);
    this->text->setPos(pos);
}

void SquareQt::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && (flags() & ItemIsMovable)) {
        qDebug() << event->scenePos() << " " << this->pos();
        QPointF toMove = this->pos() - lastMousePos + event->scenePos();
        lastMousePos = event->scenePos();
        if(movableArea(&toMove))
        {
            this->setPos(toMove);
        }
    }
}

void SquareQt::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && (flags() & ItemIsMovable)) {
        qDebug() << "event->scenePos() << " " << this->pos()";
        lastMousePos = event->scenePos();
        this->beforeMove=this->pos();
    }
}

void SquareQt::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->button() & Qt::LeftButton) && (flags() & ItemIsMovable)) {
        qDebug() << "Released";
        if((this->emptySquare->pos() - this->pos()).manhattanLength() < (this->beforeMove - this->pos()).manhattanLength())
        {
            this->setPos(this->emptySquare->pos());
            this->emptySquare->setPos(this->beforeMove);
        }
        else
        {
            this->setPos(this->beforeMove);
        }
    }
}


