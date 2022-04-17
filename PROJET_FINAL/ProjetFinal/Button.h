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
    void clickEvent(QGraphicsSceneMouseEvent* event);
    void hoverEvent(QGraphicsSceneHoverEvent* event);
    void offHoverEvent(QGraphicsSceneHoverEvent* event);
    Position getPos();
signals:
    void Pressed();
private:
    QGraphicsTextItem* text;
    Position pos;
    QColor color1;
    QColor color2;

};
