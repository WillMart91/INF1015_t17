#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.

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
		void showInitialPieces();
		void initializeGame();
		void setupTeam(QColor color);
		//GAMEPLAY RELATED
		void displayPossibleLocations(Square allo);
		void removePossibleLocations(Square allo);
		void mouvementPiece(Square pos1, Square pos2);
		void switchPieces(Square pos1, Square pos2); 
		//CREATORS RELATED
		QGraphicsTextItem* createPiece(QString str, int i, int j, QColor color);
		void drawText(QString str, int posX, int posY, int scale, QColor color);
		void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);

	private:
		//necessary attributes for the display
		QGraphicsView* view;
		QGraphicsScene* scene;

		//containers
		QGraphicsTextItem* mat[8][8]; ////contains all of the pieces
		Tile* Tiles[8][8]; //contains all of the tiles
		QList<Tile*> tileList; // testing
		Tile* Tile1D[64];

		//attributes necessary for the gameplay
		Square clicked;
		Square selected;
		int validClicks;
	};
}
