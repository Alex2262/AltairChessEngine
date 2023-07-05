# Altair

<div align="center">
  
  [![License][license-badge]][license-link]
  [![Release][release-badge]][release-link]
  [![Commits][commits-badge]][commits-link]
  
</div>

Altair is a strong UCI-protocol chess engine that succeeds my old python engine Antares.

## Ratings
[CCRL Rating List](http://ccrl.chessdom.com/ccrl/) \
[MCERL Rating list](https://www.chessengeria.com/mcerl)

| Version | CCRL Blitz | CCRL Rapid | MCERL |
|:-------:|:----------:|:----------:|:-----:|
|  1.0.0  |    ----    |    2409    | ----  |
|  2.0.0  |    2875    |    2808    | 2639  |
|  3.0.0  |    3010    |    3004    | ----  |


## Download
The release provides different binaries. \
Altair can also be built from the source code with cmake, using the CMakeLists.txt, and make, using the makefile.

## Play
Altair can be played by connecting it to GUIs such as Arena, Cutechess, Banksia, and other UCI-protocol supporting 
chess GUIs.

You can also play against Altair on lichess [here](https://lichess.org/@/Altair_Engine), but it is not always online. 
Note: Lichess BOT ratings are deflated compared to their actual human-relative-strength.

## Board Representation
Altair uses a 10x12 mailbox array. This board representation gives padding around the 8x8 board for faster move generation. Altair also features piece lists.

I hope to use bitboards instead in the future since they can be much faster if implemented well. The benefits of implementing bitboards would be a hundred elo gained in strength; however, it would require most of the engine to be rewritten.

## Move Generation
Offsets / Increments are used in loops to generate the pseudo-legal moves. Within the search and perft, the moves are tested for 
legality, and if the move is not legal, we skip to the next move.

## Search
Altair utilizes many techniques for its search—the calculation of moves and different positions. 
At the basis, Altair uses a version of minimax called negamax. On top of this, it uses the traditional alpha-beta pruning algorithm.

Furthermore, different methods of selection, pruning, and reductions enables
it to narrow down the amount of positions and moves it has to calculate.

A brief description of Altair's search layout:

- Iterative Deepening
- Aspiration Windows
- Negamax (Minimax)
  - Alpha-Beta Pruning
  - Different Search Enhancements
    - Transposition Tables
    - Pruning
    - Reductions
    - Extensions
- Quiescence Search
  - Different Search Enhancements
    - Stand-Pat
    - Transposition Tables
    - Pruning
  
#### Move Ordering
It is advantageous for a chess engine to look at the best moves first, so worse moves can be easily pruned and discarded.

Altair's Move Ordering is structured like so:

- Transposition Table Move
- Promotions
- Captures
  - Most Valuable Victim - Least Valuable Aggressor (MVV-LVA)
  - Capture History Heuristic
  - Static Exchange Evaluation (SEE)
  - En passant
- Killer move Heuristic
- Continuation History Heuristic
- History Heuristic
- Castling

## Evaluation
These are some of the evaluation features present in Altair:

- Material
- Piece Square Tables
- Mobility
  - Open and semi-open files for rooks and queens
- Pawn Structure
- King Safety
  - King Danger Zone
  - King Tropism
  - Pawn Shield
  - Pawn Storm
  - Open Files
- Piece Threats & Support
- Bishop Pair
- Tempo
- King Tropism (Distance from pieces to a King)
- Tapered evaluation between the middlegame and endgame
- Scaling based on the likeliness of a draw

## Credit and Thanks
Altair was created with the help of many people and usage of many resources. 
Altair is also inspired from other strong and notable engines.

Mentions:

- [The Chess Programming Wiki](https://www.chessprogramming.org/Main_Page) contains invaluable resources that I have used.
- [The Bitboard Chess Engine in C Playlist](https://www.youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs) is a nice video series that contains implementations for different ideas and features.
- [@archishou](https://github.com/archishou) has helped and supported me a lot in the development and improvement of my engine.
- [@GediminasMasaitis](https://github.com/GediminasMasaitis) has also helped me a lot in the development of my engine. His engine [Chessdotcpp](https://github.com/GediminasMasaitis/chess-dot-cpp) has inspired me with many ideas. Since version 1.3.6 and beyond, I have also used his [Texel Tuner](https://github.com/GediminasMasaitis/texel-tuner/tree/main/src) for tuning evaluation parameters.
- [Weiss](https://github.com/TerjeKir/weiss) is another great inspiration and resource.
- The Engine Programming Discord Server for answering many of my questions.
- Everyone in this [OpenBench Testing Instance](https://chess.swehosting.se/users/) for their support and 
contributions in testing my engine.

Many people have helped me along the development of this chess engine. Without them, Altair would have never reached this stage.


[commits-badge]:https://img.shields.io/github/commits-since/Alex2262/AltairChessEngine/latest?style=for-the-badge
[commits-link]:https://github.com/Alex2262/AltairChessEngine/commits/master
[release-badge]:https://img.shields.io/github/v/release/Alex2262/AltairChessEngine?style=for-the-badge&label=official%20release
[release-link]:https://github.com/Alex2262/AltairChessEngine/releases/latest
[license-badge]:https://img.shields.io/github/license/Alex2262/AltairChessEngine?style=for-the-badge&label=license&color=success
[license-link]:https://github.com/Alex2262/AltairChessEngine/blob/master/LICENSE
