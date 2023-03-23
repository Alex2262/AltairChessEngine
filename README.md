# Altair
Altair is a UCI-protocol chess engine that succeeds my old python engine Antares.

## Rating
CCRL Ratings:

| Version | Blitz | Rapid |
|:-------:|:-----:|:-----:|
|  1.0.0  | ----  | 2409  |


## Download
Go to releases for binaries. You can build from the source code with cmake.

## Play
You can play Altair [here](https://lichess.org/@/Altair_Engine)
It is not always online.

Altair can also be played by connecting it to GUIs such as Arena, Cutechess, Banksia, and other UCI-protocol supporting 
chess GUIs.

## Board Representation
Altair uses a 10x12 mailbox array. This board representation gives padding around the 8x8 board for faster move generation. Altair also features
piece lists.

I hope to use bitboards instead one day since they can be much faster if implemented well.

## Move Generation
Offsets / Increments are used in loops to generate the pseudo-legal moves. Within the search and perft, the moves are tested for 
legality, and if the move is not legal, we skip to the next move.

## Search
#### Iterative Deepening
- Aspiration Windows
  - Negamax (Minimax)
    - Alpha-Beta Pruning
      - Reverse Futility Pruning
      - Null Move Pruning
      - Idea similar to Internal Iterative Deepening
      - Principal Variation Search
      - Late Move Reductions
    - Transposition Tables
  - Quiescence Search
    - Delta Pruning
    - Transposition Tables
  
#### Move Ordering
- Transposition Table Move
- Captures
  - Most Valuable Victim - Least Valuable Agressor (MVV-LVA)
  - En passant
- Killer move Heuristic
- Counter move Heuristic
- History move Heuristic
- Promotions
- Castling

## Evaluation
- Material
- Piece Square Tables
- Mobility
- Double, Isolated, Backwards, and Passed Pawns
- Open and semi-open files for rooks, queens and kings
- King's pawn-shield
- Bishop Pair
- Tempo
- King Tropism (Distance from pieces to a King)
- Tapered evaluation between the middlegame and endgame

## Credit and Thanks
- [The Chess Programming Wiki](https://www.chessprogramming.org/Main_Page) contains invaluable resources that I have used.
- [Bitboard Chess Engine in C](https://www.youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs) A nice series that contains implementations
for different ideas and features.
- Gedas and his engine [Chessdotcpp](https://github.com/GediminasMasaitis/chess-dot-cpp) for different ideas and implementations.
- Gedas' [Tuner](https://github.com/GediminasMasaitis/texel-tuner/tree/main/src) for tuning evaluation parameters
- [Weiss](https://github.com/TerjeKir/weiss) Another good resource.
- Engine Programming Discord Server for answering many of my questions
