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
  void InitElements();

private:
  void OutputBoard();
  void DrawHorizontalLine(string* aBoard);
  void DrawHorizontalLineLetters(string* aBoard);
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