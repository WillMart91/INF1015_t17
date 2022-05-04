/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: class that represents a single square on the visual 8 by 8 board. 
It affects the color of the square and handles everything to do with the click and hover of buttons.
*/


#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "Square.h"
#include "GlobalConst.h"

using namespace Qt;

class Button :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // constructors
    Button(Square position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent = NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    Square getPos();
signals:
    void Clicked();
    void Hovered();
    void OffHovered();
private:
    QGraphicsTextItem* text;
    Square pos;
    QColor color1;
    QColor color2;

};