#include "my_board.h"
#include "./ui_myboard.h"
#include <QMessageBox>
#include <QPixmap>
#include <QtGui>
#include <QtCore>



MyBoard::MyBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyBoard)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015/INF1015_t17/PROJET_FINAL/prise15/ChessBoard/ressources/tour.png");
    ui->label_image->setPixmap(pix);
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)), ui->progressBar,SLOT(setValue(int)));
    //----------gridBox grid;
    //-------- makeBoard();
        

}

MyBoard::~MyBoard()
{
    delete ui;
}


void MyBoard::on_pushButton_sg_clicked()
{
    QMessageBox::about(this, "Game message : ", "Starting the game! ");
}

void MyBoard::makeBoard()
{
    QMessageBox::about(this, "Game message : ", "constructing the board! ");


    QPixmap pix1("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015/INF1015_t17/PROJET_FINAL/prise15/ChessBoard/ressources/blackTile.png");
    QPixmap pix2("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015/INF1015_t17/PROJET_FINAL/prise15/ChessBoard/ressources/whiteTile.png");
    QPixmap pix3("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015/INF1015_t17/PROJET_FINAL/prise15/ChessBoard/ressources/whiteTile.png");
    QPixmap pix4("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015/INF1015_t17/PROJET_FINAL/prise15/ChessBoard/ressources/blackTile.png");


    //QLabel* label1 = new QLabel("a");;
    //QLabel* label2 = new QLabel("b");
    //QLabel* label3 = new QLabel("c");
    //QLabel* label4 = new QLabel("d");

    QLabel* label5 = new QLabel();
    label5->setPixmap(pix1);
    QLabel* label6 = new QLabel();
    label6->setPixmap(pix2);
    QLabel* label7 = new QLabel();
    label7->setPixmap(pix3);
    QLabel* label8 = new QLabel();
    label8->setPixmap(pix4);



    ui->gridBoardLayout->addWidget(label5,0,0);
    ui->gridBoardLayout->addWidget(label6,0,1);
    ui->gridBoardLayout->addWidget(label7,1,0);
    ui->gridBoardLayout->addWidget(label8,1,1);


}

