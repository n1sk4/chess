cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
    Main.cpp
    Board.cpp
    Chess.cpp
    Piece.cpp
)

set(HEADERS
    Common.h
    Board.h
    Chess.h
    Piece.h
)

add_executable(ChessGame ${SOURCES} ${HEADERS})
