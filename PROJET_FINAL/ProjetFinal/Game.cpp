#include "Game.h"
#include "qchar.h"

using namespace std;
using namespace Qt;

Game::Game(QWidget* parent) :
	QMainWindow(parent)
{
	scene = new QGraphicsScene();
	view = new QGraphicsView();
	//setFixedSize(1600, 1000);
	//setScene(scene);

	initializeGame();
	
	//for loop for game progress (eventually)
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
				drawRectangle(HORIZONTAL_MARGIN + (i * SQUARE_SIZE), VERTICAL_MARGIN + (j * SQUARE_SIZE), SQUARE_SIZE, SQUARE_SIZE, white, 1.0);
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
		drawText(QString::number(i), HORIZONTAL_MARGIN - 15, VERTICAL_MARGIN + SQUARE_SIZE * i - 50, 1);
	}

	//horizontal
	vector<QString> tab = { "a","b","c","d","e","f","g","h"};
	for (int i = 0; i < 8; i++)
	{
		drawText(tab[i], HORIZONTAL_MARGIN + SQUARE_SIZE * (i+1) - 50, VERTICAL_MARGIN + NB_BOX*SQUARE_SIZE, 1);
	}
}

void Game::drawText(QString str, int posX, int posY, int scale )
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
	drawRectangle(HORIZONTAL_MARGIN + NB_BOX* SQUARE_SIZE, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX*SQUARE_SIZE, darkBlue, 0.5); //right
	drawRectangle(0, 0, HORIZONTAL_MARGIN*2 + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, darkBlue, 0.5); //top
	drawRectangle(0, NB_BOX * SQUARE_SIZE + VERTICAL_MARGIN, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, SQUARE_SIZE/2, darkBlue, 0.5); //bottom
	
	//drawing players elim text
	drawText("Player 1's elimination", 0, VERTICAL_MARGIN - 40, 2);

	//QGraphicsTextItem* player2 = new QGraphicsTextItem("Player 2's elimination");
	drawText("Player 2's elimination", HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE - 5, VERTICAL_MARGIN - 40, 2);

	//drawing turns 
	drawText("'s turn to play", (HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 6, 3);
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
	//delete previous items : scene->scene->removeItem
	//place new item 
	// maybe on side if elimination

	//QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
	//QPixmap pix("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015\INF1015_t17/PROJET_FINAL/ProjetFinal/ressources/knight.png");
	//QLabel* label = new QLabel();
	//label->setPixmap(pix);
	//item->setPixmap(pix);
	//item->setPos(100, 100);
	//item->setScale(15);
	//scene->addItem(item);
	//scene->addWidget(label);

	//QPixmap pixmap = QPixmap("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015\INF1015_t17/PROJET_FINAL/ProjetFinal/ressources/knight.png");
	//QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pixmap);
	//scene->addItem(pixItem);
	//view->fitInView(pixItem);
}

//TEST : FAIRE APPARAITRE PIÈCE




//QPixmap pix("C:/Users/Willm/Documents/Documents/POLY/Poly_session2/INF1015\INF1015_t17/PROJET_FINAL/ProjetFinal/ressources/knight.png");
//QGraphicsPixmapItem* item = scene->addPixmap(pix);

////QLabel* label = new QLabel();
////label->setPixmap(pix);
//item->setPixmap(pix);
//item->setPos(100,100);
//item->setScale(15);
//scene->addItem(item);



