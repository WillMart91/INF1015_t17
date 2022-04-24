#include "knight.h"


knight::knight(bool blackTeam, Square beginPos) :AbsPiece(blackTeam, beginPos)
{
}

std::vector<Square> knight::getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard)
{
    Square pos = getPosition();
    std::vector<Square> moves;

    for (int i = 0; i < direction.size(); i++)
    {
        if (chessBoard[pos.file + direction[i][0]][pos.rank + direction[i][1]]->isBlackTeam() != this->isBlackTeam()) //chek si pas allier    
            moves.push_back(pos + direction[i]);        
    }

    return moves;
}
