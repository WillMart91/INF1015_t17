#include "Tile.h"
#include <QGraphicsTextItem>
#include <QBrush>

Tile::Tile(Square position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent) : QGraphicsRectItem(parent) {

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

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit Clicked();
}

void Tile::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    emit Hovered();
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color2);
    setBrush(brush);
}

void Tile::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    emit OffHovered();
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color1);
    setBrush(brush);
}

void Tile::glow()
{
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color2);
    setBrush(brush);
}

void Tile::stopGlowing()
{
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color1);
    setBrush(brush);
}

Square Tile::getPos()
{
    return pos;
}
