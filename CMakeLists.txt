cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
    src/Main.cpp
    src/Board.cpp
    src/Chess.cpp
    src/Piece.cpp
)

set(HEADERS
    include/Common.h
    include/Board.h
    include/Chess.h
    include/Piece.h
)

add_executable(ChessGame ${SOURCES} ${HEADERS})
