#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "Position.h"
#include "GlobalConst.h"

using namespace Qt;

class Button :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // constructors
    Button(Position position, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent = NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    Position getPos();
signals:
    void Clicked();
    void Hovered();
    void OffHovered();
private:
    QGraphicsTextItem* text;
    Position pos;
    QColor color1;
    QColor color2;

};