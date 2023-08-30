#pragma once

#include "Common.h"
#include "Piece.h"
#include "Board.h"

class Chess
{
public:
  Chess() {
    this->Start();
  };
private:
  void GetCursorPosition(int& x, int& y);
  void Start();
  void StartMove();
  void EndMove();
  Board m_Board;
};