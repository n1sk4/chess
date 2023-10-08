#pragma once
#include "Chess.h"

void Chess::Start()
{
  system("cls");
  m_Board.Draw();
  while (!GetAsyncKeyState(VK_ESCAPE))
  {
    Move();
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

void Chess::Move()
{
  int startNumber, endNumber;
  char startLetter, endLetter;
  bool isMove;
  isMove = GetPositionFromInput("Enter start position: ", &startNumber, &startLetter);
  isMove = GetPositionFromInput("Enter end position: ", &endNumber, &endLetter);
  system("cls");
  if (isMove)
  {
    int position;
    cout << "Type in position: ";
    cin >> position;
    m_Board.Draw(position, 'X');
  }
  else 
  {
    m_Board.MovePiece(startNumber, startLetter, endNumber, endLetter);
  }
  cout << endl;
  m_Board.OutputBoard();
  Sleep(50);
}

bool Chess::GetPositionFromInput(string aMessage, int *pNumber, char *pLetter)
{
  string input;
  regex pattern1("^[a-hA-H][1-8]$"); // letter and number, e.g. D2
  regex pattern2("^[1-8][a-hA-H]$"); // number and letter, e.g. 2D

  while (true) {
    cout << aMessage;
    cin >> input;

    if (regex_match(input, pattern1) && input.length() == 2) 
    {
      *pNumber = input[1] - '0';
      *pLetter = input[0];
      break;
    }
    else if (regex_match(input, pattern2) && input.length() == 2) 
    {
      *pNumber = input[0] - '0';
      *pLetter = input[1];
      break;
    }
    else if (input == "help")
    {
      cout << "Valid input is a string with two characters eg: 2b [1-8][a-hA-H]" << endl;
    }
    else if (input == "bypos")
    {
      return 1;
    }
    else 
    {
      cout << "Invalid input. Please try again. (If you need help, type in 'help')" << endl;
    }
  }
  return 0;
}