﻿#include "Board.h"

/**
 Brief: This function is used to initialize the member varibles of a Board object
  This must be called before using any of the other overloaded Draw functions

  board example:
       A   B   C   D   E   F   G   H
     ---------------------------------
     |R  |N  |B  |Q  |K  |B  |N  |R  |
    1|   |   |   |   |   |   |   |   |1
     ---------------------------------
     |P  |P  |P  |P  |P  |P  |P  |P  |
    2|   |   |   |   |   |   |   |   |2
     ---------------------------------
     |   |   |   |   |   |   |   |   |
    3|   |   |   |   |   |   |   |   |3
     ---------------------------------
     |   |   |   |   |   |   |   |   |
    4|   |   |   |   |   |   |   |   |4
     ---------------------------------
     |   |   |   |   |   |   |   |   |
    5|   |   |   |   |   |   |   |   |5
     ---------------------------------
     |   |   |   |   |   |   |   |   |
    6|   |   |   |   |   |   |   |   |6
     ---------------------------------
     |P  |P  |P  |P  |P  |P  |P  |P  |
    7|   |   |   |   |   |   |   |   |7
     ---------------------------------
     |R  |N  |B  |Q  |K  |B  |N  |R  |
    8|   |   |   |   |   |   |   |   |8
     ---------------------------------
       A   B   C   D   E   F   G   H
 */
void Board::Draw()
{
  InitElements();
  OutputBoard();
}

/**
 Brief: This function is used to Insert/Move/Delete a character across the board

 @param aPosition = an integer input that coresponds to the position of a character 
 in a string that represents the board

 */
void Board::Draw(int aPostion, char aChar)
{
  m_Board[aPostion] = aChar;
  OutputBoard();
}

/**
 Brief: This function is used to Insert/Move/Delete a character across the board

 @param aNumber = an integer input that coresponds to the Number on the vertical axis
 @param aLetter = an integer input that coresponds to the Number on the horizontal axis

 */
void Board::Draw(int aNumber, int aLetter, char aChar)
{
  size_t position = 0;
  for (Fields& field : m_Fields)
  {
    if (aNumber <= 0 || aLetter <= 0 || aNumber >= ROWS || aLetter >= ROWS)
      continue;

    if (field.Number == aNumber && field.Letter == Letter(aLetter))
    {
      position = field.StringPosition;
      break;
    }
  }

  if (position)
    m_Board[position] = aChar;
  
  OutputBoard();
}

/**
 Brief: This function is used to Move a Piece character across the board

 @param aNumber = an integer input that coresponds to the Number on the vertical axis
 @param aLetter = an char input that coresponds to the Letter on the horizontal axis

 */
void Board::MovePiece(int aStartNumber, char aStartLetter, int aEndNumber, char aEndLetter, Piece pPiece)
{
  Letter startLetter = CharToLetter(aStartLetter);
  Letter endLetter = CharToLetter(aEndLetter);
  size_t startPosition = 0;
  size_t endPosition = 0;

  if (aStartNumber <= 0 || startLetter <= Letter::eEmpty || aStartNumber > ROWS || startLetter >= Letter::eCOUNT)
    return;

  if (aEndNumber <= 0 || endLetter <= Letter::eEmpty || aEndNumber > ROWS || endLetter >= Letter::eCOUNT)
    return;

  for (Fields& field : m_Fields)
  {
    if (field.Number == aStartNumber && field.Letter == startLetter)
    {
      startPosition = field.StringPosition;
      break;
    }
  }
  GetPieceFromPosition(aStartNumber, startLetter, pPiece);

  for (Fields& field : m_Fields)
  {
    if (field.Number == aEndNumber && field.Letter == endLetter)
    {
      endPosition = field.StringPosition;
      break;
    }
  }


  if (startPosition && (startLetter != Letter::eEmpty))
  {
    if (endPosition && (endLetter != Letter::eEmpty))
    {
      m_Board[startPosition] = ' ';
      m_Board[endPosition] = pPiece.m_PieceCharacter;
    }
  }

  OutputBoard();
}

/**
 Brief: This function is used to Insert/Move/Delete a character across the board

 @param aNumber = an integer input that coresponds to the Number on the vertical axis
 @param aLetter = an char input that coresponds to the Letter on the horizontal axis 
 
 */
void Board::Draw(int aNumber, char aLetter, char aChar)
{
  Letter letter = CharToLetter(aLetter);
  size_t position = 0;

  if (aNumber <= 0 || letter <= Letter::eEmpty || aNumber > ROWS || letter >= Letter::eCOUNT)
    return;

  for (Fields& field : m_Fields)
  {
    if (field.Number == aNumber && field.Letter == letter)
    {
      position = field.StringPosition;
      break;
    }
  }

  if (position && (letter != Letter::eEmpty))
    m_Board[position] = aChar;
  
  OutputBoard();
}

void Board::InitElements()
{
  m_Fields.clear();
  m_Board.clear();
  m_Pieces.clear();
  m_HorizontalLine.clear();

  Pieces pieces;
  pieces.CreatePieces(&m_Pieces);

  SetSquareSize(FIELD_SIZE);
  DrawHorizontalLineLetters(&m_Board);
  for (int i = 0; i < ROWS; i++)
  {
    DrawHorizontalLine(&m_Board);
    DrawVerticalLine(&m_Board, i);
  }
  DrawHorizontalLine(&m_Board);
  DrawHorizontalLineLetters(&m_Board);

  for (Piece& piece : m_Pieces)
  {
    size_t position = string::npos;
    for (Fields& field : m_Fields)
    {
      if (piece.m_Position[eRow] == 0 || piece.m_Position[eCol] == 0)
      {
        continue;
      }

      if (field.Number == piece.m_Position[eRow] && field.Letter == Letter(piece.m_Position[eCol]))
      {
        position = field.StringPosition;
        break;
      }
    }

    if (position == std::string::npos)
      continue;

    m_Board[position] = piece.m_PieceCharacter;
  }
}

void Board::SetSquareSize(int aSquareSize)
{
  if (m_HorizontalLine.length() >= aSquareSize)
    return;

  for (int i = 0; i < aSquareSize; ++i)
  {
    m_HorizontalLine += FILL_HORIZONTAL_CHARACTER;
  }
}

void Board::DrawHorizontalLine(string* aBoard)
{
  *aBoard += OffsetVerticalLine();
  *aBoard += FILL_HORIZONTAL_CHARACTER;
  for (int i = 0; i < COLUMNS; i++)
  {
    *aBoard += m_HorizontalLine;
  }
  *aBoard += "\n";
}

/**@brief This function draws horizontal lines for 8x8 chess board
*@param aBoard = a string that represents the board
*/
void Board::DrawHorizontalLineLetters(string* aBoard)
{
  *aBoard += OffsetVerticalLine();
  size_t interval = FIELD_SIZE / 2;
  string offset(interval, ' ');
  *aBoard += offset;
  interval *= 2;
  size_t totalWidth = COLUMNS * interval;

  char startLetter = 'A';

  for (size_t i = 0; i < totalWidth; ++i)
  {
    //TODO: There's an issue when FIELD_SIZE % 2 != 0
    //Refactor that FIELD_SIZE can be odd number
    if (i % interval == 0)
      *aBoard += char(startLetter + (i / interval));
    else
      *aBoard += ' ';
  }
  
  *aBoard += "\n";
}

/**@brief This function draws vertical lines for 8x8 chess board
*@param aBoard = a string that represents the board
*@param aRow = an integer value that represents the row number
*/
void Board::DrawVerticalLine(string* board, int aRow)
{ 
  Fields fields{};
  fields.Number = 0;
  fields.Letter = Letter::eEmpty;
  fields.StringPosition = 0;

  int halfsize = FIELD_SIZE / 2;
  for (int i = 0; i < halfsize; i++)
  {
    if (halfsize/2 == i)
      *board += to_string(aRow + 1);
    else
      *board += OffsetVerticalLine();

    for (int j = 0; j <= COLUMNS * FIELD_SIZE; j++)
    {
      if (j % FIELD_SIZE)
      {
        *board += " ";
      }
      else
      {
        *board += FILL_VERTICAL_CHARACTER;
        fields.Letter = Letter(j / FIELD_SIZE + 1);
        fields.Number = aRow + 1;
        fields.StringPosition = board->length();
        m_Fields.push_back(fields); 
      }
    }

    if (halfsize / 2 == i)
      *board += to_string(aRow + 1);

    *board += "\n";
  }
}

string Board::OffsetVerticalLine()
{
  string offset(1, ' ');
  return offset;
}

void Board::SwitchView(Color aColor)
{
  
}

void Board::OutputBoard()
{
  cout << m_Board << endl;
}

Letter Board::CharToLetter(char aLetter)
{
  char lowercaseLetter = tolower(aLetter);
  switch (lowercaseLetter) {
#define HANDLE_CHAR(letter, ch) \
        case ch: \
            return Letter::letter;

      HANDLE_CHAR(eA, 'a')
      HANDLE_CHAR(eB, 'b')
      HANDLE_CHAR(eC, 'c')
      HANDLE_CHAR(eD, 'd')
      HANDLE_CHAR(eE, 'e')
      HANDLE_CHAR(eF, 'f')
      HANDLE_CHAR(eG, 'g')
      HANDLE_CHAR(eH, 'h')
      HANDLE_CHAR(eI, 'i')
      HANDLE_CHAR(eJ, 'j')
      HANDLE_CHAR(eK, 'k')
      HANDLE_CHAR(eL, 'l')
      HANDLE_CHAR(eM, 'm')
      HANDLE_CHAR(eN, 'n')
      HANDLE_CHAR(eO, 'o')
      HANDLE_CHAR(eP, 'p')
      HANDLE_CHAR(eQ, 'q')
      HANDLE_CHAR(eR, 'r')
      HANDLE_CHAR(eS, 's')
      HANDLE_CHAR(eT, 't')
      HANDLE_CHAR(eU, 'u')
      HANDLE_CHAR(eV, 'v')
      HANDLE_CHAR(eW, 'w')
      HANDLE_CHAR(eX, 'x')
      HANDLE_CHAR(eY, 'y')
      HANDLE_CHAR(eZ, 'z')
#undef HANDLE_CHAR
  default:
    return Letter::eEmpty; // Handle unknown characters
  }
}

void Board::GetPieceFromPosition(int aRow, Letter aCol, Piece& pPiece)
{
  for (Piece piece : m_Pieces)
  {
    if (piece.m_Position[eRow] == aRow && piece.m_Position[eCol] == int(aCol))
    {
      pPiece = piece;
      break;
    }
  }
}