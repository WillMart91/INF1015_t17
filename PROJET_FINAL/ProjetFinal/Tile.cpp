#include "Tile.h"

Tile::Tile(Square position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent) : QGraphicsRectItem(parent) 
{
    isValid = false;
    pieceType = " ";
    teamColor = nullptr;
    pos = position;
    setRect(HORIZONTAL_MARGIN + ((position.file-1) * SQUARE_SIZE), VERTICAL_MARGIN + ((8-position.rank) * SQUARE_SIZE), sizeX, sizeY); 
    
    //ADDING THE PIECE TEXT TO THE TILE (empty for now)
    text = new QGraphicsTextItem(pieceType, this);
    int x = HORIZONTAL_MARGIN + ((position.file - 1) * SQUARE_SIZE);
    int y = VERTICAL_MARGIN + ((8 - position.rank) * SQUARE_SIZE);
    text->setScale(4);
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



void Tile::setPieceType(QString newType, QColor newColor) {
    pieceType = newType;
    teamColor = new QColor(newColor);
    text->setPlainText(newType);
    text->setDefaultTextColor(newColor);
   
}

void Tile::glow() {
    setBrush(*validBrush);
    setAcceptHoverEvents(false);
    isValid = true;
}

void Tile::stopGlowing() {
    setBrush(*lighterBrush);
    isValid = false;
    setAcceptHoverEvents(true);
}

void Tile::removePiece() {
    pieceType = " ";
    teamColor = nullptr;
    text->setPlainText(pieceType);
}

bool operator==(const Tile* p1, const Square s)
{
    return (p1->getPos() == s);
}
