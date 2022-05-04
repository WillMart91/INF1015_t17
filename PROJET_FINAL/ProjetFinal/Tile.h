<<<<<<< HEAD
//QT INCLUDES
=======
<<<<<<< HEAD:PROJET_FINAL/tp6cleaning(2)/Button.h
/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: class that represents a single square on the visual 8 by 8 board. 
It affects the color of the square and handles everything to do with the click and hover of buttons.
*/


=======
//QT INCLIDES
>>>>>>> 80ed777dbea3a6feb634004eac5e005ece5d7509:PROJET_FINAL/ProjetFinal/Tile.h
>>>>>>> 0857624456b0f17f1008a8f5f533726e17e58459
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
    void mousePressEvent(QGraphicsSceneMouseEvent* event) { emit Clicked(); };
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) { setBrush(*darkerBrush); };
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) { setBrush(*lighterBrush); };

    // OTHER METHODS
    Square getPos() const { return pos; };
    QString getPieceType() const { return pieceType; };
    void setPieceType(char newType) { pieceType = newType; };
    void glow() { setBrush(*validBrush); };
    void stopGlowing() { setBrush(*lighterBrush); };


signals:
    void Clicked();

private:
    Square pos;
    QString pieceType;
    QGraphicsTextItem* text;

    QBrush* lighterBrush;
    QBrush* darkerBrush;
    QBrush* validBrush;

};

bool operator==(const Tile* p1, const Square s);



