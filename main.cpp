
#include "mainwindow.h"
#include "SquareQt.h"
#include "BoardQt.h"
#include <QApplication>
#include <QMouseEvent>
#include <QVector>

int SCENE_RECT = 800;

//QVector<SquareQt*> setupSquares(QGraphicsScene *scene)
//{
//    int offsetX = 0;
//    int offsetY = 0;
//    int side = 4;
//    int RECT_SIZE = SCENE_RECT / side;
//    int num_rects = side * side;
//    SquareQt * rect;

//    //
//    int movable1 = 1;
//    int movable2 = 4;
//    //
//    QVector<SquareQt*> squares(num_rects);
//    for(int i = 0; i < num_rects; i++)
//    {

//        if(i == movable1 or i == movable2)
//            rect = new SquareQt(RECT_SIZE, offsetX, offsetY, true, false, i);
//        else if(i == 0)
//            rect = new SquareQt(RECT_SIZE, offsetX, offsetY, false, true, i);
//        else
//            rect = new SquareQt(RECT_SIZE, offsetX, offsetY, false, false, i);
//        squares[i] = rect;
//        scene->addItem(rect);
//        if ((i+1) % side == 0)
//        {
//            offsetX = 0;
//            offsetY += RECT_SIZE;
//        }
//        else
//        {
//            offsetX += RECT_SIZE;
//        }
//    }
//    return squares;
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    // setting up scene
    QGraphicsScene * scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCENE_RECT, SCENE_RECT);

    // setting up view
    QGraphicsView * view = new QGraphicsView();
    view->setFixedSize(SCENE_RECT, SCENE_RECT);

    BoardQt board = BoardQt(SCENE_RECT, 4);
    QVector<SquareQt*> squares = board.setupSquares(scene);
//    SquareQt * rect = new SquareQt(RECT_SIZE, 0, 0);
//    SquareQt * rect2 = new SquareQt(RECT_SIZE, 100, 100);

//    scene->addItem(rect);
//    scene->addItem(rect2);

//    rect->setFlag(QGraphicsItem::ItemIsFocusable);
//    rect->setFocus();


    view->setScene(scene);
    view->show();
    return a.exec();
}

//#include <QtWidgets>

//class Steer : public QGraphicsView
//{
//public:
//    Steer()
//    {
//        scene = new QGraphicsScene;
//        p1 = new QGraphicsRectItem;

//        //add player
//        p1->setRect(0, 0, 10, 80);
//        p1->setX(760);
//        p1->setY(160);

//        //add scene
//        scene->setSceneRect(0, 0, 800, 400);

//        //add moveable item
//        scene->addItem(p1);

//        //set scene
//        this->setScene(scene);
//        this->show();
//    }

//protected:
//    void mousePressEvent(QMouseEvent * click)
//    {
//        if (p1->contains(p1->mapFromScene(click->localPos()))) {
//            lastMousePos = click->pos();
//        } else {
//            lastMousePos = QPoint(-1, -1);
//        }
//    }

//    void mouseMoveEvent(QMouseEvent * event)
//    {
//        if(!(event->buttons() & Qt::LeftButton)) {
//            return;
//        }

//        if (lastMousePos == QPoint(-1, -1)) {
//            return;
//        }

//        p1->setPos(p1->pos() + (event->localPos() - lastMousePos));
//        lastMousePos = event->pos();
//    }

//private:
//    QGraphicsScene *scene;
//    QGraphicsRectItem *p1;

//    QPoint lastMousePos;
//};

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    Steer w;
//    w.show();

//    return a.exec();
//}
