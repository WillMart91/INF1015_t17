/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: implementation of the class.
*/

#include "Game.h"

namespace FrontEnd {
	Game::Game(QWidget* parent) : QGraphicsView(parent) {
		scene_ = new QGraphicsScene();
		view_ = new QGraphicsView();
		view_->setFixedHeight(1080);
		view_->setFixedWidth(1920);

		view_->setScene(scene_);
		view_->show();

		initializeGame();
		dislayMainMenu();	
	}

	Game::~Game() {
		delete(view_);
		delete(scene_);
		delete(startGameButton_);
		delete(startNormalGameButton_);
		delete(customGameButton1_);
		delete(customGameButton2_);
		delete(endGameButton_);
	}

	void Game::dislayMainMenu() {
		startGameButton_ = new GameButton("Start game", 520, 425,150,50, darkCyan, cyan);
		connect(startGameButton_, SIGNAL(Clicked()), this, SLOT(startGame()));
		scene_->addItem(startGameButton_);
	}

	void Game::startGame() 
	{
		scene_->removeItem(startGameButton_);

		startNormalGameButton_ = new GameButton("Classic game", 15, 890, 150, 50, darkYellow, darkCyan);
		connect(startNormalGameButton_, SIGNAL(Clicked()), this, SLOT(startNormalGame()));
		scene_->addItem(startNormalGameButton_);

		endGameButton_ = new GameButton("End game", 1025, 890, 150, 50, darkYellow, darkCyan);
		connect(endGameButton_, SIGNAL(Clicked()), this, SLOT(endGame()));
		scene_->addItem(endGameButton_);

		customGameButton1_ = new GameButton("3 vs 3", 15, 830, 150, 50, darkYellow, darkCyan);
		connect(customGameButton1_, SIGNAL(Clicked()), this, SLOT(startCustomGame1()));
		scene_->addItem(customGameButton1_);

		customGameButton2_ = new GameButton("2 Kings 1 Queen", 15, 770, 150, 50, darkYellow, darkCyan);
		connect(customGameButton2_, SIGNAL(Clicked()), this, SLOT(startCustomGame2()));
		scene_->addItem(customGameButton2_);

		setupTeam(0);
	}

	void Game::startCustomGame1() {
		//clearing the tiles from their piece type
		for (auto it = tileList_.begin(); it != tileList_.end(); it++)
			(*it)->removePiece();

		setupTeam(1);
	}

	void Game::startCustomGame2() {
		//clearing the tiles from their piece type
		for (auto it = tileList_.begin(); it != tileList_.end(); it++)
			(*it)->removePiece();

		setupTeam(2);
	}

	void Game::endGame() {
		tileList_.clear();
		scene_->clear();

	}

	void Game::startNormalGame() {
		//clearing the tiles from their piece type
		for (auto it = tileList_.begin(); it != tileList_.end(); it++)
			(*it)->removePiece();

		setupTeam(0);
	}

	void Game::initializeGame()
	{

		//Drawing backround
		drawSides();
		drawPositions();

		//setting up button
		QColor color1 = QColor(214, 199, 148, 255);		// beige
		QColor color2 = QColor(158, 142, 89, 255);		// darker
		QColor color3 = QColor(163, 135, 41, 255);		// brown
		QColor color4 = QColor(97, 77, 12, 255);		// darker

		//filling the 8x8 tilemap
		for (int i = 1; i <= NB_BOX; i++)
		{
			for (int j = 1; j <= NB_BOX; j++)
			{
				Square pos = {i,j};
				if ((i + j) % 2)
				{
					Tile* playButton = new Tile(pos, SQUARE_SIZE, SQUARE_SIZE, color1, color2);
					connect(playButton, SIGNAL(Clicked()), this, SLOT(tilePressed()));
					scene_->addItem(playButton); 
					tileList_.push_back(playButton); 
				}
				else
				{
					Tile* playButton = new Tile(pos, SQUARE_SIZE, SQUARE_SIZE, color3, color4);
					connect(playButton, SIGNAL(Clicked()), this, SLOT(tilePressed()));
					scene_->addItem(playButton);		
					tileList_.push_back(playButton); 		
				}
			}
		}

	}

	void Game::drawSides() {
		//drawing the sides
		drawRectangle(0, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX * SQUARE_SIZE, black, 0.8); //left
		drawRectangle(HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, HORIZONTAL_MARGIN, NB_BOX * SQUARE_SIZE, black, 0.8); //right
		drawRectangle(0, 0, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, black, 0.8); //top
		drawRectangle(0, NB_BOX * SQUARE_SIZE + VERTICAL_MARGIN, HORIZONTAL_MARGIN * 2 + NB_BOX * SQUARE_SIZE, SQUARE_SIZE / 2, black, 0.8); //bottom

		////drawing players elim text
		//drawText("Player 1's elimination", 0, VERTICAL_MARGIN - 40, 1, white);

		////QGraphicsTextItem* player2 = new QGraphicsTextItem("Player 2's elimination");
		//drawText("Player 2's elimination", HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE - 60, VERTICAL_MARGIN - 40, 1, white);

		//drawing turns 
		drawText("'s turn to play", (HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 7, 2, white);
		//drawText("<3", (HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 6, 5);

		playerTurn_ = new QGraphicsTextItem("White");
		playerTurn_->setPos((HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 - 50, VERTICAL_MARGIN / 7);
		playerTurn_->setScale(2);
		playerTurn_->setDefaultTextColor(white);
		playerTurn_->setTextInteractionFlags(TextEditorInteraction);
		
		scene_->addItem(playerTurn_);

	}

	void Game::drawPositions()
	{
		//vertical
		for (int rank : range(1,NB_BOX+1))
		{
			drawText(QString::number(rank), HORIZONTAL_MARGIN - 25, VERTICAL_MARGIN + SQUARE_SIZE * NB_BOX - rank * SQUARE_SIZE +35, 1, white);
		}

		//horizontal
		vector<QString> tab = { "a","b","c","d","e","f","g","h" };
		for (int file :range(NB_BOX))
		{
			drawText(tab[file], HORIZONTAL_MARGIN + SQUARE_SIZE * (file + 1) - 60, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE, 1, white);
		}
	}

	void Game::setupTeam(int selectedLayout)
	{
		playerTurn_->setPlainText("White");
		map<Square, AbsPiece*> layout = Board::getInstance()->getLayout(selectedLayout);
		QColor color;
		for (auto it = layout.begin(); it != layout.end(); it++)
		{
			if (it->second->isBlackTeam())
				color = black;
			else
				color = white;

			if (it->second->isType('p'))
			{
				auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&it](Tile* obj) {return it->first == obj; });
				(*matching_iter)->setPieceType("♟", color);

			}
			else if (it->second->isType('r'))
			{
				auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&it](Tile* obj) {return it->first == obj; });
				(*matching_iter)->setPieceType("♜", color);
			}
			else if (it->second->isType('k'))
			{
				auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&it](Tile* obj) {return it->first == obj; });
				(*matching_iter)->setPieceType("♞", color);
			}
			else if (it->second->isType('b'))
			{
				auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&it](Tile* obj) {return it->first == obj; });
				(*matching_iter)->setPieceType("♝", color);
			}
			else if(it->second->isType('q'))
			{
				auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&it](Tile* obj) {return it->first == obj; });
				(*matching_iter)->setPieceType("♛", color);
			}
			else if (it->second->isType('K'))
			{
				auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&it](Tile* obj) {return it->first == obj; });
				(*matching_iter)->setPieceType("♚", color);
			}
		}
	}

	void Game::customWhiteTeam()
	{

		Square position = { 4,2 };
		auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♚", white);


		position = { 4,7 };
		matching_iter = find_if(tileList_.begin(), tileList_.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♜", white);

	}

	void Game::customBlackTeam()
	{
		Square position = { 3,3 };
		auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♚", black);
	}

	void Game::tilePressed() {
		
		Tile* obj = dynamic_cast<Tile*>(sender());
		Square position = obj->getPos();
		auto iterTilePiece = find_if(tileList_.begin(), tileList_.end(), [&position](Tile* obj) {return position == obj; });					
		if ((*iterTilePiece)->getMoveValidity())
		{
			list<pair<Square, Square>> moving = Board::getInstance()->moveOnBoard(position);
			removePossibleLocations(validMoves_);
			for (auto&& it = moving.begin(); it != moving.end(); it++)
			{
				if (!(it->first == it->second)) {
					mouvementPiece(it->first, it->second);
					if (Board::getInstance()->isBlackTurn())
						playerTurn_->setPlainText("Black");
					else
						playerTurn_->setPlainText("White");
				}

			}
		}
		else
		{
			removePossibleLocations(validMoves_);
			validMoves_ = Board::getInstance()->getMovesOfPiece(position);
			displayPossibleLocations(validMoves_); //envoit validMoves
		}
	}

	void Game::displayPossibleLocations(list<Square> positions) {
		Square position;
		for (int i : range(positions.size()))
		{
			position = positions.front();
			auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&position](Tile* obj) {return position == obj; });
			(*matching_iter)->glow();
			positions.pop_front();
		}
	}

	void Game::removePossibleLocations(list<Square> positions) {
		Square position;
		for (int i : range(positions.size()))
		{
			position = positions.front();
			auto matching_iter = find_if(tileList_.begin(), tileList_.end(), [&position](Tile* obj) {return position == obj; });
			(*matching_iter)->stopGlowing();
			positions.pop_front();
		}

	}

	void Game::mouvementPiece(Square pos1, Square pos2) {
		if(pos1 == pos2)
			return;

		auto iterTilePiece1 = find_if(tileList_.begin(), tileList_.end(), [&pos1](Tile* obj) {return pos1 == obj; });
		auto iterTilePiece2 = find_if(tileList_.begin(), tileList_.end(), [&pos2](Tile* obj) {return pos2 == obj; });

		(*iterTilePiece2)->setPieceType((*iterTilePiece1)->getPieceType(), (*iterTilePiece1)->getPieceTeam());
		(*iterTilePiece1)->removePiece();
	}

	void Game::drawText(QString str, int posX, int posY, int scale, QColor color) {
		QGraphicsTextItem* text = new QGraphicsTextItem(str);
		text->setPos(posX, posY);
		text->setScale(scale);
		text->setDefaultTextColor(color);
		text->setTextInteractionFlags(TextEditorInteraction);
		scene_->addItem(text);
	}

	void Game::drawRectangle(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity) {
		QGraphicsRectItem* rect = new QGraphicsRectItem();
		rect->setRect(posX, posY, sizeX, sizeY);
		rect->setBrush(color);
		rect->setOpacity(opacity);
		scene_->addItem(rect);	
	}
}
