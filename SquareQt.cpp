#include "SquareQt.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtWidgets>
#include <QtCore>

SquareQt::SquareQt(int rectSize, int positionX, int positionY,
                   bool isMovable, bool isEmpty, int id, int position,
                   SquareQt* emptySquare, QGraphicsTextItem *text)
    : QObject(), QGraphicsRectItem()
{
    this->id = id;
    this->isMovable = isMovable;
    this->isEmpty = isEmpty;
    this->size = rectSize;
    this->emptySquare = emptySquare;
    this->setRect(0, 0, rectSize, rectSize);
    this->setX(positionX);
    this->setY(positionY);
    if(!this->isEmpty)
    {
        this->position = position;
        this->setText(text);
    }
    if(isMovable)
    {
        this->setAsMovable();
    }
    else if(isEmpty)
    {
        this->setBrush(QBrush(QColor(255, 0, 0, 50)));
    }
    else
    {
        this->setAsNonMovable();
    }
}

int SquareQt::get_position()
{
    return this->position;
}

void SquareQt::setAsMovable()
{
    this->setBrush(QBrush(QColor(255, 0, 0, 255)));
    this->setFlag(QGraphicsItem::ItemIsMovable);
}

void SquareQt::setAsNonMovable()
{
    this->setBrush(QBrush(QColor(255, 0, 0, 255)));
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
}

void SquareQt::setText(QGraphicsTextItem *text)
{
    this->text = text;
    if(this->id != 0)
    {
        text->setPlainText(QString::number(this->id));
        text->setFont(QFont("Arial", 35));
    }
    text->setPos(this->x(), this->y());
    this->setParentItem(text);
    this->setFlag(QGraphicsItem::ItemStacksBehindParent);
}

void SquareQt::setEmptySquare(SquareQt *emptySquare)
{
    this->emptySquare = emptySquare;
}

bool SquareQt::movableArea()
{
    // Make sure that the square is moving only horizontally or diagonally
    // and through allowed areas
    if (this->collidesWithItem(this->emptySquare, Qt::IntersectsItemBoundingRect)) {
        return true;
    }
    else {
        return false;
    }
}

void SquareQt::setPosition(int position)
{
    this->position = position;
}

void SquareQt::setPos(const QPointF &pos)
{
    QGraphicsRectItem::setPos(pos);
    this->text->setPos(pos);
}

void SquareQt::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && (flags() & ItemIsMovable)) {
        QPointF *toMove;
        // restrict moves alongside one of the axis
        if(this->moveVertical)
            toMove = new QPointF(this->x(), (this->pos() - lastMousePos + event->scenePos()).y());
        else
            toMove = new QPointF((this->pos() - lastMousePos + event->scenePos()).x(), this->y());
        lastMousePos = event->scenePos();
        if(movableArea())
        {
            this->setPos(*toMove);
        }
    }
}

void SquareQt::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && (flags() & ItemIsMovable)) {
        // check if the move has to be along vertical or horizontal axis.
        // To do that, check if moving up or down takes the square closer
        // to the empty square's top left corner. If so, the move has to
        // be vertical
        QPointF moveUp = this->pos() + QPointF(0, 1);
        QPointF moveDown = this->pos() + QPointF(0, -1);
        if((this->emptySquare->pos() - moveUp).manhattanLength() < (this->emptySquare->pos() - this->pos()).manhattanLength() ||
                (this->emptySquare->pos() - moveDown).manhattanLength() < (this->emptySquare->pos() - this->pos()).manhattanLength())
            this->moveVertical = true;
        else
            this->moveVertical = false;
        lastMousePos = event->scenePos();
        this->beforeMove=this->pos();
    }
}

void SquareQt::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if ((event->button() & Qt::LeftButton) && (flags() & ItemIsMovable)) {
        if((this->emptySquare->pos() - this->pos()).manhattanLength() < (this->beforeMove - this->pos()).manhattanLength())
        {
            this->setPos(this->emptySquare->pos());
            int position = this->position;
            this->setPosition(this->emptySquare->position);
            this->emptySquare->setPosition(position);
            this->emptySquare->setPos(this->beforeMove);
            emit this->moveMade(position);
        }
        else
        {
            this->setPos(this->beforeMove);
        }
    }
}


