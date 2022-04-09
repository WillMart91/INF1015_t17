
#include "Game.h"
#include "CalcWindow.hpp"


using namespace Qt;

Game::Game(QWidget* parent) :
	QGraphicsView(parent)
{
	scene = new QGraphicsScene();
	view = new QGraphicsView();
	
	setFixedSize(1600, 1400);

	initializeGame();

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
				//Box box(HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE, red, 0.7);
				drawRectangle(HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE, red, 0.7);
			}	
			else
			{
				//Box box(HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE, white, 1.0);
				drawRectangle(HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE, white, 1.0);
			}
				
		}
	}
}

void Game::drawSides()
{
	//drawing the sides
	drawRectangle(0, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX * SQUARE_SIZE, darkBlue, 0.5); //left
	drawRectangle(HORIZONTAL_MARGIN + NB_BOX* SQUARE_SIZE, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX*SQUARE_SIZE, darkBlue, 0.5); //right
	drawRectangle(0, 0, HORIZONTAL_MARGIN*2 + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, darkBlue, 0.5); //top
	drawRectangle(0, NB_BOX * SQUARE_SIZE + VERTICAL_MARGIN, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, SQUARE_SIZE, darkBlue, 0.5); //bottom
	
	//drawing players elim text
	QGraphicsTextItem* player1 = new QGraphicsTextItem("Player 1's elimination :");
	player1->setPos(10, VERTICAL_MARGIN-50);
	player1->setScale(3);
	scene->addItem(player1);

	QGraphicsTextItem* player2 = new QGraphicsTextItem("Player 2's elimination :");
	player2->setPos(HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE + 10, VERTICAL_MARGIN - 50);
	player2->setScale(3);
	scene->addItem(player2);

	//drawing turns 
	QGraphicsTextItem* turn = new QGraphicsTextItem("'s turn to play");
	turn->setPos((HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE)/2 + 150, VERTICAL_MARGIN /4);
	turn->setScale(5);
	scene->addItem(turn);
}

void Game::drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity)
{
	QGraphicsRectItem* rect = new QGraphicsRectItem();
	rect->setRect(posX, posY, sizeX, sizeY);
	rect->setBrush(color);
	rect->setOpacity(opacity);
	scene->addItem(rect);
}









//void Game::drawText(int posX, int posY, float scale, string str)
//{
//	QGraphicsTextItem* text = new QGraphicsTextItem(str); //qgraphicsitem_cast<QGraphicsTextItem*>(str)
//	text->setPos(posX, posY);
//	text->setScale(scale);
//	scene->addItem(text);
//}




