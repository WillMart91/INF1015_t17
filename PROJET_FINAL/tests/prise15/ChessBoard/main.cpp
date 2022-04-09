#include "my_board.h"
#include <QApplication>

#include <QtGui>
#include <QtCore>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyBoard w;
    w.show();



    w.makeBoard();
    return a.exec();
}
