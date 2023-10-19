#pragma once

#include "..\include\Common.h"
#include "..\include\Piece.h"
#include "..\include\Board.h"

class Chess
{
public:
  Chess() {
    this->Start();
  };
private:
  void GetCursorPosition(int& x, int& y);
  void Start();
  void Move();
  bool GetPositionFromInput(string aMessage, int *pNumber, char *pLetter);
  Board m_Board;
  Piece m_CurrentPiece;
};