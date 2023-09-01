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
  GetPositionFromInput("Enter start position: ", &startNumber, &startLetter);
  GetPositionFromInput("Enter end position: ", &endNumber, &endLetter);
  cout << startNumber << startLetter << endNumber << endLetter << endl;
  system("cls");
  m_Board.MovePiece(startNumber, startLetter, endNumber, endLetter, m_CurrentPiece);
  Sleep(50);
}

bool Chess::GetPositionFromInput(string aMessage, int *pNumber, char *pLetter)
{
  string input;
  regex pattern("^[1-8][a-hA-H]$");

  while (true) {
    cout << aMessage;
    cin >> input;

    if (regex_match(input, pattern) && input.length() == 2) {
      *pNumber = input[0] - '0';
      *pLetter = input[1];
      break;
    }
    else if (input == "help")
    {
      cout << "Valid input is a string with two characters eg: 2b [1-8][a-hA-H]" << endl;
    }
    else {
      cout << "Invalid input. Please try again. (If you need help, type in 'help')" << endl;
    }
  }
}