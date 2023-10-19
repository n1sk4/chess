#pragma once
#include "..\include\Board.h"

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
bool Board::MovePiece(int aStartNumber, char aStartLetter, int aEndNumber, char aEndLetter)
{
  Piece piece;
  Letter startLetter = CharToLetter(aStartLetter);
  Letter endLetter = CharToLetter(aEndLetter);
  size_t startPosition = 0;
  size_t endPosition = 0;

  Position oldPosition;
  oldPosition[eRow] = aStartNumber;
  oldPosition[eCol] = int(startLetter);
  Position newPosition;
  newPosition[eRow] = aEndNumber;
  newPosition[eCol] = int(endLetter);

  if (aStartNumber <= 0 || startLetter <= Letter::eEmpty || aStartNumber > ROWS || startLetter >= Letter::eCOUNT)
    return false;

  if (aEndNumber <= 0 || endLetter <= Letter::eEmpty || aEndNumber > ROWS || endLetter >= Letter::eCOUNT)
    return false;

  for (Fields& field : m_Fields)
  {
    if (field.Number == aStartNumber && field.Letter == startLetter)
    {
      startPosition = field.StringPosition;
      break;
    }
  }

  if (!GetPieceFromPosition(aStartNumber, startLetter, piece))
  {
    cout << "Type in a field with a piece" << endl;
    return false;
  }

  Characters pieceCharacter = piece.m_PieceCharacter;

  if (!CheckIfMoveIsValid(pieceCharacter, piece, newPosition))
    return false;

  if (!CheckIfPieceIsBlocked(pieceCharacter, piece, newPosition))
    return false;

  for (Fields& field : m_Fields)
  {
    if (field.Number == aEndNumber && field.Letter == endLetter)
    {
      endPosition = field.StringPosition;
      break;
    }
  }

  // Move piece
  piece.m_Position[eRow] = aEndNumber;
  piece.m_Position[eCol] = static_cast<int>(endLetter);

  if (startPosition && (startLetter != Letter::eEmpty))
  {
    if (endPosition && (endLetter != Letter::eEmpty))
    {
      m_Board[startPosition] = ' ';
      ModifyPieceAtPosition(aStartNumber, startLetter, aEndNumber, endLetter, piece);
      m_Board[endPosition] = piece.m_PieceCharacter;
    }
  }

  /*for (auto piece : m_Pieces)
  {
    cout << "Piece char: " << char(piece.m_PieceCharacter) << " , col: " << piece.m_Position[eCol] << " row:" << piece.m_Position[eRow] << endl;
  }*/

  return true;
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

/**@brief This function initializes all elements of a playing board
*/
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

/**@brief This function sets the top square size
*@param aSquareSize = integer value for square size
*/
void Board::SetSquareSize(int aSquareSize)
{
  if (m_HorizontalLine.length() >= aSquareSize)
    return;

  for (int i = 0; i < aSquareSize; ++i)
  {
    m_HorizontalLine += FILL_HORIZONTAL_CHARACTER;
  }
}

/**@brief This function draws horizontal lines for a chess board
*@param aBoard = a string that represents the board
*/
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

/**@brief This function draws horizontal line letters for a chess board
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

/**@brief This function outputs the string that represents the board
*/
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
    return Letter::eEmpty;
  }
}

bool Board::GetPieceFromPosition(int aRow, Letter aCol, Piece& pPiece)
{
  for (Piece piece : m_Pieces)
  {
    if (piece.m_Position[eRow] == aRow && piece.m_Position[eCol] == static_cast<int>(aCol))
    {
      pPiece = piece;
      return true;
    }
  }

  return false;
}

bool Board::GetPieceFromPosition(int aRow, int aCol, Piece& pPiece)
{
  for (Piece piece : m_Pieces)
  {
    if (piece.m_Position[eRow] == aRow && piece.m_Position[eCol] == aCol)
    {
      pPiece = piece;
      return true;
    }
  }

  return false;
}

void Board::ModifyPieceAtPosition(int aStartRow, Letter aStartCol, int aEndRow, Letter aEndCol, const Piece& newPiece)
{
  for (auto& piece : m_Pieces) {
    if (piece.m_Position[eRow] == aStartRow && piece.m_Position[eCol] == static_cast<int>(aStartCol))
    {
      piece = newPiece;
      Position targetValues = { aEndRow, static_cast<int>(aEndCol) };
      Characters newPieceCharacter = newPiece.m_PieceCharacter;

      //Erase piece if eaten
      auto it = find_if(m_Pieces.begin(), m_Pieces.end(), [targetValues, newPieceCharacter](const Piece& p) 
        { return p.m_Position[eRow] == targetValues[eRow] && 
                 p.m_Position[eCol] == targetValues[eCol] && 
                 p.m_PieceCharacter != newPieceCharacter;});
      if (it != m_Pieces.end()) {
        m_Pieces.erase(it);
      }

      return;
    }
  }
}

bool Board::CheckIfMoveIsValid(Characters aPieceCharacter, Piece aPiece, Position aNewPosition)
{
  bool isValid = true;

  if (aPieceCharacter == eWhiteKing || aPieceCharacter == eBlackKing)
  {
    King newKing;
    isValid = newKing.IsValidMove(aPiece, aNewPosition, &m_Pieces);
  }
  else if (aPieceCharacter == eWhiteQueen || aPieceCharacter == eBlackQueen)
  {
    Queen newQueen;
    isValid = newQueen.IsValidMove(aPiece, aNewPosition, &m_Pieces);
  }
  else if (aPieceCharacter == eWhitePawn || aPieceCharacter == eBlackPawn)
  {
    Pawn newPawn;
    isValid = newPawn.IsValidMove(aPiece, aNewPosition, &m_Pieces);
  }
  else if (aPieceCharacter == eWhiteRook || aPieceCharacter == eBlackRook)
  {
    Rook newRook;
    isValid = newRook.IsValidMove(aPiece, aNewPosition, &m_Pieces);
  }
  else if (aPieceCharacter == eWhiteBishop || aPieceCharacter == eBlackBishop)
  {
    Bishop newBishop;
    isValid = newBishop.IsValidMove(aPiece, aNewPosition, &m_Pieces);
  }
  else if (aPieceCharacter == eWhiteKnight || aPieceCharacter == eBlackKnight)
  {
    Knight newKnight;
    isValid = newKnight.IsValidMove(aPiece, aNewPosition, &m_Pieces);
  }

  return isValid;
}

bool Board::CheckIfPieceIsBlocked(Characters aPieceCharacter, Piece aPiece, Position aNewPosition)
{
  bool isValid = true;

  if (aPieceCharacter == eWhiteKing || aPieceCharacter == eBlackKing)
  {
    King newKing; 
    newKing.IsPieceBlocked(false);
  }
  else if (aPieceCharacter == eWhiteQueen || aPieceCharacter == eBlackQueen)
  {
    Queen newQueen;
    newQueen.IsPieceBlocked(false);
  }
  else if (aPieceCharacter == eWhitePawn || aPieceCharacter == eBlackPawn)
  {
    Pawn newPawn;
    newPawn.IsPieceBlocked(false);
  }
  else if (aPieceCharacter == eWhiteRook || aPieceCharacter == eBlackRook)
  {
    Rook newRook;
    bool isBlocked = IsRookBlocked(&aPiece, aNewPosition);
    newRook.IsPieceBlocked(isBlocked);
    return !isBlocked;

  }
  else if (aPieceCharacter == eWhiteBishop || aPieceCharacter == eBlackBishop)
  {
    Bishop newBishop;
    newBishop.IsPieceBlocked(false);
  }
  else if (aPieceCharacter == eWhiteKnight || aPieceCharacter == eBlackKnight)
  {
    Knight newKnight;
    newKnight.IsPieceBlocked(false);
  }

  return isValid;
}

string Board::GetBoard()
{
  return m_Board;
}

bool Board::IsRookBlocked(Piece* aPiece, Position aNewPosition)
{
  bool isBlocked = false;
  int oldRow = aPiece->m_Position[eRow];
  int oldCol = aPiece->m_Position[eCol];
  int newRow = aNewPosition[eRow];
  int newCol = aNewPosition[eCol];

  if (oldRow == newRow)
  {
    Piece p;
    for (int col = oldCol; col <= newCol; col++)
    {
      if (GetPieceFromPosition(newRow, col, p))
      {
        isBlocked = true;
        break;
      }
    }
  }
  
  if (oldCol == newCol)
  {
    Piece p;
    for (int row = oldRow; row <= newRow; row++)
    {
      if (GetPieceFromPosition(row, newCol, p))
      {
        isBlocked = true;
        break;
      }
    }
  }

  return isBlocked;
}