
<div align="center">
  
# Altair
  
  [![License][license-badge]][license-link]
  [![Release][release-badge]][release-link]
  [![Commits][commits-badge]][commits-link]


  Altair is a superhuman UCI-protocol chess engine named after the star Altair.

</div>


## Ratings

*Last Updated 11/24/23* \
(All rankings are based on single-CPU only for fairness of comparison)

[CCRL Rating List](http://ccrl.chessdom.com/ccrl/) \
[CEGT Rating List](http://www.cegt.net) \
[MCERL Rating list](https://www.chessengeria.com/mcerl)

|  Version  | CCRL Blitz 2+1 |  CCRL 40/15  | CCRL FRC 40/2 |  CEGT 40/4   |     MCERL     |
|:---------:|:--------------:|:------------:|:-------------:|:------------:|:-------------:|
|   1.0.0   |      ----      |     2405     |     ----      |     2206     |     ----      |
|   2.0.0   |      2880      |     2808     |     ----      |     2674     |     2657      |
|   3.0.0   |      3013      |     3002     |     ----      |     2874     |     ----      |
|   4.0.0   |      3083      |     3041     |     3079      |     2924     |     3098      |
| **5.0.0** |  #81 **3202**  | #81 **3132** | #42 **3214**  | #81 **3047** | #128 **3221** |


## Download
The release page provides different binaries. \
Altair can also be built from the source code with cmake, using the CMakeLists.txt, and make, using the makefile.

## Play
Altair can be played by connecting it to GUIs such as Arena, Cutechess, Banksia, and other UCI-protocol supporting 
chess GUIs.

You can also play against Altair on lichess [here](https://lichess.org/@/Altair_Engine), but it is not always online. 
Note: Lichess BOT ratings are deflated compared to their actual human relative strengths.

## Board Representation
Altair currently uses bitboards, binary representations of the chessboard, as the internal board representation as of version 4.0.1 \
Versions 4.0.0 and prior used a mailbox (12x10), array board representation

## Move Generation
Altair uses the magic bitboard approach for decently fast move generation speeds.

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
From Altair's creation to version 5.0.8, it primarily used a classical evaluation. \
Currently, from version 5.0.9 and onwards, it primarily uses NNUE (Efficiently Updatable Neural Networks) for its evaluation. \
The classical evaluation still exists in Altair currently, however it is not advised to use it.

### Neural Network Evaluation
Altair's nets are trained on completely original data. \
The data was originally trained from Altair's classical evaluation, which was specifically tuned from zero values from 5.0.0 and onwards. \
The current data has been repeatedly trained on previous data in a cycle of reinforcement learning of sorts.

#### Current Net:
Trained on over 800M FENs including mostly standard data and minimal DFRC data.

Architecture:
```
+--------+----------+--------+ 
| Input  | Hidden   | Output | 
| 768 -> | 768*2 -> |   1    | 
+--------+----------+--------+
```

*The `*2` in the Hidden Layer indicates perspective*

### Classical Evaluation

Altair's classical evaluation from versions 1.3.6 to 5.0.0 was tuned on public Zurichess data, Lichess data, and Ethereal data. \
From version 5.0.1 and onwards, Altair's classical evaluation was reset to zero values and re-tuned on self generated data.

These are some evaluation features present in Altair's classical evaluation (a more detailed list can be found in evaluation_constants.h):

- Tapered evaluation between the middle-game and end-game
- Material
- Piece Square Tables
- Mobility
- Pawn Structure
- King Safety
- Piece Threats
- Bishop Pair
- Tempo
- Endgame draw likelihood scaling

## Credit and Thanks
Altair was created with the help of many people and usage of many resources. 
Altair is also inspired from other strong and notable engines.

Altair uses [@jw1912's](https://github.com/jw1912) [Bullet](https://github.com/jw1912/bullet) for training neural networks as of version 5.0.9\
Altair's NNUE inference code is influenced by [@Ciekce's](https://github.com/Ciekce) [Polaris](https://github.com/Ciekce/Polaris/tree/viri_nnue) \
Altair uses Dale Weiler's INCBIN utility for including binary files

Since version 1.3.6 and beyond, Altair's classical evaluation has been tuned with [@GediminasMasaitis's](https://github.com/GediminasMasaitis) 
[Texel Tuner](https://github.com/GediminasMasaitis/texel-tuner/tree/main/src) for tuning HCE parameters.

Other Mentions:

- [The Chess Programming Wiki](https://www.chessprogramming.org/Main_Page) contains many resources that I have used.
- [The Bitboard Chess Engine in C Playlist](https://www.youtube.com/playlist?list=PLmN0neTso3Jxh8ZIylk74JpwfiWNI76Cs) is a great video series that I initially used to learn aspects of chess programming.
- [@archishou](https://github.com/archishou) has supported me a lot in the development of my engine with many ideas and help in implementing bitboards.
- [@Ciekce](https://github.com/Ciekce) has helped me not only fix many issues in my engine, but also improve my understanding of programming in general.
- [@GediminasMasaitis](https://github.com/GediminasMasaitis) has also helped me a lot in the development of my engine. His engine [Chessdotcpp](https://github.com/GediminasMasaitis/chess-dot-cpp) has inspired me with many ideas.
- [Weiss](https://github.com/TerjeKir/weiss) is another great inspiration and resource.
- The Engine Programming Discord Server for answering many of my questions.
- Everyone in this [OpenBench Testing Instance](https://chess.swehosting.se/users/) for their invaluable support and 
contributions in testing my engine.

Many people have helped me along the development of this chess engine. Without them, Altair would have never reached this stage.


[commits-badge]:https://img.shields.io/github/commits-since/Alex2262/AltairChessEngine/latest?style=for-the-badge
[commits-link]:https://github.com/Alex2262/AltairChessEngine/commits/master
[release-badge]:https://img.shields.io/github/v/release/Alex2262/AltairChessEngine?style=for-the-badge&label=official%20release
[release-link]:https://github.com/Alex2262/AltairChessEngine/releases/latest
[license-badge]:https://img.shields.io/github/license/Alex2262/AltairChessEngine?style=for-the-badge&label=license&color=success
[license-link]:https://github.com/Alex2262/AltairChessEngine/blob/master/LICENSE

