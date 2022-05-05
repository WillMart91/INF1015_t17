
#include "Board.h"
Board* Board::instance_;
Board::~Board()
{
    for (auto&& it = chessBoard_.begin(); it != chessBoard_.end(); it++) {
        delete it->second;
    }
}

std::list<Square> Board::getMovesOfPiece(Square clicked)
{
    std::list<Square> moves;
    lastClicked_ = clicked;
    AbsPiece* piece = chessBoard_[clicked];
    if (piece != nullptr) {
        if (piece->isBlackTeam() == blackTurn_) {
            moves = piece->getValidMoves();
        }
    }
    return moves;
}

std::list<std::pair<Square, Square>> Board::moveOnBoard(Square clicked)
{
    std::map<Square, AbsPiece*> chessBoardBefore = chessBoard_;
    chessBoard_[clicked] = chessBoard_[lastClicked_];
    chessBoard_.erase(lastClicked_);
    bool danger=false;
    for (auto&& it = chessBoard_.begin(); it != chessBoard_.end(); it++) {
        if (it->second != nullptr) {
            if (it->second->isBlackTeam() == blackTurn_ && it->second->isType('K')) {
				danger = validateMove(clicked);
                break;
            }
        }
    }
    std::list<std::pair<Square, Square>> moves;
    if (!danger) {
        moves.push_back({ lastClicked_, clicked });
        blackTurn_ = !blackTurn_;
    }
    else {
        moves.push_back({ lastClicked_, lastClicked_ });
        chessBoard_ = chessBoardBefore;
    }
    return moves;
}

bool Board::validateMove(Square endangeredPos)
{
	int maxDist = std::max(std::max(endangeredPos.file, endangeredPos.rank), std::max(8 - endangeredPos.file, 8 - endangeredPos.rank));
	for (auto&& it = knightCheck.begin(); it != knightCheck.end(); it++)
	{
		Square checkPos = endangeredPos + *it;
		if (Square::isValid(checkPos)) {
			continue;
		}
		AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if (pieceOn->isType('k'))
		{
			if (pieceOn->isBlackTeam() != blackTurn_) {
				return true;
			}
		}
	}
	for (auto&& it = pawnCheck.begin(); it != pawnCheck.end(); it++)
	{
		Square checkPos = endangeredPos + *it * ((-1) ^ (int)blackTurn_);
		if (Square::isValid(checkPos)) {
			continue;
		}
		AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if (pieceOn->isType('p'))
		{
			if (pieceOn->isBlackTeam() != blackTurn_) {
				return true;
			}
		}
	}
	std::list<std::pair<int, int>> bishopCheckCopy = bishopCheck;
	std::list<std::pair<int, int>> rookCheckCopy = rookCheck;
	for (int d = 1; d <= maxDist; d++) {
		for (auto&& it = bishopCheckCopy.begin(); it != bishopCheckCopy.end(); it++)
		{
			Square checkPos = endangeredPos + *it;
			if (Square::isValid(checkPos)) {
				bishopCheckCopy.erase(it);
				continue;
			}
			AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
			if (pieceOn != nullptr) {
				if (pieceOn->isType('b') || pieceOn->isType('q'))
				{
					if (pieceOn->isBlackTeam() != blackTurn_) {
						return true;
					}
					else {
						bishopCheckCopy.erase(it);
					}
				}
				else {
					bishopCheckCopy.erase(it);
				}
			}
		}
		for (auto&& it = rookCheckCopy.begin(); it != rookCheckCopy.end(); it++)
		{
			Square checkPos = endangeredPos + *it;
			if (Square::isValid(checkPos)) {
				rookCheckCopy.erase(it);
				continue;
			}
			AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
			if (pieceOn != nullptr) {
				if (pieceOn->isType('r') || pieceOn->isType('q'))
				{
					if (pieceOn->isBlackTeam() != blackTurn_) {
						return true;
					}
					else {
						rookCheckCopy.erase(it);
					}
				}
				else {
					rookCheckCopy.erase(it);
				}
			}
		}
	}
	return false;
}
