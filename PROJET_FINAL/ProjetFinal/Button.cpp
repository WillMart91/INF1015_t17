#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(Position position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent) : QGraphicsRectItem(parent) {

    color1 = baseColor;
    color2 = hoverColor;
    pos = position;
    setRect(pos.rank, pos.file, sizeX, sizeY);
    //setScale(3);

    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color1);
    setBrush(brush);

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit Pressed();
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(red);
    setBrush(brush);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color2);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
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
