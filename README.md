# Altair
Altair is a UCI-protocol chess engine that succeeds my old python engine Antares.

## Ratings
[CCRL Rating List](http://ccrl.chessdom.com/ccrl/) \
[MCERL Rating list](https://www.chessengeria.com/mcerl)

| Version | CCRL Blitz | CCRL Rapid | MCERL |
|:-------:|:----------:|:----------:|:-----:|
|  1.0.0  |    ----    |    2409    | ----  |
|  2.0.0  |    2875    |    2808    | 2639  |


## Download
The release provides different binaries. \
Altair can also be built from the source code with cmake and make.

## Play
You can play against Altair by using it with a chess GUI such as Arena, Cutechess, Banksia etc. \
You can also play against Altair on lichess [here](https://lichess.org/@/Altair_Engine), but it is not always online.

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
Altair utilizes many techniques for its search, or calculation of moves and different positions. 
At the basis, Altair uses a version of minimax. Different methods of selection, pruning, and reductions enables
it to narrow down the amount of positions it has to calculate. \

A brief description of Altair's search layout: 

- Framework
  - Iterative Deepening
  - Aspiration Windows
- Negamax (Minimax)
  - Alpha-Beta Pruning
  - Different Search Techniques:
    - Reverse Futility Pruning
    - Razoring
    - Null Move Pruning
    - Internal Iterative Reductions
    - Principal Variation Search
    - Singular Extensions
    - Multi-cut
    - Late Move Reductions
    - Late Move Pruning
  - Transposition Tables
- Quiescence Search
  - Stand-pat
  - Delta Pruning
  - Transposition Tables
  
#### Move Ordering
- Transposition Table Move
- Promotions
- Captures
  - Most Valuable Victim - Least Valuable Aggressor (MVV-LVA)
  - En passant
- Killer move Heuristic
- Counter move Heuristic
- History move Heuristic
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
- [The Chess Programming Wiki](https://www.chessprogramming.org/Main_Page) 
contains invaluable resources that I have used.
- [Bitboard Chess Engine in C](https://www.youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs)
A nice video series that contains implementations for different ideas and features.
- @archishou for help and support in the development and improvement of my engine.
- @GediminasMasaitis and his engine [Chessdotcpp](https://github.com/GediminasMasaitis/chess-dot-cpp) 
for different ideas and implementations.
- Gedas' [Texel Tuner](https://github.com/GediminasMasaitis/texel-tuner/tree/main/src) for tuning evaluation parameters.
- [Weiss](https://github.com/TerjeKir/weiss); Another great inspiration and resource.
- The Engine Programming Discord Server for answering many of my questions.
- Everyone in the Engine programming OpenBench testing instance for their support and 
contributions in testing my engine:
  - @cosmobobak, @uwuplant, @Adam-Kulju, @archishou, @Ciekce, @JouanDeag, 
@GediminasMasaitis, @crippa1337, @lucametehau, @spamdrew128 and @dede1751
