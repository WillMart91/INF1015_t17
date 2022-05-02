#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
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