#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsTextItem>
//OTHER
#include "Square.h"
#include "GlobalConst.h"

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
    QColor getPieceTeam() const { return *teamColor; }
    void setPieceType(QString newType, QColor newColor);
    void glow();
    void stopGlowing();
    void removePiece();
    bool isTileFree() { return pieceType == " "; }

signals:
    void Clicked();

private:
    Square pos;
    QString pieceType;
    QGraphicsTextItem* text;

    QBrush* lighterBrush;
    QBrush* darkerBrush;
    QBrush* validBrush;
    QColor* teamColor;

    bool isValid;

};

bool operator==(const Tile* p1, const Square s);



