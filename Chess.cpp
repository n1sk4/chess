#include "Chess.h"

void Chess::Start()
{
  system("cls");
  m_Board.Draw();
  while (!GetAsyncKeyState(VK_ESCAPE))
  {
    StartMove();
    EndMove();
  }
}


void Chess::GetCursorPosition(int& x, int& y) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  x = csbi.dwCursorPosition.X;
  y = csbi.dwCursorPosition.Y;
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
  CONSOLE_SCREEN_BUFFER_INFO cbsi;
  if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
  {
    return cbsi.dwCursorPosition;
  }
  else
  {
    // The function failed. Call GetLastError() for details.
    COORD invalid = { 0, 0 };
    return invalid;
  }
}

void Chess::StartMove()
{
  int value1;
  char value2;
  int value3;
  char value4{};
  cout << "Enter start position and end position ";
  cin >> value1 >> value2 >> value3 >> value4;
  system("cls");
  m_Board.MovePiece(value1, value2, value3, value4, m_CurrentPiece);
  Sleep(50);
}

void Chess::EndMove()
{
  int value1;
  char value2;
  char value3;
  cout << "Enter two numbers separated by a space: ";
  cin >> value1 >> value2 >> value3;
  system("cls");
  m_Board.Draw(value1, value2, value3);
  Sleep(50);
}