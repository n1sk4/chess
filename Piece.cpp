#include "Piece.h"

void Pieces::CreatePieces(vector<Piece>* allPieces)
{
  for (Color c : colors)
  {
    King king(c);
    allPieces->push_back(king);
    Kings.push_back(king);

    Queen queen(c);
    allPieces->push_back(queen);
    Queens.push_back(queen);

    for (int i = 0; i < COLUMNS; i++)
    {
      Pawn pawn(c);
      allPieces->push_back(pawn);
      
      int rowPostion = 2;
      if (c == eBlack)
        rowPostion = 7;
      pawn.Position[eRow] = rowPostion;
      pawn.Position[eCol] = i;

      Pawns.push_back(pawn);
    }

    for (int i = 0; i < 2; i++)
    {
      Rook rook(c);
      allPieces->push_back(rook);
      Rooks.push_back(rook);
    }

    for (int i = 0; i < 2; i++)
    {
      Knight knight(c);
      allPieces->push_back(knight);
      Knights.push_back(knight);
    }

    for (int i = 0; i < 2; i++)
    {
      Bishop bishop(c);
      allPieces->push_back(bishop);
      Bishops.push_back(bishop);
    }
  }
}