#pragma once
#include "Common.h"

class Piece
{
public:
  Piece(Color color){};
  char PieceCharacter = ' ';
  int Position[2] = { 0, int(Letter::eEmpty) };
};

class Pawn : public Piece
{
public:
  Pawn(Color color) : Piece(color)
  {
    PieceCharacter = ePawn;
  }
};

class King : public Piece
{
public:
  King(Color color) : Piece(color)
  {
    PieceCharacter = eKing;
  }
};

class Queen : public Piece
{
public:
  Queen(Color color) : Piece(color)
  {
    PieceCharacter = eQueen;
  }
};

class Rook : public Piece
{
public:
  Rook(Color color) : Piece(color)
  {
    PieceCharacter = eRook;
  }
};

class Knight : public Piece
{
public:
  Knight(Color color) : Piece(color)
  {
    PieceCharacter = eKnight;
  }
};

class Bishop : public Piece
{
public:
  Bishop(Color color) : Piece(color)
  {
    PieceCharacter = eBishop;
  }
};

class Pieces
{
public:
  void CreatePieces(vector<Piece>* allPieces);

private:

  Color colors[2] = { eWhite, eBlack };
  vector<Pawn> Pawns;
  vector<King> Kings;
  vector<Queen> Queens;
  vector<Rook> Rooks;
  vector<Knight> Knights;
  vector<Bishop> Bishops;
};