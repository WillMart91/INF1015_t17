#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(Position position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem *parent): QGraphicsRectItem(parent){

    color1 = baseColor;
    color2 = hoverColor;
    pos = position;
    setRect(pos.rank , pos.file, sizeX, sizeY);
    

    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color1);
    setBrush(brush);

    //text = new QGraphicsTextItem("G", this);
    //text->setScale(3);
    ////int xPos = rect().width() / 2 - text->boundingRect().width() / 2;
    ////int yPos = rect().height() / 2 - text->boundingRect().height() / 2;
    //text->setPos(pos.rank, pos.file);

    setAcceptHoverEvents(true);
}

void Button::clickEvent(QGraphicsSceneMouseEvent *event)
{
    emit Pressed();
}

void Button::hoverEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color2);
    setBrush(brush);
}

void Button::offHoverEvent(QGraphicsSceneHoverEvent *event)
{
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color1);
    setBrush(brush);
}

Position Button::getPos()
{
    return pos;
}