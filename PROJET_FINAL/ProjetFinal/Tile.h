#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsTextItem>
//OTHER
#pragma once
#include "GlobalConst.h"
#include "Square.h"

using namespace Qt;

class Tile :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // CTOR + DTOR
    Tile(Square position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent = NULL);
    ~Tile() = default;

    // EVENTS RELATED METHODS
    void mousePressEvent(QGraphicsSceneMouseEvent* event) { emit Clicked(); }
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) { setBrush(*darkerBrush); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) { setBrush(*lighterBrush); }

    // OTHER METHODS
    bool getMoveValidity() const { return isValid; }
    Square getPos() const { return pos; }
    QString getPieceType() const { return pieceType; }
    bool getPieceTeam() const { return blackTeam; }
    void setPieceType(QString newType, bool isBlack);
    void glow();
    void stopGlowing();

signals:
    void Clicked();

private:
    Square pos;
    QString pieceType;
    bool blackTeam;
    QGraphicsTextItem* text;

    QBrush* lighterBrush;
    QBrush* darkerBrush;
    QBrush* validBrush;

    bool isValid;

};

bool operator==(const Tile* p1, const Square s);
bool operator==(const Square s, const Tile* p1);



