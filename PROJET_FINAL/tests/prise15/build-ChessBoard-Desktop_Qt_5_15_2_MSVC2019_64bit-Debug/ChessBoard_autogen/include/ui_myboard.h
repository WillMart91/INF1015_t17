/********************************************************************************
** Form generated from reading UI file 'myboard.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYBOARD_H
#define UI_MYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyBoard
{
public:
    QAction *actionv;
    QWidget *centralwidget;
    QPushButton *pushButton_np;
    QPushButton *pushButton_sg;
    QLabel *label_image;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QProgressBar *progressBar;
    QWidget *gridLayoutWidget;
    QGridLayout *gridBoardLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuTRYING;
    QMenu *menug;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuversion_1_0;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MyBoard)
    {
        if (MyBoard->objectName().isEmpty())
            MyBoard->setObjectName(QString::fromUtf8("MyBoard"));
        MyBoard->resize(729, 559);
        actionv = new QAction(MyBoard);
        actionv->setObjectName(QString::fromUtf8("actionv"));
        centralwidget = new QWidget(MyBoard);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_np = new QPushButton(centralwidget);
        pushButton_np->setObjectName(QString::fromUtf8("pushButton_np"));
        pushButton_np->setGeometry(QRect(20, 440, 151, 71));
        pushButton_sg = new QPushButton(centralwidget);
        pushButton_sg->setObjectName(QString::fromUtf8("pushButton_sg"));
        pushButton_sg->setGeometry(QRect(230, 440, 171, 71));
        label_image = new QLabel(centralwidget);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setGeometry(QRect(30, 20, 371, 401));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(450, 430, 247, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(layoutWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(50);

        verticalLayout->addWidget(progressBar);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(410, 130, 301, 201));
        gridBoardLayout = new QGridLayout(gridLayoutWidget);
        gridBoardLayout->setObjectName(QString::fromUtf8("gridBoardLayout"));
        gridBoardLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(40, 70, 256, 192));
        MyBoard->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MyBoard);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 729, 19));
        menuTRYING = new QMenu(menubar);
        menuTRYING->setObjectName(QString::fromUtf8("menuTRYING"));
        menug = new QMenu(menubar);
        menug->setObjectName(QString::fromUtf8("menug"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menuversion_1_0 = new QMenu(menubar);
        menuversion_1_0->setObjectName(QString::fromUtf8("menuversion_1_0"));
        MyBoard->setMenuBar(menubar);
        statusbar = new QStatusBar(MyBoard);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MyBoard->setStatusBar(statusbar);

        menubar->addAction(menuTRYING->menuAction());
        menubar->addAction(menug->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menuversion_1_0->menuAction());
        menuTRYING->addSeparator();
        menuTRYING->addSeparator();
        menuTRYING->addSeparator();
        menug->addSeparator();
        menug->addAction(actionv);

        retranslateUi(MyBoard);

        QMetaObject::connectSlotsByName(MyBoard);
    } // setupUi

    void retranslateUi(QMainWindow *MyBoard)
    {
        MyBoard->setWindowTitle(QCoreApplication::translate("MyBoard", "MyBoard", nullptr));
        actionv->setText(QCoreApplication::translate("MyBoard", "v", nullptr));
        pushButton_np->setText(QCoreApplication::translate("MyBoard", "I have no purpose :(", nullptr));
        pushButton_sg->setText(QCoreApplication::translate("MyBoard", "Start Game", nullptr));
        label_image->setText(QString());
        menuTRYING->setTitle(QCoreApplication::translate("MyBoard", "ChessGame", nullptr));
        menug->setTitle(QString());
        menu->setTitle(QString());
        menu_2->setTitle(QString());
        menuversion_1_0->setTitle(QCoreApplication::translate("MyBoard", "version_1.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyBoard: public Ui_MyBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYBOARD_H
