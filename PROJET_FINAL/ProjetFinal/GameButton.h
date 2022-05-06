#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsTextItem>
//OTHER


/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: A GameButton if simply a button on the screen. Their only task is notifying the "Game" class when an event occurs
*/

using namespace std;
using namespace Qt;

class GameButton :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // CTOR + DTOR
    GameButton(QString buttonText, int posX, int posY, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent = NULL);
    ~GameButton() = default;

    // EVENTS RELATED METHODS
    void mousePressEvent(QGraphicsSceneMouseEvent* event) { emit Clicked(); }
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) { setBrush(*darkerBrush); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) { setBrush(*lighterBrush); }

signals:
    void Clicked();

private:
    QGraphicsTextItem* text;
    QBrush* lighterBrush;
    QBrush* darkerBrush;
};






