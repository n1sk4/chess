#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <limits> 
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <codecvt>
#include <regex>

using namespace std;

const int   ROWS = 8;
const int   COLUMNS = 8;
const int   FIELD_SIZE = 2;
const char  FILL_HORIZONTAL_CHARACTER = '-';
const char  FILL_VERTICAL_CHARACTER = '|';

using Position = int[2];

enum Color { eWhite = 0, eBlack };

enum Characters {
 /* eWhiteKing   = '♔',
  eWhiteQueen  = '♕',
  eWhitePawn   = '♙',
  eWhiteRook   = '♖',
  eWhiteKnight = '♘',
  eWhiteBishop = '♗',

  eBlackKing   = '♚',
  eBlackQueen  = '♛',
  eBlackPawn   = '♟︎',
  eBlackRook   = '♜',
  eBlackKnight = '♞',
  eBlackBishop = '♝'
*/
  eEmpty = ' ',
  eWhiteKing = 'K',
  eWhiteQueen = 'Q',
  eWhitePawn = 'P',
  eWhiteRook = 'R',
  eWhiteKnight = 'N',
  eWhiteBishop = 'B',

  eBlackKing = 'k',
  eBlackQueen = 'q',
  eBlackPawn = 'p',
  eBlackRook = 'r',
  eBlackKnight = 'n',
  eBlackBishop = 'b'
};

enum Coordinates { eRow = 0, eCol };

#define DEFINE_ENUM_ALPHABET(EnumType) \
    enum class EnumType { \
        eEmpty = 0, \
        eA, eB, eC, eD, eE, eF, eG, eH, eI, eJ, \
        eK, eL, eM, eN, eO, eP, eQ, eR, eS, eT, \
        eU, eV, eW, eX, eY, eZ, \
        eCOUNT \
    }

DEFINE_ENUM_ALPHABET(Letter);