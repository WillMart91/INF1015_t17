#include "Calc.hpp"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>

#include <QString>
#include <QLabel>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <cppitertools/range.hpp>

//#include "Box.h"
#include <QMouseEvent>


class Game : public QGraphicsView {
	Q_OBJECT

public:
	Game(QWidget* parent = nullptr);
	~Game() override = default;
	void initializeGame();
	void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
	void drawSides();

	QGraphicsScene* scene;
	QGraphicsView* view;
	const int HORIZONTAL_MARGIN = 400;
	const int VERTICAL_MARGIN = 200;
	const int SQUARE_SIZE = 100;
	const int NB_BOX = 8;
};
