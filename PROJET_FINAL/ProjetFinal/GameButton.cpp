#include "GameButton.h"

GameButton::GameButton(QString buttonText, int posX, int posY, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent) : QGraphicsRectItem(parent) {
    setRect(posX, posY, sizeX, sizeY);

    //ADDING THE PIECE TEXT TO THE TILE (empty for now)
    text = new QGraphicsTextItem(buttonText, this);
    int x = posX;
    int y = posY;
    text->setScale(1.5);
    text->setPos(x, y);

    //DEFINING THE BUTTON COLORS
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(baseColor);
    lighterBrush = new QBrush(brush);
    QBrush brush2;
    brush2.setStyle(SolidPattern);
    brush2.setColor(hoverColor);
    darkerBrush = new QBrush(brush2);

    //SET BASE COLOR AND ENABLE MOUSE ACTION
    setBrush(*lighterBrush);
    setAcceptHoverEvents(true);
}


