#ifndef GRIDBOX_H
#define GRIDBOX_H

#include <QMainWindow>

class gridBox : public QMainWindow
{
    Q_OBJECT
public:
    gridBox();
    ~gridBox();
}
private:
    Ui::MyBoard* ui;

#endif // GRIDBOX_H



