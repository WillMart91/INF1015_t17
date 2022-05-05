#include "GameButton.h"

GameButton::GameButton(QString buttonText, int posX, int posY, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    setRect(0,0,200,50);

    //ADDING THE PIECE TEXT TO THE TILE (empty for now)
    text = new QGraphicsTextItem(buttonText, this);
    int x =rect().width()/2 - text-> boundingRect().width()/2;
    int y = rect().height() / 2 - text->boundingRect().height() / 2;
    text->setScale(4);
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

