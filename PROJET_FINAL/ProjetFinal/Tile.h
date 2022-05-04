//QT INCLIDES
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
