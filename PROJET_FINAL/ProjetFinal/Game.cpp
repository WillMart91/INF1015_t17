#include "Game.h"
#include "qchar.h"

using namespace std;
using namespace Qt;


//namespace FrontEnd {
	Game::Game(QWidget* parent) :
		QGraphicsView(parent)
	{
		scene = new QGraphicsScene();
		view = new QGraphicsView();

		startGame();

		updateScene();
		view->setScene(scene);
		view->show();
	}


	void Game::initializeGame()
	{
		drawSides();

		for (int i = 0; i < NB_BOX; i++)
		{
			for (int j = 0; j < NB_BOX; j++)
			{
				if ((i + j) % 2)
				{
					drawRectangle(HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE, red, 0.7);
				}
				else
				{
					drawRectangle(HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE, yellow, 0.1);
				}
			}
		}

		drawPositions();
	}
	void Game::drawPositions()
	{
		//vertical
		for (int i = 1; i <= 8; i++)
		{
			drawText(QString::number(i), HORIZONTAL_MARGIN - 25, VERTICAL_MARGIN + SQUARE_SIZE * i - 60, 1);
		}

		//horizontal
		vector<QString> tab = { "a","b","c","d","e","f","g","h" };
		for (int i = 0; i < 8; i++)
		{
			drawText(tab[i], HORIZONTAL_MARGIN + SQUARE_SIZE * (i + 1) - 60, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE, 1);
		}
	}

	void Game::drawText(QString str, int posX, int posY, int scale)
	{
		QGraphicsTextItem* player1 = new QGraphicsTextItem(str);
		player1->setPos(posX, posY);
		player1->setScale(scale);
		scene->addItem(player1);
	}

	void Game::drawSides()
	{
		//drawing the sides
		drawRectangle(0, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX * SQUARE_SIZE, darkBlue, 0.5); //left
		drawRectangle(HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX * SQUARE_SIZE, darkBlue, 0.5); //right
		drawRectangle(0, 0, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, darkBlue, 0.5); //top
		drawRectangle(0, NB_BOX * SQUARE_SIZE + VERTICAL_MARGIN, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, SQUARE_SIZE / 2, darkBlue, 0.5); //bottom

		//drawing players elim text
		drawText("Player 1's elimination", 0, VERTICAL_MARGIN - 40, 1);

		//QGraphicsTextItem* player2 = new QGraphicsTextItem("Player 2's elimination");
		drawText("Player 2's elimination", HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE - 60, VERTICAL_MARGIN - 40, 1);

		//drawing turns 
		drawText("'s turn to play", (HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 7, 2);
		//drawText("<3", (HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 6, 5);
	}

	void Game::drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity)
	{
		QGraphicsRectItem* rect = new QGraphicsRectItem();
		rect->setRect(posX, posY, sizeX, sizeY);
		rect->setBrush(color);
		rect->setOpacity(opacity);
		//view->fitInView(rect, Qt::KeepAspectRatio);
		//rect->setScale(2);
		scene->addItem(rect);
	}

	void Game::updateScene() //receves a chess piece ; deletes it ; copies it to the right place
	{

	}

	void Game::startGame() //receves Player1, Player2, Board
	{
		initializeGame();

		//int i;
		//for (i = 0; i < 5; i++)
		//{
		// //if (i%2)
		//		Player1.play()
		//   else
		//		Player2.play()
		// 
		//

		//test 
		
		settupPossibleLocation();
	}
	void Game::Action()
	{
		
	}

	void Game::createButton(Position pos)
	{
		Button* playButton = new Button(pos);
		connect(playButton, SIGNAL(Pressed()), this, SLOT(Action()));
		scene->addItem(playButton);
	}

	void Game::settupPossibleLocation() //will receve vector of position
	{
		//exemple of positions (to test)
		Position pos1 = { 4,3 };
		Position pos2 = { 4,5 };
		Position pos3 = { 4,6 };
		Position pos4 = { 5,4 };
		Position pos5 = { 3,4 };
		vector<Position> pos = { pos1, pos2, pos3, pos4, pos5};

		for (int i = 0; i < pos.size(); i++)
			createButton(pos[i]);
		
	}
