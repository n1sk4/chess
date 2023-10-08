# CLI Chess
I like playing chess in my free time, but I'm not that good with a score of 1.1k on Chess.com -> @nikizg
But it inspired me to create a CLI Chess to progress mine C++ programming skills and try out some arhitecture patterns.

This is my one day project that turned into a bigger one (Unexpectedly, said no one ever :)

General plan is:
 * Have all standard Chess rules
 * Call Stockfish API to generate best moves, or play vs the computer
 * Use web socket to play remotely vs friends

Starting screen:

![Chess board](https://github.com/n1sk4/chess/assets/92214769/37755ffc-4d38-4394-a197-0d3ff053ec71)

User input under the chess board:

![User input](https://github.com/n1sk4/chess/assets/92214769/e2e8cfdd-fd14-43ff-8089-e2dcb2d4fb5a)

Features for now:
 
 * Moving pieces
 
 * Eating other pieces
 
 * Not moving if blocked or not in piece's movement pattern

One game in:

![Game in](https://github.com/n1sk4/chess/assets/92214769/5908f17d-a451-40c8-b0e2-a8a2fbe70b5f)

Type in: A1 -> A5:

![Blocked](https://github.com/n1sk4/chess/assets/92214769/d4d4b4d3-3782-4549-93a6-174de270070d)

Type in: A1 -> B5:

![Wrong pattern](https://github.com/n1sk4/chess/assets/92214769/069a4c9b-5544-4059-8306-b5dd051deb8e)

Piece eaten:

![Eat](https://github.com/n1sk4/chess/assets/92214769/2c9b2f53-6be6-4ebe-ae46-4be3a5681a3b)
