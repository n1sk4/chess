#pragma once
#include "Common.h"
#include "Piece.h"

struct Fields {
  int Number;
  Letter Letter;
  size_t StringPosition;
};

class Board
{
public:
  Board() = default;
  
  void Draw();
  void Draw(int aPostion, char aChar);
  void Draw(int aNumber, int aLetter, char aChar);
  void Draw(int aNumber, char aLetter, char aChar);
  void MovePiece(int aStartNumber, char aStartLetter, int aEndNumber, char aEndLetter);
  void InitElements();
  bool GetPieceFromPosition(int aRow, Letter aCol, Piece& pPiece);
  void ModifyPieceAtPosition(int aStartRow, Letter aStartCol, int aEndRow, Letter aEndCol, const Piece& newPiece);
  bool CheckIfMoveIsValid(Characters pieceCharacter, Piece piece, Position newPosition);

private:
  void OutputBoard();
  void DrawHorizontalLine(string* aBoard);
  void DrawHorizontalLineLetters(string* pBoard);
  void DrawVerticalLine(string* board, int aRow);
  string OffsetVerticalLine();
  void SetSquareSize(int aSquareSize);
  void SwitchView(Color aColor);

  Letter CharToLetter(char aLetter);

private:
  vector<Piece> m_Pieces;
  string m_HorizontalLine;
  string m_Board;
  vector<Fields> m_Fields;
};