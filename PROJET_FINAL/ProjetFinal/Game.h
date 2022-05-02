
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
#include "Square.h"
#include <QMouseEvent>
#include "Tile.h"
//#include "AbsPiece.h"
#include <QMessageBox>

//#include "Pawn.h"

namespace FrontEnd {
	class Game : public QGraphicsView {
		Q_OBJECT

	public slots:
		void tilePressed();
		
	public:
		Game(QWidget* parent = nullptr);
		~Game() override = default;
		void initializeGame();
		void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
		QGraphicsRectItem* CreateRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
		void drawSides();
		//void updateScene();//send board
		void drawPositions();
		void drawText(QString str, int posX, int posY, int scale, QColor color);
		void settupPossibleLocation();
		//void createButton(Position pos);
		void startGame();
		void showPieces();
		QGraphicsTextItem* createPiece(QString str, int i, int j, QColor color);
		void setupTeam(QColor color);
		void mouvementPiece(Square pos1, Square pos2);
		void switchPieces(Square pos1, Square pos2); //castle
		void tileHover(Square allo);
		void tileOffHover(Square allo);

		QGraphicsView* view;
		//unique_ptr<QGraphicsView> view;
		QGraphicsScene* scene;
		//map<pair<int, int>, QGraphicsTextItem*> piecesContainer;
		QGraphicsTextItem* mat[8][8];
		//AbsPiece* matPiece[8][8];
		Tile* Tiles[8][8];
		//chessPiece* pieces[8][8];
		//vector<QGraphicsRectItem*> locations;
		Square temp;
		Square lastClicked;
		int validClicks;

	};
}//
