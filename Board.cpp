#include "Board.h"

void Board::Draw(int aPostion)
{
  InitElements();
  m_Board[aPostion] = 'P'; 
  OutputBoard();
}

void Board::Draw(int aNumber, int aLetter)
{
  InitElements();
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
    m_Board[position] = 'X';
  
  OutputBoard();
}


void Board::Draw(int aNumber, char aLetter)
{
  InitElements();

  Letter letter = CharToLetter(aLetter);
  cout << to_string(int(letter)) << endl;
  size_t position = 0;

  for (Fields& field : m_Fields)
  {
    if (aNumber <= 0 || letter <= Letter::eEmpty || aNumber > ROWS || letter >= Letter::eCOUNT)
      continue;

    if (field.Number == aNumber && field.Letter == letter)
    {
      position = field.StringPosition;
      break;
    }
  }

  if (position && (letter != Letter::eEmpty))
    m_Board[position] = 'X';
  
  OutputBoard();
}

void Board::Draw()
{
  InitElements(); 
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
      if (piece.Position[eRow] == 0 || piece.Position[eCol] == 0)
        continue;

      if (field.Number == piece.Position[eRow] && field.Letter == Letter(piece.Position[eCol]))
      {
        position = field.StringPosition;
        break;
      }
    }

    if (position == std::string::npos)
      continue;

    m_Board[position] = piece.PieceCharacter;
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

void Board::DrawHorizontalLineLetters(string* aBoard)
{
  *aBoard += OffsetVerticalLine();
  size_t interval = m_HorizontalLine.length() / 2;
  string offset(interval, ' ');
  *aBoard += offset;
  interval *= 2;
  size_t totalWidth = COLUMNS * interval;
  char startLetter = 'A';

  for (size_t i = 0; i < totalWidth; ++i)
  {
    if (i % interval == 0)
      *aBoard += char(startLetter + (i / interval));
    else
      *aBoard += ' ';
  }
  
  *aBoard += "\n";
}

/**@brief This function draws vertical lines for 8x8 chess board*/
void Board::DrawVerticalLine(string* board, int aRow)
{ 
  Fields fields;
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