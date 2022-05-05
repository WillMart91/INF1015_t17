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
#pragma once
//#include "GlobalConst.h"
#include "Tile.h"
#include "Board.h"

#include "Square.h"
#include "GameButton.h"


using namespace std;
using namespace iter;

namespace FrontEnd {
	class Game : public QGraphicsView {
		Q_OBJECT

	public slots:
		void tilePressed();
		void startGame();
		void endGame();
		void restartGame();
		void startCustomGame();
		
	public:
		Game(QWidget* parent = nullptr);
		~Game();

		//PRE-GAME 
		void dislayMainMenu();
		//INITIAL BOARD RELATED
		void drawSides();
		void drawPositions();
		void initializeGame();
		void setupTeam(QColor color);
		void customWhiteTeam();
		void customBlackTeam();
		//GAMEPLAY RELATED
		void displayPossibleLocations(list<Square> positions);
		void removePossibleLocations(list<Square> positions);
		void mouvementPiece(Square pos1, Square pos2);
		//CREATORS RELATED
		void drawText(QString str, int posX, int posY, int scale, QColor color);
		void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);

	private:
		//necessary attributes for the display
		QGraphicsView* view_;
		QGraphicsScene* scene_;
		GameButton* startGameButton_;
		GameButton* restartGameButton_;
		GameButton* endGameButton_;
		GameButton* customGameButton_;
		QGraphicsTextItem* playerTurn_;

		//container
		QList<Tile*> tileList_; // contains all tiles (each tile contains chessPiece images)
		list<Square> validMoves_;

		//attributes necessary for the gameplay
		Square clicked_;
		Square selected_;
		int mouvementMade_;
	};
}
