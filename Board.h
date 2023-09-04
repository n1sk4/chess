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
  void GetPieceFromPosition(int aRow, Letter aCol, Piece& pPiece);
  void ModifyPieceAtPosition(int aRow, Letter aCol, const Piece& newPiece);

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