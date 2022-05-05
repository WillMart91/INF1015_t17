#include "Board.h"
#include "Game.h"



namespace FrontEnd {
	Game::Game(QWidget* parent) : QGraphicsView(parent)
	{
		scene = new QGraphicsScene();
		view = new QGraphicsView();
		view->setScene(scene);
		view->show();
		//set default window size

		//dislayMainMenu();
		startGame();

	}

	void Game::dislayMainMenu()
	{
		//GameButton gb = new GameButton();
	}

	//ADD START BUTTON
	void Game::startGame() 
	{
		initializeGame();
	}

	void Game::initializeGame()
	{
		validClicks = 0;

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
				Square pos = {i,j};
				if ((i + j) % 2)
				{
					Tile* playButton = new Tile(pos, SQUARE_SIZE, SQUARE_SIZE, color1, color2);
					connect(playButton, SIGNAL(Clicked()), this, SLOT(tilePressed()));
					scene->addItem(playButton); 
					tileList.push_back(playButton); 
				}
				else
				{
					Tile* playButton = new Tile(pos, SQUARE_SIZE, SQUARE_SIZE, color3, color4);
					connect(playButton, SIGNAL(Clicked()), this, SLOT(tilePressed()));
					scene->addItem(playButton);		
					tileList.push_back(playButton); 		
				}
			}
		}

		setupTeam(white);
		setupTeam(black);
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

	void Game::setupTeam(QColor color)
	{
		Square position;
		int v = 0;
		int w = 1;
		bool isBlack = true;
		if (color == white)
		{
			isBlack = false;
			v = 7;
			w = 6;
		}

		position = { 3,v };
		auto matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♛", isBlack);

		position = { 4,v };
		matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♚", isBlack);

		position = { 2,v };
		matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♝", isBlack);

		position = { 5,v };
		matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♝", isBlack);

		position = { 1,v };
		matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♞", isBlack);

		position = { 6,v };
		matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♞", isBlack);


		position = { 0,v };
		matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♜", isBlack);

		position = { 7,v };
		matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		(*matching_iter)->setPieceType("♜", isBlack);

	
		for (int i = 0; i < 8; i++)
		{
			position = { i,w };
			matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
			(*matching_iter)->setPieceType("♟", isBlack);
		}
	}

	void Game::tilePressed() //fction call when a button is pressed
	{
		removePossibleLocations(validMoves);

		Tile* obj = dynamic_cast<Tile*>(sender());
		Square position = obj->getPos();
		auto iterTilePiece = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		if ((*iterTilePiece)->getMoveValidity())
		{
			list<pair<Square, Square>> a = Board::getInstance()->moveOnBoard(position);
			
			for(auto it = a.begin(); it != a.end(), it++)
			{
				if (it->first != it->second) {
					mouvementPiece(it->first, it->second);
					//turn est changer // je peu te faire un getter de turn
				}
	
			}
		}
		else 
		{
			validMoves = Board::getInstance()->getMovesOfPiece(position);
			displayPossibleLocations(validMoves); //envoit validMoves
		}

	}

	void Game::displayPossibleLocations(list<Square> positions) 
	{

		Square position;
		for (int i : range(positions.size()))
		{
			position = positions.front();
			auto matching_iter = find_if(tileList.begin(), tileList.end(),[&position](Tile* obj) {return position == obj;});
			(*matching_iter)->glow();
			positions.pop_front();
		}
			
		
	}

	void Game::removePossibleLocations(list<Square> positions)
	{
		Square position;
		for (int i : range(positions.size()))
		{
			position = positions.front();
			auto matching_iter = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
			(*matching_iter)->stopGlowing();
			positions.pop_front();
		}

	}

	void Game::mouvementPiece(Square pos1, Square pos2) 
	{
		//iter pos1 :
		Square position1 = { pos1.file,pos1.rank };
		auto iterTilePiece1 = find_if(tileList.begin(), tileList.end(), [&position1](Tile* obj) {return position1 == obj; });
		//iter pos2 :
		Square position2 = { pos2.file,pos2.rank };
		auto iterTilePiece2 = find_if(tileList.begin(), tileList.end(), [&position2](Tile* obj) {return position2 == obj; });

		if (position1 == position2)
			return;

		(*iterTilePiece2)->setPieceType((*iterTilePiece1)->getPieceType(), (*iterTilePiece1)->getPieceTeam());
		(*iterTilePiece1)->setPieceType(" ", false);
	

	}

	//REDO OR DELETE
	void Game::switchPieces(Square pos1, Square pos2) //piece à pos1 chage de place avec pos2 (AKA castle)
	{
		//iter pos1 :
		Square position1 = { pos1.file,pos1.rank };
		auto iterTilePiece1 = find_if(tileList.begin(), tileList.end(), [&position1](Tile* obj) {return position1 == obj; });

		//iter pos2 :
		Square position2 = { pos2.file,pos2.rank };
		auto iterTilePiece2 = find_if(tileList.begin(), tileList.end(), [&position2](Tile* obj) {return position2 == obj; });

		//iter temp
		auto temp = iterTilePiece2;
		(*iterTilePiece2)->setPieceType((*iterTilePiece1)->getPieceType(), (*iterTilePiece1)->getPieceTeam());
		(*iterTilePiece1)->setPieceType((*temp)->getPieceType(), (*temp)->getPieceTeam());
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

}

/*		//exemple of positions (to test)
		list<Square> pos ;
		Square pos1 = { allo.file + 1,allo.rank };
		Square pos2 = { allo.file,allo.rank + 1 };
		Square pos3 = { allo.file - 1,allo.rank };
		Square pos4 = { allo.file,allo.rank - 1 };
		pos.push_back(pos1);
		pos.push_back(pos2);
		pos.push_back(pos3);
		pos.push_back(pos4);
		//^^ will be gone*/


/*		//auto obj = dynamic_cast<Tile*>(sender());
		//auto position = obj->getPos();

		//auto iterTilePiece = find_if(tileList.begin(), tileList.end(), [&position](Tile* obj) {return position == obj; });
		//if (validClicks == 0 && (*iterTilePiece)->getPieceType() == " ") //WE IGNORE A FRIST CLICK ON A FREE TILE
		//	return;

		//validClicks++;
		//clicked = { position.file,position.rank };

		//if (validClicks == 1)  // + VERIFY WHO'S TURN (BLACK VS WHITE PIECES)
		//{
		//	displayPossibleLocations(clicked);
		//	selected = clicked;
		//}

		//if (validClicks == 2 && (*iterTilePiece)->getMoveValidity())  // + VERIFY IF LEGIT
		//{
		//	mouvementPiece(selected, clicked);
		//	removePossibleLocations(selected);
		//	validClicks = 0;
		//}
		//else if ((*iterTilePiece)->getMoveValidity())
		//{
		//	removePossibleLocations(selected);
		//	validClicks = 0;
		//}*/