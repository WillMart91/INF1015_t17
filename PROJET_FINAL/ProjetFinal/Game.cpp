#include "Game.h"
#include "qchar.h"

using namespace std;


//namespace FrontEnd {
	Game::Game(QWidget* parent) : QGraphicsView(parent)
	{
		scene = new QGraphicsScene();
		view = new QGraphicsView();

		startGame();

		updateScene();
		view->setScene(scene);
		view->show();
	}

	void Game::startGame() //receves Player1, Player2, Board
	{
		initializeGame();

		settupPossibleLocation();
		showPieces();
	}

	void Game::initializeGame()
	{
		// clean the array
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mat[i][j] = nullptr;
			}
		}
		// add correct pieces to array
		setupTeam(white);
		setupTeam(black);

		//Drawing backround
		drawSides();
		drawPositions();

		//setting up button
		QColor color1 = QColor(214, 199, 148, 255);		// beige
		QColor color2 = QColor(158, 142, 89, 255);		// darker
		QColor color3 = QColor(163, 135, 41, 255);		// brown
		QColor color4 = QColor(97, 77, 12, 255);		// darker

		for (int i = 0; i < NB_BOX; i++)
		{
			for (int j = 0; j < NB_BOX; j++)
			{
				Position pos = { HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE) };
				if ((i + j) % 2)
				{
					Button* playButton = new Button(pos, SQUARE_SIZE, SQUARE_SIZE, color1, color2);
					connect(playButton, SIGNAL(Pressed()), this, SLOT(Action()));
					scene->addItem(playButton);
				}
				else
				{
					Button* playButton = new Button(pos, SQUARE_SIZE, SQUARE_SIZE, color3, color4);
					connect(playButton, SIGNAL(Pressed()), this, SLOT(Action()));
					scene->addItem(playButton);
				}
			}
		}
	}

	void Game::drawSides()
	{
		//drawing the sides
		drawRectangle(0, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX * SQUARE_SIZE, black, 0.8); //left
		drawRectangle(HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX * SQUARE_SIZE, black, 0.8); //right
		drawRectangle(0, 0, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, black, 0.8); //top
		drawRectangle(0, NB_BOX * SQUARE_SIZE + VERTICAL_MARGIN, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, SQUARE_SIZE / 2, black, 0.8); //bottom

		//drawing players elim text
		drawText("Player 1's elimination", 0, VERTICAL_MARGIN - 40, 1, white);

		//QGraphicsTextItem* player2 = new QGraphicsTextItem("Player 2's elimination");
		drawText("Player 2's elimination", HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE - 60, VERTICAL_MARGIN - 40, 1, white);

		//drawing turns 
		drawText("'s turn to play", (HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 7, 2, white);
		//drawText("<3", (HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 6, 5);
	}

	void Game::drawPositions()
	{
		//vertical
		for (int rank = 1; rank <= 8; rank++)
		{
			drawText(QString::number(rank), HORIZONTAL_MARGIN - 25, VERTICAL_MARGIN + SQUARE_SIZE * rank - 60, 1, white);
		}

		//horizontal
		vector<QString> tab = { "a","b","c","d","e","f","g","h" };
		for (int file = 0; file < 8; file++)
		{
			drawText(tab[file], HORIZONTAL_MARGIN + SQUARE_SIZE * (file + 1) - 60, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE, 1,white);
		}
	}


	void Game::setupTeam(QColor color)
	{
		int v = 0;
		int w = 1;
		if (color == white)
		{
			v = 7;
			w = 6;
		}
		mat[3][v] = createPiece("♛",3,v, color);
		mat[4][v] = createPiece("♚",4,v, color);

		mat[2][v] = createPiece("♝",2,v, color);
		mat[5][v] = createPiece("♝",5,v, color);

		mat[1][v] = createPiece("♞",1,v, color);
		mat[6][v] = createPiece("♞",6,v, color);

		mat[0][v] = createPiece("♜",0,v, color);
		mat[7][v] = createPiece("♜",7,v, color);



		for (int i = 0; i < 8; i++)
		{
			mat[i][w] = createPiece("♟",i,w, color);
			//Pawn* piece = new Pawn(true,pos);
			//matPiece[i][w] = piece;
		}
	}





	void Game::updateScene() //receves a chess piece ; deletes it ; copies it to the right place
	{

	}


	void Game::Action()
	{
		
		QMessageBox::about(this, "Position of the tile : (x)" , "");

		//drawRectangle(pos.rank * 100, pos.file * 100, 300, 300, red, 1);
	}

	void Game::createButton(Position pos) //to be removed
	{
		drawRectangle(HORIZONTAL_MARGIN + (pos.rank - 1) * SQUARE_SIZE+ 10, VERTICAL_MARGIN + (pos.file - 1) * SQUARE_SIZE + 10, SQUARE_SIZE-20, SQUARE_SIZE-20, gray, 0.70);
	}

	void Game::settupPossibleLocation() //will receve vector of position
	{
		//exemple of positions (to test)
		//Position pos1 = { 4,3 };
		//Position pos2 = { 4,5 };
		//Position pos3 = { 4,6 };
		//Position pos4 = { 5,4 };
		//Position pos5 = { 3,4 };
		//vector<Position> pos = { pos1, pos2, pos3, pos4, pos5};

		//for (int i = 0; i < pos.size(); i++)
			//createButton(pos[i]);
		
	}

	void Game::mouvementPiece(Position pos1, Position pos2)
	{
		if (mat[pos2.file][pos2.rank] != nullptr)
		{
			//add to sides
			mat[pos2.file][pos2.rank] = nullptr; //delete from game
		}

		//mat[pos1.file][pos1.rank]->setPosition(pos1.file,pos1.rank);
		mat[pos2.file][pos2.rank] = mat[pos1.file][pos1.rank];
		mat[pos1.file][pos1.rank] = nullptr;
	}


	QGraphicsTextItem* Game::createPiece(QString str,int file, int rank, QColor color)
	{
		QGraphicsTextItem* piece = new QGraphicsTextItem(str);
		piece->setScale(3);
		piece->setDefaultTextColor(color);
		piece->setTextInteractionFlags(TextEditorInteraction);
		piece->setPos(HORIZONTAL_MARGIN + SQUARE_SIZE * file, VERTICAL_MARGIN + SQUARE_SIZE * rank);
		return piece;
	}

	void Game::drawText(QString str, int posX, int posY, int scale, QColor color)
	{
		QGraphicsTextItem* text = new QGraphicsTextItem(str);
		text->setPos(posX, posY);
		text->setScale(scale);
		text->setDefaultTextColor(color);
		text->setTextInteractionFlags(TextEditorInteraction);
		scene->addItem(text);
	}

	void Game::drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity)
	{
		QGraphicsRectItem* rect = new QGraphicsRectItem();
		rect->setRect(posX, posY, sizeX, sizeY);
		rect->setBrush(color);
		rect->setOpacity(opacity);
		scene->addItem(rect);
	}

	void Game::showPieces()
	{
		for (int file = 0; file < 8; file++)
		{
			for (int rank = 0; rank < 8; rank++)  
			{
				if (mat[file][rank] != nullptr)
					scene->addItem(mat[file][rank]);
				
			}
		}
	}

//map<pair<int, int>, QGraphicsTextItem*> piecesContainer;à
//map<pair<int, int>, QGraphicsTextItem*> piecesContainer;
//map<pair<int, int>, int> try2;