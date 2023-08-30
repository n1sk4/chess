#include "Chess.h"

int main()
{
  system("cls");
  Board board;
  board.Board::Draw();
  while (!GetAsyncKeyState(VK_ESCAPE))
  {
    if (GetAsyncKeyState(VK_SPACE))
    {

      int value1;
      char value2;

      std::cout << "Enter two numbers separated by a space: ";
      std::cin >> value1 >> value2;

      system("cls");
      board.Board::Draw(value1, value2);
      Sleep(50);
    }
  }
}