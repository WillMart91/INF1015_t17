#ifndef MYBOARD_H
#define MYBOARD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MyBoard; }
QT_END_NAMESPACE

class MyBoard : public QMainWindow
{ 
    Q_OBJECT

public:
    MyBoard(QWidget *parent = nullptr);
    ~MyBoard();
    void makeBoard();

private slots:
    void on_pushButton_sg_clicked();

private:
    Ui::MyBoard *ui;

};
#endif // MYBOARD_H
