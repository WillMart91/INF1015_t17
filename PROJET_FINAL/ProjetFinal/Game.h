//#include "Calc.hpp"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>

#include <QString>
#include <QLabel>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> //list << element
#include <QPointF> //F for float + more fctions 
#include <QPixmap>
//#include <QtGui>

#include <cppitertools/range.hpp>

//#include "Box.h"
#include <QMouseEvent>


class Game : public QMainWindow {
	Q_OBJECT

public:
	Game(QWidget* parent = nullptr);
	~Game() override = default;
	void initializeGame();
	void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
	void drawSides();
	void updateScene();//send board

	
	QGraphicsView* view;
	QGraphicsScene* scene;

	const int HORIZONTAL_MARGIN = 400;
	const int VERTICAL_MARGIN = 100;
	const int SQUARE_SIZE = 100;
	const int NB_BOX = 8;
};
