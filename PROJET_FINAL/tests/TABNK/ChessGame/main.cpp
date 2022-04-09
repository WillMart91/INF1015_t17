#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsRectItem* rect = new QGraphicsRectItem();
    //rect->setRect(0, 0, 100, 100);
    //rect->setBrush(Qt::red);
    //rect->setOpacity(0.7);


    for(int i =0; i< 8; i++)
    {
        for(int j =0; j< 8; j++)
        {
            QGraphicsRectItem* rect = new QGraphicsRectItem();
            if((i+j)%2)
            {
                rect->setRect(i*100, j*100, 100, 100);
                rect->setBrush(Qt::red);
                rect->setOpacity(0.7);
            }
            else
            {
                rect->setRect(i*100, j*100, 100, 100);
            }

        }
    }
    scene->addItem(rect);
    QGraphicsView* view = new QGraphicsView(scene);
    view->show();
    return a.exec();
}






