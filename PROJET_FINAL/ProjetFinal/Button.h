#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "Position.h"
#include "GlobalConst.h"

class Button :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // constructors
    Button(Position position, QGraphicsItem* parent = NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
signals:
    void Pressed();
private:
    QGraphicsTextItem* text;
    Position pos;
};
