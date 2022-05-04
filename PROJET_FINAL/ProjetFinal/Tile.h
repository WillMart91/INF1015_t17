<<<<<<< HEAD:PROJET_FINAL/tp6cleaning(2)/Button.h
/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: class that represents a single square on the visual 8 by 8 board. 
It affects the color of the square and handles everything to do with the click and hover of buttons.
*/


=======
//QT INCLIDES
>>>>>>> 80ed777dbea3a6feb634004eac5e005ece5d7509:PROJET_FINAL/ProjetFinal/Tile.h
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
//OTHER
#include "Square.h"
#include "GlobalConst.h"

using namespace Qt;

class Tile :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // constructors
    Tile(Square position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent = NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);


    Square getPos() const;
    void glow();
    void stopGlowing();
signals:
    void Clicked();

private:
    Square pos;

    QBrush* lighterBrush;
    QBrush* darkerBrush;
    QBrush* validBrush;


};

bool operator==(const Tile* p1, const Square s);
