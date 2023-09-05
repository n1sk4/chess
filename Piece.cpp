#include "Piece.h"

void Pieces::CreatePieces(vector<Piece>* allPieces)
{
  ClearAllPieces();

  for (Color c : colors)
  {
    King king; 
    king.Init(allPieces, &m_Kings, c);

    Queen queen;
    queen.Init(allPieces, &m_Queens, c);

    Pawn pawn;
    pawn.Init(allPieces, &m_Pawns, c);

    Rook rook;
    rook.Init(allPieces, &m_Rooks, c);

    Knight knight;
    knight.Init(allPieces, &m_Knights, c);

    Bishop bishop;
    bishop.Init(allPieces, &m_Bishops, c);
  }
}

void Pawn::Init(vector<Piece>* allPieces, vector<Pawn>* pawns, Color c)
{
  for (int i = 1; i <= COLUMNS; i++)
  {
    Pawn pawn(c, pawns->size());

    int rowPostion = 2;
    if (c == eBlack)
      rowPostion = 7;
    pawn.m_Position[eRow] = rowPostion;
    pawn.m_Position[eCol] = i;

    pawns->push_back(pawn);
    allPieces->push_back(pawn);
  }
}


void King::Init(vector<Piece>* allPieces, vector<King>* kings, Color c)
{
  King newKing(c, kings->size());
  kings->push_back(newKing);

  for (auto &currentKing : *kings)
  {
    if (currentKing.m_Color == eWhite)
      currentKing.m_Position[eRow] = 1;

    if (currentKing.m_Color == eBlack)
      currentKing.m_Position[eRow] = 8;

    currentKing.m_Position[eCol] = int(Letter::eE);
    allPieces->push_back(currentKing);
  }
}

void Queen::Init(vector<Piece>* allPieces, vector<Queen>* queens, Color c)
{
  Queen queen(c, queens->size());
  queens->push_back(queen);

  for (auto &queen : *queens)
  {
    if (queen.m_Color == eWhite)
      queen.m_Position[eRow] = 1;

    if (queen.m_Color == eBlack)
      queen.m_Position[eRow] = 8;

    queen.m_Position[eCol] = int(Letter::eD);

    allPieces->push_back(queen);
  }
}

void Rook::Init(vector<Piece>* allPieces, vector<Rook>* rooks, Color c)
{
  for (int i = 0; i < 2; i++)
  {
    Rook rook(c, rooks->size());
    rooks->push_back(rook);
  }

  for (auto &rook : *rooks)
  {
    if (rook.m_Color == eWhite)
    {
      rook.m_Position[eRow] = 1;
    }
    if (rook.m_Color == eBlack)
    {
      rook.m_Position[eRow] = 8;
    }

    if (rook.m_Id % 2)
      rook.m_Position[eCol] = int(Letter::eA);
    else
      rook.m_Position[eCol] = int(Letter::eH);

    allPieces->push_back(rook);
  }
}

void Knight::Init(vector<Piece>* allPieces, vector<Knight>* knights, Color c)
{
  for (int i = 0; i < 2; i++)
  {
    Knight knight(c, knights->size());
    knights->push_back(knight);
  }

  for (auto &knight : *knights)
  {
    if (knight.m_Color == eWhite)
    {
      knight.m_Position[eRow] = 1;
    }
    if (knight.m_Color == eBlack)
    {
      knight.m_Position[eRow] = 8;
    }

    if (knight.m_Id % 2)
      knight.m_Position[eCol] = int(Letter::eB);
    else
      knight.m_Position[eCol] = int(Letter::eG);

    allPieces->push_back(knight);
  }
}

void Bishop::Init(vector<Piece>* allPieces, vector<Bishop>* bishops, Color c)
{
  for (int i = 0; i < 2; i++)
  {
    Bishop bishop(c, bishops->size());
    bishops->push_back(bishop);
  }

  for (auto &bishop : *bishops)
  {
    if (bishop.m_Color == eWhite)
    {
      bishop.m_Position[eRow] = 1;
    }
    if (bishop.m_Color == eBlack)
    {
      bishop.m_Position[eRow] = 8;
    }

    if (bishop.m_Id % 2)
      bishop.m_Position[eCol] = int(Letter::eC);
    else
      bishop.m_Position[eCol] = int(Letter::eF);

    allPieces->push_back(bishop);
  }
}

void Pieces::ClearAllPieces()
{
  m_Kings.clear();
  m_Queens.clear();
  m_Pawns.clear();
  m_Rooks.clear();
  m_Knights.clear();
  m_Bishops.clear();
}

bool Pawn::IsValidMove(Piece pPawn, Position aNewPosition, vector<Piece> *pAllPieces)
{
  bool result = false;
  Position oldPosition;

  if (pAllPieces == nullptr || pAllPieces->size() == 0)
  {
    cout << "No pieces to display! Check order of creation" << endl;
    return result;
  }

  copy(begin(pPawn.m_Position), end(pPawn.m_Position), begin(oldPosition));
  
  if (oldPosition == aNewPosition)
  {
    cout << "Starting position is the same as Ending position" << endl;
    result = false;
  }
  else if (oldPosition[eRow] > aNewPosition[eRow] && pPawn.m_Color == eWhite)
  {
    cout << "Starting position is the wrong direction" << endl;
    result = false;
  }
  else if (oldPosition[eRow] < aNewPosition[eRow] && pPawn.m_Color == eBlack)
  {
    cout << "Starting position is the wrong direction" << endl;
    result = false;
  }
  else if (oldPosition[eCol] != aNewPosition[eCol])
  {
    cout << "Can not move sideways" << endl;
    result = false;
  }
  else
  {
    result = true;
  }
  
  if (Pawn::IsPieceBlocked())
  {
    result = false;
  }

  if (!result)
    cout << __FUNCTION__ << ": Invalid move." << endl;

  return result;
}
bool Pawn::IsPieceBlocked()
{
  return false;
}

bool Rook::IsValidMove(Piece aRook, Position aNewPosition, vector<Piece> *pAllPieces)
{
  bool result = false;
  Position oldPosition;

  if (pAllPieces == nullptr || pAllPieces->size() == 0)
  {
    cout << "No pieces to display! Check order of creation" << endl;
    return result;
  }

  copy(begin(aRook.m_Position), end(aRook.m_Position), begin(oldPosition));

  if (oldPosition == aNewPosition)
  {
    //cout << "Starting position is the same as Ending position" << endl;
    result = false;
  }
  else if (oldPosition[eCol] == aNewPosition[eCol] && oldPosition[eRow] != aNewPosition[eRow])
  {
    result = true;
  }
  else if ((oldPosition[eRow] == aNewPosition[eRow]) && (oldPosition[eCol] != aNewPosition[eCol]))
  {
    result = true;
  }
  else
  {
    result = false;
  }
  
  if (Rook::IsPieceBlocked())
  {
    result = false;
  }

  if (!result)
    cout << __FUNCTION__ << ": Invalid move." << endl;

  return result;
}
bool Rook::IsPieceBlocked()
{
  return false;
}

bool Bishop::IsValidMove(Piece aBishop, Position aNewPosition, vector<Piece> *pAllPieces)
{
  bool result = false;
  Position oldPosition;

  if (pAllPieces == nullptr || pAllPieces->size() == 0)
  {
    cout << "No pieces to display! Check order of creation" << endl;
    return result;
  }

  copy(begin(aBishop.m_Position), end(aBishop.m_Position), begin(oldPosition));

  // Check if the absolute difference in file and rank positions is the same
  int fileDifference = abs(oldPosition[eRow] - aNewPosition[eRow]);
  int rankDifference = abs(oldPosition[eCol] - aNewPosition[eCol]);

  if (oldPosition == aNewPosition)
  {
    //cout << "Starting position is the same as Ending position" << endl;
    result = false;
  }
  else if (fileDifference == rankDifference)
  {
    result = true;
  }
  
  if (Bishop::IsPieceBlocked())
  {
    result = false;
  }

  if (!result)
    cout << __FUNCTION__ << ": Invalid move." << endl;

  return result;
}
bool Bishop::IsPieceBlocked()
{
  return false;
}

bool Queen::IsValidMove(Piece aQueen, Position aNewPosition, vector<Piece> *pAllPieces)
{
  bool result = false;
  Position oldPosition;

  if (pAllPieces == nullptr || pAllPieces->size() == 0)
  {
    cout << "No pieces to display! Check order of creation" << endl;
    return result;
  }

  copy(begin(aQueen.m_Position), end(aQueen.m_Position), begin(oldPosition));

  // Check if the absolute difference in file and rank positions is the same
  int fileDifference = abs(oldPosition[eRow] - aNewPosition[eRow]);
  int rankDifference = abs(oldPosition[eCol] - aNewPosition[eCol]);

  if (oldPosition == aNewPosition)
  {
    //cout << "Starting position is the same as Ending position" << endl;
    result = false;
  }
  else if (fileDifference == rankDifference)
  {
    result = true;
  }
  else if (oldPosition[eCol] == aNewPosition[eCol] && oldPosition[eRow] != aNewPosition[eRow])
  {
    result = true;
  }
  else if ((oldPosition[eRow] == aNewPosition[eRow]) && (oldPosition[eCol] != aNewPosition[eCol]))
  {
    result = true;
  }

  if (Queen::IsPieceBlocked())
  {
    result = false;
  }

  if (!result)
    cout << __FUNCTION__ << ": Invalid move." << endl;

  return result;
}
bool Queen::IsPieceBlocked()
{
  return false;
}

bool King::IsValidMove(Piece aKing, Position aNewPosition, vector<Piece> *pAllPieces)
{
  bool result = false;
  Position oldPosition;

  if (pAllPieces == nullptr || pAllPieces->size() == 0)
  {
    cout << "No pieces to display! Check order of creation" << endl;
    return result;
  }

  copy(begin(aKing.m_Position), end(aKing.m_Position), begin(oldPosition));

  // Check if the absolute difference in file and rank positions is the same
  int fileDifference = abs(oldPosition[eRow] - aNewPosition[eRow]);
  int rankDifference = abs(oldPosition[eCol] - aNewPosition[eCol]);
  
  if (oldPosition == aNewPosition)
  {
    //cout << "Starting position is the same as Ending position" << endl;
    result = false;
  }
  else if (fileDifference == rankDifference)
  {
    result = true;
  }
  else if (oldPosition[eCol] == aNewPosition[eCol] && oldPosition[eRow] != aNewPosition[eRow])
  {
    result = true;
  }
  else if ((oldPosition[eRow] == aNewPosition[eRow]) && (oldPosition[eCol] != aNewPosition[eCol]))
  {
    result = true;
  }

  if (!result)
    cout << __FUNCTION__ << ": Invalid move." << endl;

  return result;
}
bool King::IsPieceBlocked()
{
  return false;
}

bool Knight::IsValidMove(Piece aKnight, Position aNewPosition, vector<Piece> *pAllPieces)
{
  bool result = false;
  Position oldPosition;

  if (pAllPieces == nullptr || pAllPieces->size() == 0)
  {
    cout << "No pieces to display! Check order of creation" << endl;
    return result;
  }

  copy(begin(aKnight.m_Position), end(aKnight.m_Position), begin(oldPosition));

  // Check if the absolute difference in file and rank positions is the same
  int fileDifference = abs(oldPosition[eRow] - aNewPosition[eRow]);
  int rankDifference = abs(oldPosition[eCol] - aNewPosition[eCol]);

  // Check if the move is an L-shape (2 squares in one direction and 1 square in another)
  result = (fileDifference == 2 && rankDifference == 1) || (fileDifference == 1 && rankDifference == 2);

  if (!result)
    cout << __FUNCTION__ << ": Invalid move." << endl;

  return result;
}

bool Knight::IsPieceBlocked()
{
  return false;
}