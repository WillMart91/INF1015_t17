#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.

//QT INCLUDES
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QString>
#include <cppitertools/range.hpp>
#include <QMessageBox>
#include <QtAlgorithms>
//OTHER
#include "Square.h"
#include "Tile.h"

using namespace std;
using namespace iter;

namespace FrontEnd {
	class Game : public QGraphicsView {
		Q_OBJECT

	public slots:
		void tilePressed();
		
	public:
		Game(QWidget* parent = nullptr);
		~Game() override = default;

		//INITIAL BOARD RELATED
		void drawSides();
		void drawPositions();
		void startGame();
		void initializeGame();
		void setupTeam(QColor color);
		//GAMEPLAY RELATED
		void displayPossibleLocations(Square allo);
		void removePossibleLocations(Square allo);
		void mouvementPiece(Square pos1, Square pos2);
		void switchPieces(Square pos1, Square pos2); 
		//CREATORS RELATED
		void drawText(QString str, int posX, int posY, int scale, QColor color);
		void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);

	private:
		//necessary attributes for the display
		QGraphicsView* view;
		QGraphicsScene* scene;

		//container
		QList<Tile*> tileList; // contains all tiles (each tile contains chessPiece images)

		//attributes necessary for the gameplay
		Square clicked;
		Square selected;
		int validClicks;
	};
}
