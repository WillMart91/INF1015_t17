#include "Pawn.h"

Pawn::Pawn(bool blackTeam, Square beginPos) :AbsPiece(blackTeam,beginPos)
{
}

std::vector<Square> Pawn::getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard)
{
    Square pos = getPosition();
    std::vector<Square> moves = { pos + direction[0]*range * (-1 ^ isBlackTeam()) };
    if (inStartPos()) {
        moves.push_back(pos + direction[0] * (range + 1)*(-1^ isBlackTeam()));
    }
    for (int i = 0; i < attackDirection.size(); i++)
    {
        if (chessBoard[pos.file + attackDirection[i][0] * range*(-1 ^ isBlackTeam())][pos.rank + attackDirection[i][1] * range*(-1 ^ isBlackTeam())]->isBlackTeam() != this->isBlackTeam()) {
            moves.push_back(pos + attackDirection[i] * range*(-1 ^ isBlackTeam()));
        }
    }
    return moves;

}

