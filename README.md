# CLI Chess
I like playing chess in my free time, but I'm not that good with a score of 1.1k on Chess.com -> @nikizg
But it inspired me to create a CLI Chess to progress mine C++ programming skills and try out some arhitecture patterns.

This is my one day project that turned into a bigger one (Unexpectedly, said no one ever :)

General plan is:
 * Have all standard Chess rules
 * Call Stockfish API to generate best moves, or play vs the computer
 * Use web socket to play remotely vs friends

# Build
Using CMake:
```
 mkdir build
 cd build
 cmake ..
 cmake --build . --target Chess --config Release
```

# Game Look

## Starting screen:

![Start](https://github.com/n1sk4/chess/assets/92214769/bee3835f-91ea-4d20-bbbd-ae5c37b8ee37)

## User input under the chess board:

![StartInput](https://github.com/n1sk4/chess/assets/92214769/488a05b4-107c-4e8e-9022-e49c43c5074a)

## One game in:

![GameIn](https://github.com/n1sk4/chess/assets/92214769/d10d0cc5-fc42-4695-adff-3342dee6abba)

Type in: A1 -> A5:

![Blocked](https://github.com/n1sk4/chess/assets/92214769/3ea2c670-2d6d-4d00-ba6f-3f3a3efb1c06)

Type in: A1 -> B5:

![Invalid](https://github.com/n1sk4/chess/assets/92214769/4abf9984-af5a-4a97-8802-f04d67784bc4)

## Piece eaten:

![Eaten](https://github.com/n1sk4/chess/assets/92214769/14f3546b-4e38-441f-9ad8-160f02c20536)


# Features:
 
 * Moving pieces
 
 * Eating other pieces
 
 * Not moving if blocked or not in piece's movement pattern

