
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>

#include <QString>
#include <QLabel>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> 
#include <QPointF> 
#include <QPixmap>
#include <QString>
#include <QPushButton>
#include <cppitertools/range.hpp>
#include "Square.h"
#include <QMouseEvent>
#include "button.h"
#include "Board.h" 
#include <QMessageBox>

//#include "Pawn.h"

namespace FrontEnd {
	class Game : public QGraphicsView {
		Q_OBJECT

	public slots:
		void tilePressed();
		void tileHover();
		void tileOffHover();
		void chessAction();
	public:
		Game(QWidget* parent = nullptr);
		~Game() override = default;
		void initializeGame();
		void drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
		QGraphicsRectItem* CreateRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
		void drawSides();
		void drawPositions();
		void drawText(QString str, int posX, int posY, int scale, QColor color);
		void settupPossibleLocation();
		void startGame();
		void showPieces();
		QGraphicsTextItem* createPiece(QString str, int i, int j, QColor color);
		void setupTeam(QColor color);
		void mouvementPiece(Square pos1, Square pos2);
		void switchPieces(Square pos1, Square pos2); //castle

		QGraphicsView* view;
		QGraphicsScene* scene;
		QGraphicsTextItem* mat[8][8];
		Button* buttons[8][8];
		//vector<QGraphicsRectItem*> locations;
		Square temp;
		Square lastClicked;
		int validClicks;
		BackEnd::Board b;
	};
}//
