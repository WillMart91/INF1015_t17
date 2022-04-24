#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(Position position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent) : QGraphicsRectItem(parent) {

    color1 = baseColor;
    color2 = hoverColor;
    pos = position;
    setRect(HORIZONTAL_MARGIN + (position.rank * SQUARE_SIZE), VERTICAL_MARGIN + (position.file * SQUARE_SIZE), sizeX, sizeY);
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color1);
    setBrush(brush);
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit Clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    emit Hovered();
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color2);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    emit OffHovered();
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color1);
    setBrush(brush);
}

Position Button::getPos()
{
    return pos;
}
