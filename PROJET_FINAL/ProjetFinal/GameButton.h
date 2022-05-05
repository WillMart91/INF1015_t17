#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QGraphicsTextItem>
//OTHER
#include "GlobalConst.h"

using namespace std;
using namespace Qt;

class GameButton :public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // CTOR + DTOR
    GameButton(QString buttonText, int posX, int posY, int sizeX, int sizeY, QColor baseColor, QColor hoverColor, QGraphicsItem* parent = NULL);
    ~GameButton() = default;

    // EVENTS RELATED METHODS
    void mousePressEvent(QGraphicsSceneMouseEvent* event) { emit Clicked(); }
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) { setBrush(*darkerBrush); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) { setBrush(*lighterBrush); }

signals:
    void Clicked();

private:
    QGraphicsTextItem* text;

    QBrush* lighterBrush;
    QBrush* darkerBrush;

};






