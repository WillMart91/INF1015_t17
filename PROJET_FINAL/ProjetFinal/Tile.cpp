#include "Tile.h"

Tile::Tile(Square position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent) : QGraphicsRectItem(parent) 
{
    pieceType = " ";
    pos = position;
    setRect(HORIZONTAL_MARGIN + (position.file * SQUARE_SIZE), VERTICAL_MARGIN + (position.rank * SQUARE_SIZE), sizeX, sizeY); 
    
    //ADDING THE PIECE TEXT TO THE TILE (empty for now)
    text = new QGraphicsTextItem(pieceType, this);
    int x = HORIZONTAL_MARGIN + (position.file * SQUARE_SIZE);
    int y = VERTICAL_MARGIN + (position.rank * SQUARE_SIZE)-40; 
    text->setScale(8);
    text->setPos(x,y);
    
    //DEFINING THE TILE COLORS
    QBrush brush;
    brush.setStyle(SolidPattern);
    brush.setColor(baseColor);
    lighterBrush = new QBrush(brush);
  
    QBrush brush2;
    brush2.setStyle(SolidPattern);
    brush2.setColor(hoverColor);
    darkerBrush = new QBrush(brush2);

    QBrush brush3;
    brush3.setStyle(SolidPattern);
    brush3.setColor(darkCyan);
    validBrush = new QBrush(brush3);

    //SET BASE COLOR AND ENABLE MOUSE ACTION
    setBrush(*lighterBrush);
    setAcceptHoverEvents(true);
}



bool operator==(const Tile* p1, const Square s)
{
    return (p1->getPos() == s);
}