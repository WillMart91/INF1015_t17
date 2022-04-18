#include "AbsPiece.h"
#include <QGraphicsTextItem>
#include <QBrush>

AbsPiece::AbsPiece(bool black, QString pieceImage, Position position, QGraphicsItem* parent) : QGraphicsRectItem(parent) {

    if (black)
        color = black;
    else
        color = white;


    pos = position;
    setRect(pos.rank, pos.file, SQUARE_SIZE, SQUARE_SIZE);


    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color);
    setBrush(brush);

    text = new QGraphicsTextItem("G", this);
    text->setScale(3);
    text->setPos(pos.rank, pos.file);

    setAcceptHoverEvents(true);
}

void AbsPiece::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit Pressed();
}

void AbsPiece::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(blue);
    setBrush(brush);
}

void AbsPiece::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(color);
    setBrush(brush);
}

Position AbsPiece::getPos()
{
    return pos;
}