#include "Button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(Position position, QGraphicsItem *parent): QGraphicsRectItem(parent){

    pos = position;
    setRect(HORIZONTAL_MARGIN + (pos.rank - 1) * SQUARE_SIZE + 10, VERTICAL_MARGIN + (pos.file - 1) * SQUARE_SIZE + 10, 80, 80);
    QBrush brush;
    brush.setStyle(Qt::Dense3Pattern);
    brush.setColor(Qt::blue);
    setBrush(brush);

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit Pressed();
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color to cyan
    QBrush brush;
    brush.setStyle(Qt::Dense4Pattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color to dark cyan
    QBrush brush;
    brush.setStyle(Qt::Dense3Pattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}