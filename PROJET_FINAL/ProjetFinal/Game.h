
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
#include <QString>
#include <QPushButton>
#include <cppitertools/range.hpp>
#include "Position.h"
#include <QMouseEvent>
#include "button.h"

//namespace FrontEnd {
	class Game : public QGraphicsView {
		Q_OBJECT

	public:
		Game(QWidget* parent = nullptr);
		~Game() override = default;
		void initializeGame();
		void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
		void drawSides();
		void updateScene();//send board
		void drawPositions();
		void drawText(QString str, int posX, int posY, int scale);
		void settupPossibleLocation(); 
		void createButton(Position pos);
		void startGame();
		void Action();

		QGraphicsView* view;
		QGraphicsScene* scene;
	};
