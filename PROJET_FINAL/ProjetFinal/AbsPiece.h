#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "Position.h"
#include "GlobalConst.h"
#include <string>

using namespace Qt;

class AbsPiece :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // constructors
    AbsPiece(bool blackteam, QString pieceImage, Position position, QGraphicsItem* parent = NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    Position getPos();
    void setPos(Position newPos);
signals:
    void Pressed();
private:
    QGraphicsTextItem* text;
    Position pos;
    bool blackTeam;
    QColor color;

};


