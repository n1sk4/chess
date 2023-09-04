#pragma once
#include "Common.h"

class Piece
{
public:
  Piece() = default;
  Piece(Color color, size_t id) {
    m_Color = color;
    m_Id = id;
  };
  Color m_Color;
  Characters m_PieceCharacter = eEmpty;
  Position m_Position = { 0, int(Letter::eEmpty) };
  size_t m_Id;
  bool m_IsBlocked = false;
  bool m_IsValidMove = false;
};

class Pawn : public Piece
{
public:
  Pawn() = default;
  Pawn(Color color, size_t id) : Piece(color, id)
  {
    if (color == eWhite)
      m_PieceCharacter = eWhitePawn;
    else
      m_PieceCharacter = eBlackPawn;
  }
  void Init(vector<Piece>* allPieces, vector<Pawn>* pawns, Color c);
  bool IsPieceBlocked();
  bool IsValidMove(Piece aPawn, Position newPosition, vector<Piece> *pAllPieces);
};

class King : public Piece
{
public:
  King() = default;
  King(Color color, size_t id) : Piece(color, id)
  {
    if(color == eWhite)
      m_PieceCharacter = eWhiteKing;
    else
      m_PieceCharacter = eBlackKing;
  }
  void Init(vector<Piece>* allPieces, vector<King>* kings, Color c);
};

class Queen : public Piece
{
public:
  Queen() = default;
  Queen(Color color, size_t id) : Piece(color, id)
  {
    if (color == eWhite)
      m_PieceCharacter = eWhiteQueen;
    else
      m_PieceCharacter = eBlackQueen;
  }
  void Init(vector<Piece>* allPieces, vector<Queen>* queens, Color c);
};

class Rook : public Piece
{
public:
  Rook() = default;
  Rook(Color color, size_t id) : Piece(color, id)
  {
    if (color == eWhite)
      m_PieceCharacter = eWhiteRook;
    else
      m_PieceCharacter = eBlackRook;
  }
  void Init(vector<Piece>* allPieces, vector<Rook>* rooks, Color c);
  bool IsPieceBlocked();
  bool IsValidMove(Piece aPawn, Position newPosition, vector<Piece> *pAllPieces);
};

class Knight : public Piece
{
public:
  Knight() = default;
  Knight(Color color, size_t id) : Piece(color, id)
  {
    if (color == eWhite)
      m_PieceCharacter = eWhiteKnight;
    else
      m_PieceCharacter = eBlackKnight;
  }
  void Init(vector<Piece>* allPieces, vector<Knight>* knights, Color c);
};

class Bishop : public Piece
{
public:
  Bishop() = default;
  Bishop(Color color, size_t id) : Piece(color, id)
  {
    if (color == eWhite)
      m_PieceCharacter = eWhiteBishop;
    else
      m_PieceCharacter = eBlackBishop;
  }
  void Init(vector<Piece>* allPieces, vector<Bishop>* bishop, Color c);
};

class Pieces
{
public:
  void CreatePieces(vector<Piece>* allPieces);

private:
  void ClearAllPieces();
  Color colors[2] = { eWhite, eBlack };
  vector<Pawn> m_Pawns;
  vector<King> m_Kings;
  vector<Queen> m_Queens;
  vector<Rook> m_Rooks;
  vector<Knight> m_Knights;
  vector<Bishop> m_Bishops;
};