# Changelog

### Bare a/b negamax with PST eval
```
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 127 nps 127000 pv b1c3 g8f6
info depth 3 score cp 58 time 3 nodes 1246 nps 415333 pv b1c3 g8f6 g1f3
info depth 4 score cp 0 time 6 nodes 8680 nps 1446666 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 55 time 41 nodes 184415 nps 4497926 pv e2e4 b8c6 f1b5 c6e5 b5d7
info depth 6 score cp -30 time 274 nodes 1326069 nps 4839667 pv b1c3 e7e5 e2e3 f8b4 c3d5 b4d2
info depth 7 score cp 98 time 3277 nodes 17673132 nps 5393082 pv e2e3 b8c6 b1c3 c6b4 f1c4 g8f6 c4f7
info depth 8 score cp -63 time 41540 nodes 213790795 nps 5146624 pv b1c3 b8c6 e2e3 e7e5 f1b5 f8b4 c3d5 b4d2
info depth 8 score cp -63 time 44999 nodes 231026698 nps 5134040 pv b1c3 b8c6 e2e3 e7e5 f1b5 f8b4 c3d5 b4d2
bestmove b1c3
```


### Qsearch + pre-allocating move vectors
```
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 2 nodes 157 nps 78500 pv b1c3 b8c6
info depth 3 score cp 58 time 4 nodes 2362 nps 590500 pv b1c3 g8f6 g1f3
info depth 4 score cp 0 time 7 nodes 14721 nps 2103000 pv g1f3 g8f6 b1c3 b8c6
info depth 5 score cp 41 time 35 nodes 157226 nps 4492171 pv b1c3 g8f6 g1f3 b8c6 d2d4
info depth 6 score cp 0 time 412 nodes 1765136 nps 4284310 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5
info depth 7 score cp 30 time 7861 nodes 31894942 nps 4057364 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 7 score cp 30 time 45000 nodes 146612255 nps 3258050 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
bestmove e2e4

Score of AntaresCpp0.01 vs AntaresCpp0.00: 54 - 5 - 41 [0.745]
...      AntaresCpp0.01 playing White: 23 - 1 - 26  [0.720] 50
...      AntaresCpp0.01 playing Black: 31 - 4 - 15  [0.770] 50
...      White vs Black: 27 - 32 - 41  [0.475] 100
Elo difference: 186.2 +/- 53.7, LOS: 100.0 %, DrawRatio: 41.0 %

Score of AntaresCpp0.01 vs SebLagueEngine0.1: 6 - 18 - 5 [0.293]
...      AntaresCpp0.01 playing White: 3 - 9 - 3  [0.300] 15
...      AntaresCpp0.01 playing Black: 3 - 9 - 2  [0.286] 14
...      White vs Black: 12 - 12 - 5  [0.500] 29
Elo difference: -152.9 +/- 132.7, LOS: 0.7 %, DrawRatio: 17.2 %
```


### In check extensions
```
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 157 nps 157000 pv b1c3 b8c6
info depth 3 score cp 58 time 2 nodes 2362 nps 1181000 pv b1c3 g8f6 g1f3
info depth 4 score cp 0 time 5 nodes 14756 nps 2951200 pv g1f3 g8f6 b1c3 b8c6
info depth 5 score cp 41 time 32 nodes 150351 nps 4698468 pv b1c3 g8f6 g1f3 b8c6 d2d4
info depth 6 score cp 0 time 510 nodes 2111693 nps 4140574 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6
info depth 7 score cp 30 time 4875 nodes 21066927 nps 4321420 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 7 score cp 30 time 44999 nodes 171016216 nps 3800444 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
bestmove e2e4

Score of AntaresCpp0.02 vs AntaresCpp0.01: 21 - 20 - 59 [0.505]
...      AntaresCpp0.02 playing White: 16 - 5 - 29  [0.610] 50
...      AntaresCpp0.02 playing Black: 5 - 15 - 30  [0.400] 50
...      White vs Black: 31 - 10 - 59  [0.605] 100
Elo difference: 3.5 +/- 43.8, LOS: 56.2 %, DrawRatio: 59.0 %

Score of AntaresCpp0.02 vs SebLagueEngine0.1: 15 - 103 - 32 [0.207]
...      AntaresCpp0.02 playing White: 7 - 50 - 18  [0.213] 75
...      AntaresCpp0.02 playing Black: 8 - 53 - 14  [0.200] 75
...      White vs Black: 60 - 58 - 32  [0.507] 150
Elo difference: -233.7 +/- 57.4, LOS: 0.0 %, DrawRatio: 21.3 %
```


### Negamax Move Ordering
```
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 157 nps 157000 pv b1c3 b8c6
info depth 3 score cp 58 time 3 nodes 2176 nps 725333 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 7 nodes 13851 nps 1978714 pv g1f3 b8c6 b1c3 g8f6
info depth 5 score cp 41 time 24 nodes 91403 nps 3808458 pv g1f3 b8c6 d2d4 g8f6 b1c3
info depth 6 score cp 0 time 267 nodes 1000631 nps 3747681 pv g1f3 g8f6 d2d4 d7d5 b1c3 b8c6
info depth 7 score cp 30 time 2067 nodes 7725204 nps 3737399 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 8 score cp 0 time 17696 nodes 61743103 nps 3489099 pv g1f3 g8f6 e2e3 b8c6 b1c3 d7d6 d2d4 e7e5
info depth 8 score cp 0 time 45000 nodes 156903437 nps 3486743 pv g1f3 g8f6 e2e3 b8c6 b1c3 d7d6 d2d4 e7e5
bestmove g1f3

Score of AntaresCpp0.03 vs AntaresCpp0.02: 80 - 9 - 62 [0.735]
...      AntaresCpp0.03 playing White: 45 - 3 - 28  [0.776] 76
...      AntaresCpp0.03 playing Black: 35 - 6 - 34  [0.693] 75
...      White vs Black: 51 - 38 - 62  [0.543] 151
Elo difference: 177.3 +/- 43.5, LOS: 100.0 %, DrawRatio: 41.1 %

Score of AntaresCpp0.03 vs SebLagueEngine0.1: 34 - 30 - 36 [0.520]
...      AntaresCpp0.03 playing White: 18 - 13 - 19  [0.550] 50
...      AntaresCpp0.03 playing Black: 16 - 17 - 17  [0.490] 50
...      White vs Black: 35 - 29 - 36  [0.530] 100
Elo difference: 13.9 +/- 54.9, LOS: 69.1 %, DrawRatio: 36.0 %
```


### Quiescence Search Move Ordering
```
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 157 nps 157000 pv b1c3 b8c6
info depth 3 score cp 58 time 2 nodes 2176 nps 1088000 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 6 nodes 15135 nps 2522500 pv g1f3 g8f6 b1c3 b8c6
info depth 5 score cp 41 time 20 nodes 78230 nps 3911500 pv g1f3 b8c6 d2d4 g8f6 b1c3
info depth 6 score cp 0 time 167 nodes 607033 nps 3634928 pv g1f3 d7d5 b1c3 b8c6 e2e4 g8f6
info depth 7 score cp 30 time 2349 nodes 9543601 nps 4062835 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 8 score cp 0 time 19282 nodes 71098146 nps 3687280 pv d2d4 g8f6 e2e3 d7d5 b1c3 b8c6 g1f3 c8f5
info depth 8 score cp 0 time 44999 nodes 152193051 nps 3382142 pv d2d4 g8f6 e2e3 d7d5 b1c3 b8c6 g1f3 c8f5
bestmove d2d4

Score of AntaresCpp0.04 vs AntaresCpp0.03: 60 - 35 - 105 [0.563]
...      AntaresCpp0.04 playing White: 32 - 16 - 52  [0.580] 100
...      AntaresCpp0.04 playing Black: 28 - 19 - 53  [0.545] 100
...      White vs Black: 51 - 44 - 105  [0.517] 200
Elo difference: 43.7 +/- 33.2, LOS: 99.5 %, DrawRatio: 52.5 %

Score of AntaresCpp0.04 vs SebLagueEngine0.1: 60 - 29 - 61 [0.603]
...      AntaresCpp0.04 playing White: 25 - 16 - 34  [0.560] 75
...      AntaresCpp0.04 playing Black: 35 - 13 - 27  [0.647] 75
...      White vs Black: 38 - 51 - 61  [0.457] 150
Elo difference: 72.9 +/- 43.3, LOS: 99.9 %, DrawRatio: 40.7 %
```


### Killer move ordering
```
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 2 nodes 157 nps 78500 pv b1c3 b8c6
info depth 3 score cp 58 time 4 nodes 975 nps 243750 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 6 nodes 3446 nps 574333 pv g1f3 b8c6 b1c3 g8f6
info depth 5 score cp 41 time 12 nodes 23106 nps 1925500 pv g1f3 b8c6 b1c3 g8f6 e2e4
info depth 6 score cp 0 time 52 nodes 155748 nps 2995153 pv e2e4 b8c6 b1c3 g8f6 g1f3 e7e5
info depth 7 score cp 30 time 233 nodes 837200 nps 3593133 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 8 score cp 0 time 2009 nodes 6416736 nps 3193995 pv b1c3 b8c6 g1f3 g8f6 e2e3 d7d6 d2d4 e7e5
info depth 9 score cp 27 time 11604 nodes 38981072 nps 3359278 pv e2e4 e7e5 f1c4 b8c6 g1e2 g8f6 b1c3 f8c5 e1g1
info depth 9 score cp 27 time 44999 nodes 144943108 nps 3221029 pv e2e4 e7e5 f1c4 b8c6 g1e2 g8f6 b1c3 f8c5 e1g1
bestmove e2e4

Score of AntaresCpp0.05 vs AntaresCpp0.04: 41 - 22 - 87 [0.563]
...      AntaresCpp0.05 playing White: 28 - 11 - 36  [0.613] 75
...      AntaresCpp0.05 playing Black: 13 - 11 - 51  [0.513] 75
...      White vs Black: 39 - 24 - 87  [0.550] 150
Elo difference: 44.2 +/- 36.0, LOS: 99.2 %, DrawRatio: 58.0 %
150 of 150 games finished.

Score of AntaresCpp0.05 vs SebLagueEngine0.1: 45 - 6 - 49 [0.695]
...      AntaresCpp0.05 playing White: 22 - 6 - 22  [0.660] 50
...      AntaresCpp0.05 playing Black: 23 - 0 - 27  [0.730] 50
...      White vs Black: 22 - 29 - 49  [0.465] 100
Elo difference: 143.1 +/- 48.4, LOS: 100.0 %, DrawRatio: 49.0 %
100 of 100 games finished.

Score of AntaresCpp0.05 vs Lynx0.11.0: 65 - 9 - 26 [0.780]
...      AntaresCpp0.05 playing White: 31 - 4 - 15  [0.770] 50
...      AntaresCpp0.05 playing Black: 34 - 5 - 11  [0.790] 50
...      White vs Black: 36 - 38 - 26  [0.490] 100
Elo difference: 219.9 +/- 66.2, LOS: 100.0 %, DrawRatio: 26.0 %
100 of 100 games finished.

Score of AntaresCpp0.05 vs Vice1.0: 11 - 65 - 24 [0.230]
...      AntaresCpp0.05 playing White: 4 - 31 - 15  [0.230] 50
...      AntaresCpp0.05 playing Black: 7 - 34 - 9  [0.230] 50
...      White vs Black: 38 - 38 - 24  [0.500] 100
Elo difference: -209.9 +/- 67.2, LOS: 0.0 %, DrawRatio: 24.0 %
100 of 100 games finished.

Rank Name               Elo    +/-  Games   Wins Losses  Draws  Points  WWins  WLoss. WDraws  BWins BLoss. BDraws
1 AntaresCpp0.05     230     49    145     90      6     49   114.5     47      3     22     43      3     27
2 AntaresCpp0.04     191     46    144     80      8     56   108.0     44      3     25     36      5     31
3 AntaresCpp0.03     134     47    144     72     19     53    98.5     34      7     31     38     12     22
4 AntaresCpp0.02     -34     46    145     41     55     49    65.5     20     29     24     21     26     25
5 AntaresCpp0.01     -46     45    145     35     54     56    63.0     19     23     31     16     31     25
6 AntaresCpp0.00    -201     54    144     16     91     37    34.5      8     47     17      8     44     20
7 AntaresOld0.2     -299     68    145     11    112     22    22.0      7     54     11      4     58     11

510 of 2100 games finished.
```


### History move heuristic move ordering
```
info depth 1 score cp 58 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 157 nps 157000 pv b1c3 b8c6
info depth 3 score cp 58 time 2 nodes 962 nps 481000 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 4 nodes 2824 nps 706000 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 41 time 7 nodes 17829 nps 2547000 pv b1c3 b8c6 g1f3 g8f6 d2d4
info depth 6 score cp 0 time 41 nodes 116572 nps 2843219 pv g1f3 b8c6 b1c3 g8f6 d2d4 d7d5
info depth 7 score cp 30 time 198 nodes 728612 nps 3679858 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6e4 b1c3
info depth 8 score cp 0 time 1426 nodes 4080248 nps 2861323 pv d2d4 g8f6 g1f3 d7d5 b1c3 b8c6 e2e3 e7e6
info depth 9 score cp 27 time 8181 nodes 27702922 nps 3386251 pv e2e4 e7e5 f1c4 g8f6 b1c3 b8c6 g1e2 f8b4 e1g1
info depth 9 score cp 27 time 44999 nodes 134451211 nps 2987871 pv e2e4 e7e5 f1c4 g8f6 b1c3 b8c6 g1e2 f8b4 e1g1
bestmove e2e4

Score of AntaresCpp0.06 vs AntaresCpp0.05: 39 - 25 - 136 [0.535]
...      AntaresCpp0.06 playing White: 20 - 13 - 67  [0.535] 100
...      AntaresCpp0.06 playing Black: 19 - 12 - 69  [0.535] 100
...      White vs Black: 32 - 32 - 136  [0.500] 200
Elo difference: 24.4 +/- 27.2, LOS: 96.0 %, DrawRatio: 68.0 %
200 of 200 games finished.

Score of AntaresCpp0.06 vs Vice1.0: 15 - 89 - 46 [0.253]
...      AntaresCpp0.06 playing White: 9 - 48 - 18  [0.240] 75
...      AntaresCpp0.06 playing Black: 6 - 41 - 28  [0.267] 75
...      White vs Black: 50 - 54 - 46  [0.487] 150
Elo difference: -187.8 +/- 49.8, LOS: 0.0 %, DrawRatio: 30.7 %
150 of 150 games finished.

Score of AntaresCpp0.06 vs Lynx0.11.0: 70 - 9 - 21 [0.805]
...      AntaresCpp0.06 playing White: 35 - 4 - 11  [0.810] 50
...      AntaresCpp0.06 playing Black: 35 - 5 - 10  [0.800] 50
...      White vs Black: 40 - 39 - 21  [0.505] 100
Elo difference: 246.3 +/- 72.1, LOS: 100.0 %, DrawRatio: 21.0 %
100 of 100 games finished.

LYNX VS SEB_LAGUE_ENGINE COMPARISON

Score of Lynx0.11.0 vs SebLagueEngine: 41 - 48 - 11 [0.465]
...      Lynx0.11.0 playing White: 18 - 26 - 6  [0.420] 50
...      Lynx0.11.0 playing Black: 23 - 22 - 5  [0.510] 50
...      White vs Black: 40 - 49 - 11  [0.455] 100
Elo difference: -24.4 +/- 65.0, LOS: 22.9 %, DrawRatio: 11.0 %
100 of 100 games finished.
```


### Use AntaresPy pre-pawn-eval PSTs and Piece values.
```
info depth 1 score cp 50 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 176 nps 176000 pv b1c3 b8c6
info depth 3 score cp 50 time 3 nodes 1066 nps 355333 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 5 nodes 2842 nps 568400 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 43 time 11 nodes 18121 nps 1647363 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 0 time 39 nodes 93584 nps 2399589 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6
info depth 7 score cp 30 time 163 nodes 611075 nps 3748926 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 10 time 1426 nodes 4114859 nps 2885595 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6 f3e5 c6e5
info depth 9 score cp 30 time 10265 nodes 33032398 nps 3217963 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
info depth 9 score cp 30 time 45000 nodes 124993571 nps 2777634 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
bestmove e2e4

Score of AntaresCpp0.07 vs AntaresCpp0.06: 47 - 37 - 116 [0.525]
...      AntaresCpp0.07 playing White: 25 - 17 - 58  [0.540] 100
...      AntaresCpp0.07 playing Black: 22 - 20 - 58  [0.510] 100
...      White vs Black: 45 - 39 - 116  [0.515] 200
Elo difference: 17.4 +/- 31.2, LOS: 86.2 %, DrawRatio: 58.0 %
200 of 200 games finished.

Score of AntaresCpp0.07 vs Vice1.0: 20 - 100 - 80 [0.300]
...      AntaresCpp0.07 playing White: 10 - 55 - 35  [0.275] 100
...      AntaresCpp0.07 playing Black: 10 - 45 - 45  [0.325] 100
...      White vs Black: 55 - 65 - 80  [0.475] 200
Elo difference: -147.2 +/- 38.2, LOS: 0.0 %, DrawRatio: 40.0 %
200 of 200 games finished.

Score of AntaresCpp0.07 vs Lynx0.11.0: 62 - 9 - 29 [0.765]
...      AntaresCpp0.07 playing White: 30 - 8 - 12  [0.720] 50
...      AntaresCpp0.07 playing Black: 32 - 1 - 17  [0.810] 50
...      White vs Black: 31 - 40 - 29  [0.455] 100
Elo difference: 205.0 +/- 63.2, LOS: 100.0 %, DrawRatio: 29.0 %
100 of 100 games finished.
```


### Tapered Eval
```
info depth 1 score cp 50 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 0 time 1 nodes 176 nps 176000 pv b1c3 b8c6
info depth 3 score cp 50 time 3 nodes 1066 nps 355333 pv b1c3 b8c6 g1f3
info depth 4 score cp 0 time 5 nodes 2840 nps 568000 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 43 time 9 nodes 18066 nps 2007333 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 0 time 38 nodes 94817 nps 2495184 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6
info depth 7 score cp 30 time 177 nodes 618287 nps 3493146 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 10 time 1426 nodes 4177444 nps 2929483 pv d2d4 d7d5 b1c3 b8c6 g1f3 g8f6 f3e5 c6e5
info depth 9 score cp 30 time 10263 nodes 33158085 nps 3230837 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
info depth 9 score cp 30 time 44999 nodes 122472481 nps 2721671 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
bestmove e2e4

Score of AntaresCpp0.08 vs AntaresCpp0.07: 46 - 30 - 124 [0.540]
...      AntaresCpp0.08 playing White: 25 - 11 - 64  [0.570] 100
...      AntaresCpp0.08 playing Black: 21 - 19 - 60  [0.510] 100
...      White vs Black: 44 - 32 - 124  [0.530] 200
Elo difference: 27.9 +/- 29.7, LOS: 96.7 %, DrawRatio: 62.0 %
200 of 200 games finished.

Score of AntaresCpp0.08 vs Vice1.0: 13 - 44 - 43 [0.345]
...      AntaresCpp0.08 playing White: 10 - 20 - 20  [0.400] 50
...      AntaresCpp0.08 playing Black: 3 - 24 - 23  [0.290] 50
...      White vs Black: 34 - 23 - 43  [0.555] 100
Elo difference: -111.4 +/- 52.3, LOS: 0.0 %, DrawRatio: 43.0 %
100 of 100 games finished.

Score of AntaresCpp0.08 vs Lynx0.11.0: 109 - 11 - 30 [0.827]
...      AntaresCpp0.08 playing White: 52 - 7 - 16  [0.800] 75
...      AntaresCpp0.08 playing Black: 57 - 4 - 14  [0.853] 75
...      White vs Black: 56 - 64 - 30  [0.473] 150
Elo difference: 271.4 +/- 60.5, LOS: 100.0 %, DrawRatio: 20.0 %
150 of 150 games finished.
```


### Tempo Bonus
```
info depth 1 score cp 42 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 8 time 1 nodes 176 nps 176000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 1066 nps 355333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 5 nodes 2832 nps 566400 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 35 time 11 nodes 18020 nps 1638181 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 43 nodes 92183 nps 2143790 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6
info depth 7 score cp 22 time 182 nodes 612118 nps 3363285 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 9 time 1562 nodes 4230256 nps 2708230 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6g4 d2d4 d7d5
info depth 9 score cp 22 time 8776 nodes 28278151 nps 3222214 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
info depth 9 score cp 22 time 45001 nodes 131461161 nps 2921294 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
bestmove e2e4

Score of AntaresCpp0.09 vs AntaresCpp0.08: 34 - 32 - 134 [0.505]
...      AntaresCpp0.09 playing White: 16 - 14 - 70  [0.510] 100
...      AntaresCpp0.09 playing Black: 18 - 18 - 64  [0.500] 100
...      White vs Black: 34 - 32 - 134  [0.505] 200
Elo difference: 3.5 +/- 27.7, LOS: 59.7 %, DrawRatio: 67.0 %
200 of 200 games finished.
```


### Zobrist Hashing, Repetition Detection, 50 move rule.
```
info depth 1 score cp 42 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 8 time 1 nodes 176 nps 176000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 1066 nps 355333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 5 nodes 2832 nps 566400 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 35 time 9 nodes 18020 nps 2002222 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 38 nodes 92182 nps 2425842 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6
info depth 7 score cp 22 time 173 nodes 612115 nps 3538236 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 9 time 1462 nodes 4230163 nps 2893408 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6g4 d2d4 d7d5
info depth 9 score cp 22 time 9126 nodes 27840921 nps 3050725 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
info depth 9 score cp 22 time 45144 nodes 116811778 nps 2587537 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
bestmove e2e4

Score of AntaresCpp0.10 vs AntaresCpp0.09: 61 - 32 - 107 [0.573]
...      AntaresCpp0.10 playing White: 29 - 18 - 53  [0.555] 100
...      AntaresCpp0.10 playing Black: 32 - 14 - 54  [0.590] 100
...      White vs Black: 43 - 50 - 107  [0.482] 200
Elo difference: 50.7 +/- 32.8, LOS: 99.9 %, DrawRatio: 53.5 %
200 of 200 games finished.

Score of AntaresCpp0.10 vs Vice1.0: 56 - 74 - 20 [0.440]
...      AntaresCpp0.10 playing White: 28 - 34 - 13  [0.460] 75
...      AntaresCpp0.10 playing Black: 28 - 40 - 7  [0.420] 75
...      White vs Black: 68 - 62 - 20  [0.520] 150
Elo difference: -41.9 +/- 52.4, LOS: 5.7 %, DrawRatio: 13.3 %
150 of 150 games finished.
```



### Transposition table returning scores
```
info depth 1 score cp 42 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 8 time 1 nodes 176 nps 176000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 1066 nps 355333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 2742 nps 685500 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 35 time 8 nodes 14037 nps 1754625 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 30 nodes 61955 nps 2065166 pv d2d4 g8f6 g1f3 d7d5 b1c3 b8c6
info depth 7 score cp 22 time 151 nodes 377331 nps 2498880 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 9 time 717 nodes 1919527 nps 2677164 pv e2e4 b8c6 g1f3 g8f6
info depth 9 score cp 22 time 4626 nodes 13883841 nps 3001262 pv e2e4 b8c6 d2d4 d7d5 e4d5
info depth 9 score cp 22 time 45000 nodes 113160192 nps 2514670 pv e2e4 b8c6 d2d4 d7d5 e4d5
bestmove e2e4

Score of AntaresCpp0.11 vs AntaresCpp0.10: 97 - 52 - 51 [0.613]
...      AntaresCpp0.11 playing White: 40 - 28 - 32  [0.560] 100
...      AntaresCpp0.11 playing Black: 57 - 24 - 19  [0.665] 100
...      White vs Black: 64 - 85 - 51  [0.448] 200
Elo difference: 79.5 +/- 42.4, LOS: 100.0 %, DrawRatio: 25.5 %
200 of 200 games finished.

Score of AntaresCpp0.11 vs Vice1.0: 73 - 92 - 35 [0.453]
...      AntaresCpp0.11 playing White: 37 - 49 - 14  [0.440] 100
...      AntaresCpp0.11 playing Black: 36 - 43 - 21  [0.465] 100
...      White vs Black: 80 - 85 - 35  [0.487] 200
Elo difference: -33.1 +/- 44.1, LOS: 7.0 %, DrawRatio: 17.5 %
200 of 200 games finished.
```


### TT Move ordering
```
info depth 1 score cp 42 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 8 time 3 nodes 81 nps 27000 pv b1c3 b8c6
info depth 3 score cp 42 time 4 nodes 616 nps 154000 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 5 nodes 2242 nps 448400 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 35 time 8 nodes 11901 nps 1487625 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 22 nodes 47004 nps 2136545 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 70 nodes 222108 nps 3172971 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 9 time 440 nodes 1263916 nps 2872536 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6g4 d2d4 d7d5
info depth 9 score cp 22 time 2762 nodes 9076317 nps 3286139 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
info depth 9 score cp 22 time 44999 nodes 123766784 nps 2750434 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
bestmove e2e4

5s + 0.05
Score of AntaresCpp0.12 vs AntaresCpp0.11: 103 - 47 - 49 [0.641]
...      AntaresCpp0.12 playing White: 46 - 28 - 26  [0.590] 100
...      AntaresCpp0.12 playing Black: 57 - 19 - 23  [0.692] 99
...      White vs Black: 65 - 85 - 49  [0.450] 199
Elo difference: 100.5 +/- 43.3, LOS: 100.0 %, DrawRatio: 24.6 %
199 of 200 games finished.

Score of AntaresCpp0.12 vs Vice1.0: 93 - 37 - 20 [0.687]
...      AntaresCpp0.12 playing White: 43 - 21 - 11  [0.647] 75
...      AntaresCpp0.12 playing Black: 50 - 16 - 9  [0.727] 75
...      White vs Black: 59 - 71 - 20  [0.460] 150
Elo difference: 136.3 +/- 55.7, LOS: 100.0 %, DrawRatio: 13.3 %
150 of 150 games finished.

Score of AntaresCpp0.12 vs GOOB1.0.0: 94 - 41 - 15 [0.677]
...      AntaresCpp0.12 playing White: 52 - 17 - 6  [0.733] 75
...      AntaresCpp0.12 playing Black: 42 - 24 - 9  [0.620] 75
...      White vs Black: 76 - 59 - 15  [0.557] 150
Elo difference: 128.3 +/- 56.5, LOS: 100.0 %, DrawRatio: 10.0 %
150 of 150 games finished.

30s + 0.00
Score of AntaresCpp0.12 vs Vice1.0: 25 - 26 - 10 [0.492]
...      AntaresCpp0.12 playing White: 15 - 12 - 4  [0.548] 31
...      AntaresCpp0.12 playing Black: 10 - 14 - 6  [0.433] 30
...      White vs Black: 29 - 22 - 10  [0.557] 61
Elo difference: -5.7 +/- 81.1, LOS: 44.4 %, DrawRatio: 16.4 %
```


### Adaptive NMP

```
info depth 1 score cp 42 time 0 nodes 21 nps 210000 pv b1c3
info depth 2 score cp 8 time 2 nodes 81 nps 40500 pv b1c3 b8c6
info depth 3 score cp 42 time 4 nodes 616 nps 154000 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 6 nodes 1933 nps 322166 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 35 time 10 nodes 10303 nps 1030300 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 17 nodes 26761 nps 1574176 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 41 nodes 120447 nps 2937731 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 9 time 115 nodes 364831 nps 3172443 pv e2e4 b8c6 g1f3 g8f6
info depth 9 score cp 22 time 357 nodes 1202886 nps 3369428 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
info depth 10 score cp 18 time 1030 nodes 3264847 nps 3169754 pv e2e4 b8c6 d2d4 e7e6 g1f3 g8f6 b1d2 d7d5 e4e5 f6e4
info depth 11 score cp 30 time 85715 nodes 247363046 nps 2885878 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6 f1b5
info depth 11 score cp 30 time 89999 nodes 259332104 nps 2881499 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6 f1b5
bestmove e2e4

Score of Altair0.13 vs AntaresCpp0.12: 110 - 46 - 44 [0.660]
...      Altair0.13 playing White: 62 - 16 - 22  [0.730] 100
...      Altair0.13 playing Black: 48 - 30 - 22  [0.590] 100
...      White vs Black: 92 - 64 - 44  [0.570] 200
Elo difference: 115.2 +/- 44.4, LOS: 100.0 %, DrawRatio: 22.0 %
200 of 200 games finished.
```


### Principle Variation Search for Negamax

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 628 nps 209333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 5 nodes 1972 nps 394400 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 35 time 7 nodes 10194 nps 1456285 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 13 nodes 25937 nps 1995153 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 35 nodes 110690 nps 3162571 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 9 time 104 nodes 341541 nps 3284048 pv e2e4 b8c6 g1f3 g8f6 e4e5 f6g4 d2d4 d7d5
info depth 9 score cp 22 time 299 nodes 1036567 nps 3466779 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1e2 g8f6 b1c3
info depth 10 score cp 18 time 832 nodes 2717039 nps 3265671 pv e2e4 b8c6 d2d4 e7e6 g1f3 g8f6 b1d2 d7d5 e4e5 f6e4
info depth 11 score cp 30 time 2873 nodes 9105569 nps 3169359 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6 f1b5 f8b4 d2d3 c6d4 f3d4

info depth 11 score cp 30 time 45000 nodes 121378825 nps 2697307 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6 f1b5 f8b4 d2d3 c6d4 
f3d4
bestmove e2e4

Score of Altair0.14 vs Altair0.13: 80 - 56 - 64 [0.560]
...      Altair0.14 playing White: 40 - 24 - 36  [0.580] 100
...      Altair0.14 playing Black: 40 - 32 - 28  [0.540] 100
...      White vs Black: 72 - 64 - 64  [0.520] 200
Elo difference: 41.9 +/- 40.0, LOS: 98.0 %, DrawRatio: 32.0 %
200 of 200 games finished.
```


### Late Move Reductions

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 2 nodes 86 nps 43000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 266 nps 88666 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 1155 nps 288750 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 35 time 6 nodes 2604 nps 434000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 8 nodes 6926 nps 865750 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 13 nodes 15318 nps 1178307 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 8 time 36 nodes 71360 nps 1982222 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3 e7e6
info depth 9 score cp 17 time 50 nodes 102854 nps 2057080 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 f1b5
info depth 10 score cp 21 time 217 nodes 536772 nps 2473603 pv e2e4 b8c6 g1f3 g8f6 b1c3
info depth 11 score cp 22 time 306 nodes 756555 nps 2472401 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 d2d4 g8f6 c1g5
info depth 12 score cp 23 time 489 nodes 1226830 nps 2508854 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6 d2d4 e5d4 f3d4 f8b4 d4c6 
b7c6
info depth 13 score cp 22 time 990 nodes 2462313 nps 2487184 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4 g8f6 c1g5 
f8e7 e4f6
info depth 14 score cp 22 time 2026 nodes 5150694 nps 2542297 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4 g8f6 c1g5
f8e7 g5f6 e7f6
info depth 14 score cp 22 time 45000 nodes 102752294 nps 2283384 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4 g8f6 
c1g5 f8e7 g5f6 e7f6
bestmove e2e4

Score of Altair0.15 vs Altair0.14: 75 - 62 - 63 [0.532]
...      Altair0.15 playing White: 44 - 28 - 28  [0.580] 100
...      Altair0.15 playing Black: 31 - 34 - 35  [0.485] 100
...      White vs Black: 78 - 59 - 63  [0.547] 200
Elo difference: 22.6 +/- 40.0, LOS: 86.7 %, DrawRatio: 31.5 %
200 of 200 games finished.
```


### Pawn Eval -- Passed, Backwards, Doubled, Isolated, PST changes

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 266 nps 88666 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 1144 nps 286000 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 6 nodes 2504 nps 417333 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 10 nodes 8352 nps 835200 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 15 nodes 16496 nps 1099733 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 20 time 34 nodes 49177 nps 1446382 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6g4
info depth 9 score cp 20 time 66 nodes 108143 nps 1638530 pv b1c3 b8c6 g1f3 d7d5 e2e4 d5e4 c3e4 g8f6 f3g5
info depth 10 score cp 14 time 284 nodes 507831 nps 1788137 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 f1b5
info depth 11 score cp 14 time 370 nodes 666042 nps 1800113 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 f1b5 f8b4 a2a3 b4c3 d2c3
info depth 12 score cp 18 time 798 nodes 1463427 nps 1833868 pv e2e4 e7e5 b1c3 g8f6 g1f3 f8b4 f3e5 d7d6 e5d3 b4c3 d2c3 f
6e4
info depth 13 score cp 28 time 1448 nodes 2635943 nps 1820402 pv e2e4 e7e5 b1c3 g8f6 g1f3 f8b4 f3e5 d7d6 e5d3 b4c3 d2c3
f6e4 c1f4
info depth 14 score cp 25 time 2610 nodes 4809645 nps 1842775 pv e2e4 e7e5 b1c3 g8f6 g1f3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3
d8e7 e1g1 b4c3
info depth 14 score cp 25 time 45001 nodes 76933131 nps 1709587 pv e2e4 e7e5 b1c3 g8f6 g1f3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d
3 d8e7 e1g1 b4c3
bestmove e2e4

Score of Altair0.16 vs Altair0.15: 128 - 231 - 141 [0.397]
...      Altair0.16 playing White: 61 - 129 - 60  [0.364] 250
...      Altair0.16 playing Black: 67 - 102 - 81  [0.430] 250
...      White vs Black: 163 - 196 - 141  [0.467] 500
Elo difference: -72.6 +/- 26.2, LOS: 0.0 %, DrawRatio: 28.2 %
500 of 500 games finished.
```


### Quiescence Search TT

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 2 nodes 265 nps 132500 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 1126 nps 281500 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 6 nodes 2448 nps 408000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 10 nodes 8087 nps 808700 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 14 nodes 15064 nps 1076000 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 20 time 33 nodes 46749 nps 1416636 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6g4
info depth 9 score cp 20 time 72 nodes 114587 nps 1591486 pv b1c3 b8c6 g1f3 d7d5 e2e4 d5e4 c3e4 g8f6 f3g5
info depth 10 score cp 14 time 292 nodes 501070 nps 1715993 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 f1b5
info depth 11 score cp 14 time 388 nodes 671563 nps 1730832 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 f1b5 f8b4 a2a3 b4c3 d2c3
info depth 12 score cp 18 time 643 nodes 1119329 nps 1740791 pv e2e4 e7e5 b1c3 g8f6 g1f3 f8b4 f3e5 d7d6 e5d3 b4c3 d2c3 f
6e4
info depth 13 score cp 28 time 1197 nodes 2081335 nps 1738792 pv e2e4 e7e5 b1c3 g8f6 g1f3 f8b4 f3e5 d7d6 e5d3 b4c3 d2c3
f6e4 c1f4
info depth 14 score cp 14 time 3958 nodes 6811612 nps 1720973 pv e2e4 e7e5 g1e2 g8f6 d2d4 e5d4 e4e5 f6g4 d1d4 d7d6 e5d6

info depth 14 score cp 14 time 45000 nodes 72984686 nps 1621881 pv e2e4 e7e5 g1e2 g8f6 d2d4 e5d4 e4e5 f6g4 d1d4 d7d6 e5d
6
bestmove e2e4

Score of Altair0.17 vs Altair0.16: 75 - 39 - 84 [0.591]
...      Altair0.17 playing White: 41 - 17 - 41  [0.621] 99
...      Altair0.17 playing Black: 34 - 22 - 43  [0.561] 99
...      White vs Black: 63 - 51 - 84  [0.530] 198
Elo difference: 63.9 +/- 37.0, LOS: 100.0 %, DrawRatio: 42.4 %
198 of 200 games finished.
```


### Qsearch Delta Pruning

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 2 nodes 86 nps 43000 pv b1c3 b8c6
info depth 3 score cp 42 time 4 nodes 265 nps 66250 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 5 nodes 1113 nps 222600 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 7 nodes 2413 nps 344714 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 11 nodes 8052 nps 732000 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 15 nodes 14976 nps 998400 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 20 time 34 nodes 44738 nps 1315823 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6g4
info depth 9 score cp 23 time 64 nodes 96970 nps 1515156 pv b1c3 b8c6 e2e4 g8f6 g1f3 d7d5
info depth 10 score cp 36 time 228 nodes 381334 nps 1672517 pv e2e4 b8c6 g1f3 g8f6 b1c3
info depth 11 score cp 37 time 507 nodes 872782 nps 1721463 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5f3 f6e4 d2d3 e4c5 b1c3
info depth 12 score cp 21 time 813 nodes 1395961 nps 1717049 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d1e2 c6d4 f3d4 e
5d4
info depth 13 score cp 25 time 1259 nodes 2164309 nps 1719069 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d2d3 d8e7 e1g1
e8g8 c1d2
info depth 14 score cp 10 time 3173 nodes 5403821 nps 1703063 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d1e2 d8e7 e1g1
e8g8 a2a3 b4c5
info depth 14 score cp 10 time 45000 nodes 69988393 nps 1555297 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d1e2 d8e7 e1g
1 e8g8 a2a3 b4c5
bestmove e2e4

Score of Altair0.18 vs Altair0.17: 98 - 82 - 120 [0.527]
...      Altair0.18 playing White: 52 - 43 - 55  [0.530] 150
...      Altair0.18 playing Black: 46 - 39 - 65  [0.523] 150
...      White vs Black: 91 - 89 - 120  [0.503] 300
Elo difference: 18.5 +/- 30.5, LOS: 88.3 %, DrawRatio: 40.0 %
300 of 300 games finished.
```


### LMR changes based on Weiss

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 262 nps 87333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 844 nps 211000 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 6 nodes 1807 nps 301166 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 8 nodes 3941 nps 492625 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 11 nodes 8069 nps 733545 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 8 time 20 nodes 22555 nps 1127750 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6
info depth 9 score cp 23 time 40 nodes 53892 nps 1347300 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4
info depth 10 score cp 14 time 123 nodes 192178 nps 1562422 pv b1c3 g8f6 e2e4 b8c6 g1f3 e7e5 f1b5 f8b4 a2a3 b4c3
info depth 11 score cp 14 time 178 nodes 283354 nps 1591876 pv b1c3 g8f6 e2e4 e7e5 g1f3 b8c6 f1b5
info depth 12 score cp 16 time 309 nodes 490140 nps 1586213 pv g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 f1b5 c8d7 b5d3 b8c6 e1g1 f6
e4 b1d2
info depth 13 score cp 17 time 659 nodes 1061042 nps 1610078 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5f3 f6e4 d2d3 e4f6 b1c3 b
8c6 c1f4
info depth 14 score cp 10 time 3687 nodes 5651804 nps 1532900 pv g1f3 d7d5 d2d4 g8f6 e2e3 e7e6 f1d3 b8c6 e1g1 f8d6 b1c3
d6b4 c1d2 e8g8
info depth 14 score cp 10 time 45000 nodes 65755136 nps 1461225 pv g1f3 d7d5 d2d4 g8f6 e2e3 e7e6 f1d3 b8c6 e1g1 f8d6 b1c
3 d6b4 c1d2 e8g8
bestmove g1f3

Score of Altair0.19 vs Altair0.18: 81 - 91 - 128 [0.483]
...      Altair0.19 playing White: 35 - 57 - 58  [0.427] 150
...      Altair0.19 playing Black: 46 - 34 - 70  [0.540] 150
...      White vs Black: 69 - 103 - 128  [0.443] 300
Elo difference: -11.6 +/- 29.8, LOS: 22.3 %, DrawRatio: 42.7 %
300 of 300 games finished.
```

### Evaluation incorporated into TT + Reverse Futility Pruning

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 262 nps 87333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 5 nodes 843 nps 168600 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 7 nodes 1803 nps 257571 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 10 nodes 3932 nps 393200 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 14 nodes 8155 nps 582500 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 19 time 31 nodes 32865 nps 1060161 pv e2e4 g8f6 e4e5 f6d5 b1c3 d5c3 d2c3 b8c6
info depth 9 score cp 20 time 59 nodes 76064 nps 1289220 pv e2e4 b8c6 b1c3 e7e5 f1b5 g8e7 g1f3 a7a6 b5c4
info depth 10 score cp 14 time 115 nodes 165525 nps 1439347 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5
info depth 11 score cp 14 time 169 nodes 253879 nps 1502242 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 a2a3 b4c3 d2c3
info depth 12 score cp 8 time 357 nodes 559863 nps 1568243 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 e1g1 e8g8 b5c6 d7c
6
info depth 13 score cp 21 time 475 nodes 753009 nps 1585282 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d1e2 d7d6 e2c4 b4
c3 d2c3
info depth 14 score cp 10 time 1420 nodes 2276870 nps 1603429 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d1e2 d8e7 e1g1
e8g8 a2a3 b4c5
info depth 14 score cp 10 time 45000 nodes 68747276 nps 1527717 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d1e2 d8e7 e1g
1 e8g8 a2a3 b4c5
bestmove e2e4

Score of Altair0.20 vs Altair0.19: 69 - 45 - 86 [0.560]
...      Altair0.20 playing White: 29 - 27 - 44  [0.510] 100
...      Altair0.20 playing Black: 40 - 18 - 42  [0.610] 100
...      White vs Black: 47 - 67 - 86  [0.450] 200
Elo difference: 41.9 +/- 36.5, LOS: 98.8 %, DrawRatio: 43.0 %
200 of 200 games finished.
```

### Countermove Heuristic

```

*Low node counts because computer is acting up*
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 2 nodes 262 nps 131000 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 795 nps 198750 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 6 nodes 1761 nps 293500 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 9 nodes 4535 nps 503888 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 16 nodes 10622 nps 663875 pv b1c3 g8f6 d2d4 b8c6 g1f3 d7d5 e2e3
info depth 8 score cp 19 time 34 nodes 31336 nps 921647 pv e2e4 g8f6 e4e5 f6d5 b1c3 d5c3
info depth 9 score cp 23 time 61 nodes 60590 nps 993278 pv e2e4 b8c6 g1f3 d7d5 b1c3 g8f6 e4e5
info depth 10 score cp 14 time 209 nodes 214003 nps 1023937 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
info depth 11 score cp 22 time 287 nodes 296150 nps 1031881 pv e2e4 e7e5 g1e2 g8f6 b1c3 f8b4 a2a3 b4c3 e2c3 b8c6 f1b5
info depth 12 score cp 25 time 639 nodes 692283 nps 1083384 pv g1f3 g8f6 d2d4 d7d5 e2e3 b8c6 f1b5 c8d7 e1g1 a7a6 b5d3 e7
e6
info depth 13 score cp 16 time 823 nodes 889220 nps 1080461 pv g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 f1b5 b8d7 e1g1 c7c6 b5d3 f8
d6 b1c3 e8g8
info depth 14 score cp 10 time 1733 nodes 1895454 nps 1093741 pv g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 f1d3 b8c6 e1g1 f8b4 a2a3
b4d6 b1c3 e8g8
info depth 15 score cp 10 time 2923 nodes 3208393 nps 1097637 pv g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 f1d3 b8c6 e1g1 f8d6 b1c3
e8g8 d3b5 c8d7 d1d3
info depth 15 score cp 10 time 45000 nodes 43366400 nps 963697 pv g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 f1d3 b8c6 e1g1 f8d6 b1c3
 e8g8 d3b5 c8d7 d1d3
bestmove g1f3

Score of Altair0.21 vs Altair0.20: 61 - 56 - 83 [0.512]
...      Altair0.21 playing White: 33 - 29 - 38  [0.520] 100
...      Altair0.21 playing Black: 28 - 27 - 45  [0.505] 100
...      White vs Black: 60 - 57 - 83  [0.507] 200
Elo difference: 8.7 +/- 36.9, LOS: 67.8 %, DrawRatio: 41.5 %
200 of 200 games finished.
```


### Tweaking Move Ordering Parameters

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 0 nodes 86 nps 860000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 262 nps 87333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 5 nodes 843 nps 168600 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 8 nodes 1800 nps 225000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 15 nodes 4500 nps 300000 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 24 nodes 11589 nps 482875 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 e2e3
info depth 8 score cp 8 time 36 nodes 20923 nps 581194 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 e2e3 e7e6
info depth 9 score cp 17 time 93 nodes 72420 nps 778709 pv b1c3 g8f6 g1f3 d7d5 d2d4
info depth 10 score cp 15 time 230 nodes 242402 nps 1053921 pv e2e4 e7e5 g1f3 b8c6 f1b5
info depth 11 score cp 28 time 298 nodes 323183 nps 1084506 pv e2e4 e7e5 g1f3 b8c6 f1b5 g8f6 d2d3 f8d6 e1g1 e8g8 b1c3
info depth 12 score cp 28 time 390 nodes 443681 nps 1137643 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d2d3
info depth 13 score cp 21 time 568 nodes 711066 nps 1251876 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 b4c3 d2c3 f6
e4 f3d4
info depth 14 score cp 39 time 964 nodes 1328381 nps 1377988 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3 f
8e8 e1g1 b4c3
info depth 15 score cp 39 time 1310 nodes 1889745 nps 1442553 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3
f8e8 e1g1 b4c3 d2c3
info depth 16 score cp 39 time 2496 nodes 3685212 nps 1476447 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3
f8e8 e1g1 b4c3 d2c3 f6e4
info depth 16 score cp 39 time 45000 nodes 58359817 nps 1296884 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d
3 f8e8 e1g1 b4c3 d2c3 f6e4
bestmove e2e4

Score of Altair0.22 vs Altair0.21: 59 - 51 - 90 [0.520]
...      Altair0.22 playing White: 26 - 28 - 46  [0.490] 100
...      Altair0.22 playing Black: 33 - 23 - 44  [0.550] 100
...      White vs Black: 49 - 61 - 90  [0.470] 200
Elo difference: 13.9 +/- 35.8, LOS: 77.7 %, DrawRatio: 45.0 %
200 of 200 games finished.

Score of Altair0.22 vs GOOBv1: 71 - 55 - 24 [0.553]
...      Altair0.22 playing White: 27 - 34 - 14  [0.453] 75
...      Altair0.22 playing Black: 44 - 21 - 10  [0.653] 75
...      White vs Black: 48 - 78 - 24  [0.400] 150
Elo difference: 37.2 +/- 51.5, LOS: 92.3 %, DrawRatio: 16.0 %
150 of 150 games finished.
```

### Insufficient Material / Drawishness checks

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 2 nodes 262 nps 131000 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 843 nps 210750 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 6 nodes 1800 nps 300000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 9 nodes 4500 nps 500000 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 15 nodes 11589 nps 772600 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 e2e3
info depth 8 score cp 8 time 24 nodes 20923 nps 871791 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 e2e3 e7e6
info depth 9 score cp 17 time 69 nodes 72420 nps 1049565 pv b1c3 g8f6 g1f3 d7d5 d2d4
info depth 10 score cp 15 time 226 nodes 242402 nps 1072575 pv e2e4 e7e5 g1f3 b8c6 f1b5
info depth 11 score cp 28 time 302 nodes 323183 nps 1070142 pv e2e4 e7e5 g1f3 b8c6 f1b5 g8f6 d2d3 f8d6 e1g1 e8g8 b1c3
info depth 12 score cp 28 time 411 nodes 443681 nps 1079515 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1b5 f8b4 d2d3
info depth 13 score cp 21 time 656 nodes 711066 nps 1083942 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 b4c3 d2c3 f6
e4 f3d4
info depth 14 score cp 39 time 1211 nodes 1328381 nps 1096928 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3
f8e8 e1g1 b4c3
info depth 15 score cp 39 time 1691 nodes 1889745 nps 1117531 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3
f8e8 e1g1 b4c3 d2c3
info depth 16 score cp 39 time 3244 nodes 3685212 nps 1136008 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3
f8e8 e1g1 b4c3 d2c3 f6e4
info depth 16 score cp 39 time 45001 nodes 44671005 nps 992666 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3e5 d7d6 e5f3 e8g8 f1d3
 f8e8 e1g1 b4c3 d2c3 f6e4
bestmove e2e4

Score of Altair0.23 vs Altair0.22: 82 - 97 - 121 [0.475]
...      Altair0.23 playing White: 37 - 55 - 58  [0.440] 150
...      Altair0.23 playing Black: 45 - 42 - 63  [0.510] 150
...      White vs Black: 79 - 100 - 121  [0.465] 300
Elo difference: -17.4 +/- 30.4, LOS: 13.1 %, DrawRatio: 40.3 %
300 of 300 games finished.
```

### Bishop Pair Bonus

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 2 nodes 262 nps 131000 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 843 nps 210750 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 6 nodes 1801 nps 300166 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 10 nodes 4495 nps 449500 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 17 nodes 11410 nps 671176 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 e2e3
info depth 8 score cp 8 time 24 nodes 20399 nps 849958 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 e2e3 e7e6
info depth 9 score cp 21 time 45 nodes 53472 nps 1188266 pv b1c3 d7d5 e2e4 d5e4 c3e4 b8c6 g1e2 g8f6 e2c3
info depth 10 score cp 22 time 83 nodes 117007 nps 1409722 pv e2e4 g8f6 b1c3 d7d5 e4e5 f6e4 c3e4 d5e4 f1b5 c8d7 b5c4
info depth 11 score cp 35 time 185 nodes 282738 nps 1528313 pv e2e4 b8c6 g1f3 e7e6 d2d4 g8f6 b1d2 d7d5 e4e5 f6e4 d2e4
info depth 12 score cp 30 time 278 nodes 439403 nps 1580586 pv e2e4 g8f6 b1c3 d7d5 e4e5 f6e4 c3e4 d5e4 d2d4 b8c6 g1e2 e7
e6
info depth 13 score cp 39 time 493 nodes 786793 nps 1595929 pv e2e4 g8f6 b1c3 d7d5 e4e5 f6e4 c3e4 d5e4 d2d4 b8c6 g1e2 e7
e6 c1f4
info depth 14 score cp 33 time 802 nodes 1282981 nps 1599726 pv e2e4 g8f6 e4e5 f6d5 g1f3 b8c6 b1c3 d5c3 d2c3 d7d6 c1f4 f
7f6 e5d6 e7d6
info depth 15 score cp 36 time 3051 nodes 4896627 nps 1604925 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
info depth 15 score cp 36 time 44999 nodes 69900305 nps 1553374 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
bestmove e2e4

Score of Altair0.24 vs Altair0.23: 128 - 99 - 128 [0.541]
...      Altair0.24 playing White: 57 - 52 - 69  [0.514] 178
...      Altair0.24 playing Black: 71 - 47 - 59  [0.568] 177
...      White vs Black: 104 - 123 - 128  [0.473] 355
Elo difference: 28.4 +/- 29.0, LOS: 97.3 %, DrawRatio: 36.1 %
359 of 500 games finished.
```

### Eval Changes. 
Seperate functions for each piece, open and semi-open files for rooks, queens, and kings.

```
info depth 1 score cp 42 time 0 nodes 26 nps 260000 pv b1c3
info depth 2 score cp 8 time 1 nodes 86 nps 86000 pv b1c3 b8c6
info depth 3 score cp 42 time 3 nodes 262 nps 87333 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 4 nodes 843 nps 210750 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 6 nodes 1801 nps 300166 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 9 nodes 4712 nps 523555 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 16 nodes 11182 nps 698875 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6 e2e3
info depth 8 score cp 8 time 26 nodes 23023 nps 885500 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6 e2e3 e7e6
info depth 9 score cp 23 time 53 nodes 62229 nps 1174132 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4
info depth 10 score cp 27 time 80 nodes 101709 nps 1271362 pv e2e4 b8c6 g1f3 d7d5 e4d5 d8d5 d2d4 g8f6 b1c3 d5d6
info depth 11 score cp 20 time 227 nodes 316053 nps 1392303 pv e2e4 e7e5 g1f3 b8c6 b1c3
info depth 12 score cp 27 time 527 nodes 771789 nps 1464495 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3 b8c6 g1f3
info depth 13 score cp 28 time 816 nodes 1098553 nps 1346265 pv e2e4 b8c6 d2d4 e7e6 b1c3 d7d5 g1e2 g8e7 e4e5 c8d7 c1g5 h
7h6 g5f4
info depth 14 score cp 27 time 1147 nodes 1603854 nps 1398303 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3 b8c6 g1f3
e7e6 c1g5 f8b4
info depth 15 score cp 28 time 1830 nodes 2641936 nps 1443680 pv e2e4 e7e6 d2d4 b8c6 g1f3 d7d5 e4e5 f8b4 c2c3 b4a5 b1d2
g8e7 f1d3 e8g8 e1g1 a5b6
info depth 15 score cp 28 time 44999 nodes 61997056 nps 1377742 pv e2e4 e7e6 d2d4 b8c6 g1f3 d7d5 e4e5 f8b4 c2c3 b4a5 b1d
2 g8e7 f1d3 e8g8 e1g1 a5b6
bestmove e2e4

Score of Altair0.25 vs Altair0.24: 100 - 91 - 109 [0.515]
...      Altair0.25 playing White: 50 - 48 - 52  [0.507] 150
...      Altair0.25 playing Black: 50 - 43 - 57  [0.523] 150
...      White vs Black: 93 - 98 - 109  [0.492] 300
Elo difference: 10.4 +/- 31.4, LOS: 74.3 %, DrawRatio: 36.3 %
300 of 300 games finished.
```


### King Tropism

```
info depth 1 score cp 47 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 score cp 8 time 3 nodes 87 nps 29000 pv b1c3 b8c6
info depth 3 score cp 46 time 5 nodes 258 nps 51600 pv b1c3 b8c6 g1f3
info depth 4 score cp 8 time 6 nodes 856 nps 142666 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 38 time 8 nodes 1825 nps 228125 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 8 time 10 nodes 4161 nps 416100 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 22 time 14 nodes 8207 nps 586214 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 8 time 27 nodes 22508 nps 833629 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6
info depth 9 score cp 24 time 45 nodes 45296 nps 1006577 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4
info depth 10 score cp 24 time 72 nodes 78395 nps 1088819 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4 d5e4
info depth 11 score cp 36 time 228 nodes 273194 nps 1198219 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 d2d4 g8f6 e4e5 f6e4 c3e4
info depth 12 score cp 12 time 529 nodes 651581 nps 1231722 pv e2e4 d7d5 e4e5 d5d4 g1f3 e7e6 d2d3 b8c6 b1d2 g8e7 d2e4 e7
d5
info depth 13 score cp 34 time 1442 nodes 1676221 nps 1162427 pv e2e4 e7e6 d2d4 b8c6 b1c3 d7d5
info depth 14 score cp 28 time 3258 nodes 2926295 nps 898187 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 b8c6 c2c4 d5f6 b1c3 e
7e6 c1g5 f8b4
info depth 15 score cp 34 time 5285 nodes 4848358 nps 917380 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f3 e7e6
info depth 16 score cp 30 time 9293 nodes 9527267 nps 1025208 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f3 e7e6 b1c3
b8c6 c1f4 f8b4 a2a3 b4d6
info depth 16 score cp 30 time 45000 nodes 52383755 nps 1164083 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f3 e7e6 b1c
3 b8c6 c1f4 f8b4 a2a3 b4d6
bestmove e2e4

Score of Altair0.26 vs Altair0.25: 96 - 84 - 120 [0.520]
...      Altair0.26 playing White: 49 - 35 - 66  [0.547] 150
...      Altair0.26 playing Black: 47 - 49 - 54  [0.493] 150
...      White vs Black: 98 - 82 - 120  [0.527] 300
Elo difference: 13.9 +/- 30.5, LOS: 81.4 %, DrawRatio: 40.0 %
300 of 300 games finished.
```

### Own king safety penalty idea

```
info depth 1 score cp 51 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 score cp 7 time 1 nodes 87 nps 87000 pv b1c3 b8c6
info depth 3 score cp 49 time 3 nodes 258 nps 86000 pv b1c3 b8c6 g1f3
info depth 4 score cp 7 time 5 nodes 852 nps 170400 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 40 time 6 nodes 1823 nps 303833 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 7 time 9 nodes 3930 nps 436666 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 23 time 13 nodes 7754 nps 596461 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 7 time 26 nodes 24159 nps 929192 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6
info depth 9 score cp 24 time 45 nodes 47151 nps 1047800 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4
info depth 10 score cp 24 time 70 nodes 79665 nps 1138071 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4 d5e4
info depth 11 score cp 24 time 243 nodes 299107 nps 1230893 pv e2e4 d7d5 e4e5 b8c6 g1f3 c8g4 f1b5 e7e6 e1g1 a7a6 b5c6
info depth 12 score cp 35 time 386 nodes 483215 nps 1251852 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6
info depth 13 score cp 42 time 584 nodes 713258 nps 1221332 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 b8c6 c2c4 d5f6 b1c3 c8
g4 c1f4
info depth 14 score cp 27 time 771 nodes 958014 nps 1242560 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 b8c6 c2c4 d5f6 b1c3 c8
g4 c1g5 e7e6
info depth 15 score cp 35 time 1174 nodes 1492687 nps 1271454 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 b8c6 f1b5 d8d6 e1g1
a7a6 b5c4 c8g4 c1g5
info depth 16 score cp 35 time 2975 nodes 3832910 nps 1288373 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 e7e6 c2c4 f8b4 b1d2
d5f6 a2a3 b4d2 c1d2 b8c6 d2g5 e8g8
info depth 16 score cp 35 time 45004 nodes 55107584 nps 1224504 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 e7e6 c2c4 f8b4 b1d
2 d5f6 a2a3 b4d2 c1d2 b8c6 d2g5 e8g8
bestmove e2e4

Score of Altair0.27 vs Altair0.26: 93 - 93 - 114 [0.500]
...      Altair0.27 playing White: 44 - 46 - 60  [0.493] 150
...      Altair0.27 playing Black: 49 - 47 - 54  [0.507] 150
...      White vs Black: 91 - 95 - 114  [0.493] 300
Elo difference: 0.0 +/- 31.0, LOS: 50.0 %, DrawRatio: 38.0 %
300 of 300 games finished.

info depth 1 score cp 49 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 score cp 7 time 2 nodes 87 nps 43500 pv b1c3 b8c6
info depth 3 score cp 48 time 3 nodes 258 nps 86000 pv b1c3 b8c6 g1f3
info depth 4 score cp 7 time 4 nodes 853 nps 213250 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 40 time 6 nodes 1824 nps 304000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 7 time 8 nodes 4159 nps 519875 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 23 time 12 nodes 8019 nps 668250 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 e2e3
info depth 8 score cp 7 time 25 nodes 22601 nps 904040 pv b1c3 g8f6 e2e3 d7d5 g1f3 b8c6 d2d4 e7e6
info depth 9 score cp 24 time 59 nodes 66640 nps 1129491 pv e2e4 b8c6 b1c3 g8f6
info depth 10 score cp 9 time 123 nodes 146978 nps 1194943 pv e2e4 d7d5 e4e5 b8c6 d2d4 c8f5 g1f3 e7e6 b1c3 g8e7
info depth 11 score cp 24 time 205 nodes 251407 nps 1226375 pv e2e4 d7d5 e4e5 b8c6 d2d4 c8f5 g1f3 e7e6 b1c3 g8e7 c1g5
info depth 12 score cp 27 time 397 nodes 494952 nps 1246730 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3 b8c6 g1f3 e7
e6
info depth 13 score cp 37 time 760 nodes 960113 nps 1263306 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 f1b5 a7a6 b5c6 b7
c6 e1g1 c8f5
info depth 14 score cp 28 time 1452 nodes 1831010 nps 1261026 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3 b8c6 g1f3
e7e6 c1g5 f8b4
info depth 15 score cp 30 time 2459 nodes 3127577 nps 1271889 pv e2e4 e7e6 b1c3 d7d5 d2d4 b8c6 g1f3 f8b4 e4d5 e6d5 f1b5
g8e7 e1g1 e8g8 f1e1
info depth 15 score cp 30 time 45000 nodes 55326748 nps 1229483 pv e2e4 e7e6 b1c3 d7d5 d2d4 b8c6 g1f3 f8b4 e4d5 e6d5 f1b
5 g8e7 e1g1 e8g8 f1e1
bestmove e2e4

Score of Altair0.28 vs Altair0.27: 148 - 129 - 223 [0.519]
...      Altair0.28 playing White: 78 - 64 - 108  [0.528] 250
...      Altair0.28 playing Black: 70 - 65 - 115  [0.510] 250
...      White vs Black: 143 - 134 - 223  [0.509] 500
Elo difference: 13.2 +/- 22.7, LOS: 87.3 %, DrawRatio: 44.6 %
500 of 500 games finished.
```


### Aspiration Windows

```
info depth 1 score cp 49 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 score cp 7 time 2 nodes 87 nps 43500 pv b1c3 b8c6
info depth 3 score cp 48 time 4 nodes 292 nps 73000 pv b1c3 b8c6 g1f3
info depth 4 score cp 7 time 6 nodes 1017 nps 169500 pv b1c3 b8c6 g1f3 g8f6
info depth 5 score cp 40 time 8 nodes 1848 nps 231000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 score cp 7 time 10 nodes 3620 nps 362000 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 score cp 23 time 14 nodes 7116 nps 508285 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 score cp 7 time 26 nodes 21699 nps 834576 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3
info depth 9 score cp 24 time 51 nodes 53286 nps 1044823 pv e2e4 b8c6 b1c3 g8f6
info depth 10 score cp 24 time 79 nodes 87352 nps 1105721 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4 d5e4
info depth 11 score cp 16 time 172 nodes 208219 nps 1210575 pv e2e4 d7d5 e4d5 g8f6 b1c3 f6d5 c3d5 d8d5 d2d4 b8c6 g1f3
info depth 12 score cp 14 time 436 nodes 543843 nps 1247346 pv e2e4 d7d5 b1c3 d5e4 c3e4 e7e5 g1f3 g8f6 d2d3 f6e4 d3e4 b8
d7
info depth 13 score cp 36 time 660 nodes 843066 nps 1277372 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5b6 g1f3 b8c6 b1c3 c8
e6 d4d5
info depth 14 score cp 27 time 838 nodes 1083040 nps 1292410 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3 b8c6 g1f3 c
8g4 c1g5 e7e6
info depth 15 score cp 35 time 1713 nodes 2215086 nps 1293103 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f3 e7e6 b1c3
b8c6 c1g5 h7h6 g5f4
info depth 16 score cp 30 time 3363 nodes 4366142 nps 1298287 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f3 e7e6 b1c3
b8c6 c1f4 f8b4 a2a3 b4d6
info depth 16 score cp 30 time 45001 nodes 53374988 nps 1186084 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f3 e7e6 b1c
3 b8c6 c1f4 f8b4 a2a3 b4d6
bestmove e2e4

Score of Altair0.29 vs Altair0.28: 184 - 116 - 200 [0.568]
...      Altair0.29 playing White: 92 - 51 - 107  [0.582] 250
...      Altair0.29 playing Black: 92 - 65 - 93  [0.554] 250
...      White vs Black: 157 - 143 - 200  [0.514] 500
Elo difference: 47.5 +/- 23.7, LOS: 100.0 %, DrawRatio: 40.0 %
500 of 500 games finished.

Score of Altair0.29 vs bienchen.1.0: 40 - 81 - 29 [0.363]
...      Altair0.29 playing White: 21 - 35 - 19  [0.407] 75
...      Altair0.29 playing Black: 19 - 46 - 10  [0.320] 75
...      White vs Black: 67 - 54 - 29  [0.543] 150
Elo difference: -97.4 +/- 51.8, LOS: 0.0 %, DrawRatio: 19.3 %
150 of 150 games finished.

Score of Altair0.29 vs bbc_1.1_64bit_windows: 73 - 13 - 14 [0.800]
...      Altair0.29 playing White: 36 - 9 - 5  [0.770] 50
...      Altair0.29 playing Black: 37 - 4 - 9  [0.830] 50
...      White vs Black: 40 - 46 - 14  [0.470] 100
Elo difference: 240.8 +/- 77.8, LOS: 100.0 %, DrawRatio: 14.0 %
100 of 100 games finished.

Score of Altair0.29 vs GOOBv1: 86 - 34 - 30 [0.673]
...      Altair0.29 playing White: 38 - 21 - 16  [0.613] 75
...      Altair0.29 playing Black: 48 - 13 - 14  [0.733] 75
...      White vs Black: 51 - 69 - 30  [0.440] 150
Elo difference: 125.7 +/- 52.6, LOS: 100.0 %, DrawRatio: 20.0 %
150 of 150 games finished.
```


### Simple Internal Iterative Deepening Implementation

```
info depth 1 seldepth 1 score cp 49 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 87 nps 87000 pv b1c3 b8c6
info depth 3 seldepth 5 score cp 48 time 3 nodes 292 nps 97333 pv b1c3 b8c6 g1f3
info depth 4 seldepth 7 score cp 7 time 5 nodes 1017 nps 203400 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 9 score cp 40 time 7 nodes 1848 nps 264000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 13 score cp 7 time 11 nodes 3620 nps 329090 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 13 score cp 23 time 14 nodes 7116 nps 508285 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 seldepth 18 score cp 7 time 26 nodes 21699 nps 834576 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3
info depth 9 seldepth 21 score cp 24 time 52 nodes 53309 nps 1025173 pv e2e4 b8c6 b1c3 g8f6
info depth 10 seldepth 21 score cp 24 time 80 nodes 87367 nps 1092087 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4 d5
e4
info depth 11 seldepth 21 score cp 16 time 173 nodes 208234 nps 1203664 pv e2e4 d7d5 e4d5 g8f6 b1c3 f6d5 c3d5 d8d5 d2d4
b8c6 g1f3
info depth 12 seldepth 26 score cp 14 time 446 nodes 543694 nps 1219044 pv e2e4 d7d5 b1c3 d5e4 c3e4 e7e5 g1f3 g8f6 d2d3
f6e4 d3e4 b8d7
info depth 13 seldepth 29 score cp 36 time 670 nodes 842747 nps 1257831 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5b6 g1f3
b8c6 b1c3 c8e6 d4d5
info depth 14 seldepth 29 score cp 27 time 848 nodes 1082881 nps 1276982 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3
 b8c6 g1f3 c8g4 c1g5 e7e6
info depth 15 seldepth 30 score cp 35 time 1748 nodes 2243788 nps 1283631 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f
3 e7e6 b1c3 b8c6 c1g5 h7h6 g5f4
info depth 16 seldepth 31 score cp 30 time 3233 nodes 4166061 nps 1288605 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f
3 e7e6 b1c3 b8c6 c1f4 f8b4 a2a3 b4d6
info depth 16 seldepth 36 score cp 30 time 45003 nodes 52081854 nps 1157297 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g
1f3 e7e6 b1c3 b8c6 c1f4 f8b4 a2a3 b4d6
bestmove e2e4

Score of Altair0.30 vs Altair0.29: 56 - 58 - 86 [0.495]
...      Altair0.30 playing White: 25 - 33 - 42  [0.460] 100
...      Altair0.30 playing Black: 31 - 25 - 44  [0.530] 100
...      White vs Black: 50 - 64 - 86  [0.465] 200
Elo difference: -3.5 +/- 36.4, LOS: 42.6 %, DrawRatio: 43.0 %
200 of 200 games finished.

Score of Altair0.30 vs bienchen.1.0: 49 - 77 - 24 [0.407]
...      Altair0.30 playing White: 30 - 31 - 14  [0.493] 75
...      Altair0.30 playing Black: 19 - 46 - 10  [0.320] 75
...      White vs Black: 76 - 50 - 24  [0.587] 150
Elo difference: -65.6 +/- 52.0, LOS: 0.6 %, DrawRatio: 16.0 %
150 of 150 games finished.
```


### TT probing and check extensions ahead of Qsearch

```
go movetime 50000
45000
info depth 1 seldepth 1 score cp 49 time 0 nodes 53 nps 530000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 152 nps 152000 pv b1c3 b8c6
info depth 3 seldepth 5 score cp 48 time 3 nodes 492 nps 164000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 7 score cp 7 time 5 nodes 1595 nps 319000 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 9 score cp 40 time 6 nodes 2908 nps 484666 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 13 score cp 7 time 9 nodes 5541 nps 615666 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 13 score cp 23 time 12 nodes 10809 nps 900750 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 e2e3
info depth 8 seldepth 17 score cp 7 time 24 nodes 30593 nps 1274708 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3
info depth 9 seldepth 19 score cp 24 time 45 nodes 67519 nps 1500422 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4
info depth 10 seldepth 20 score cp 24 time 66 nodes 105151 nps 1593196 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4 d
5e4
info depth 11 seldepth 23 score cp 40 time 227 nodes 398420 nps 1755154 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 e4e5 g8e7 d2d4
e7f5 c1g5
info depth 12 seldepth 25 score cp 27 time 391 nodes 701155 nps 1793235 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3
b8c6 g1f3 e7e6
info depth 13 seldepth 28 score cp 38 time 667 nodes 1212450 nps 1817766 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 d2d4 f8b4 e4d5
 e6d5 f3e5 c6e5 d4e5
info depth 14 seldepth 28 score cp 28 time 998 nodes 1829614 nps 1833280 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3
 b8c6 g1f3 e7e6 c1g5 f8b4
info depth 15 seldepth 28 score cp 35 time 1486 nodes 2739849 nps 1843774 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c
3 b8c6 g1f3 e7e6 c1g5 h7h6 g5f4
info depth 16 seldepth 29 score cp 30 time 2521 nodes 4642843 nps 1841667 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c
3 b8c6 g1f3 e7e6 c1f4 f8b4 a2a3 b4d6
info depth 16 seldepth 37 score cp 30 time 45004 nodes 71278037 nps 1583815 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b
1c3 b8c6 g1f3 e7e6 c1f4 f8b4 a2a3 b4d6
bestmove e2e4

Score of Altair0.31 vs Altair0.30: 67 - 49 - 84 [0.545]
...      Altair0.31 playing White: 34 - 22 - 44  [0.560] 100
...      Altair0.31 playing Black: 33 - 27 - 40  [0.530] 100
...      White vs Black: 61 - 55 - 84  [0.515] 200
Elo difference: 31.4 +/- 36.8, LOS: 95.3 %, DrawRatio: 42.0 %
200 of 200 games finished.

Score of Altair0.31 vs bienchen.1.0: 51 - 71 - 28 [0.433]
...      Altair0.31 playing White: 26 - 33 - 16  [0.453] 75
...      Altair0.31 playing Black: 25 - 38 - 12  [0.413] 75
...      White vs Black: 64 - 58 - 28  [0.520] 150
Elo difference: -46.6 +/- 50.8, LOS: 3.5 %, DrawRatio: 18.7 %
150 of 150 games finished.

Score of Altair0.31 vs GOOBv1: 69 - 17 - 14 [0.760]
...      Altair0.31 playing White: 34 - 8 - 8  [0.760] 50
...      Altair0.31 playing Black: 35 - 9 - 6  [0.760] 50
...      White vs Black: 43 - 43 - 14  [0.500] 100
Elo difference: 200.2 +/- 73.5, LOS: 100.0 %, DrawRatio: 14.0 %
100 of 100 games finished.

4 min / 40 moves repeating
Score of Altair0.31 vs bienchen.1.0: 31 - 84 - 40 [0.329]
...      Altair0.31 playing White: 16 - 40 - 23  [0.348] 79
...      Altair0.31 playing Black: 15 - 44 - 17  [0.309] 76
...      White vs Black: 60 - 55 - 40  [0.516] 155
Elo difference: -123.8 +/- 49.3, LOS: 0.0 %, DrawRatio: 25.8 %
162 of 1000 games finished.
```


### Mobility Eval + small RFP changes

```
info depth 1 seldepth 1 score cp 62 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 5 score cp 61 time 3 nodes 321 nps 107000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 7 score cp 7 time 6 nodes 1306 nps 217666 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 9 score cp 51 time 8 nodes 2067 nps 258375 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 13 score cp 7 time 14 nodes 7376 nps 526857 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 17 score cp 32 time 21 nodes 11532 nps 549142 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 24 score cp 7 time 43 nodes 28273 nps 657511 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4
info depth 9 seldepth 24 score cp 29 time 58 nodes 42020 nps 724482 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 10 time 130 nodes 110482 nps 849861 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 f1b5 c7c6 b5d3 f
8b4 c1d2 d8d6
info depth 11 seldepth 25 score cp 26 time 218 nodes 194563 nps 892490 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 b1c3 f8b4 f3e5 e
8g8 f1b5
info depth 12 seldepth 30 score cp 23 time 351 nodes 321311 nps 915415 pv d2d4 d7d5 b1c3 g8f6 c1f4 b8c6 g1f3 c8g4 e2e3 e
7e6 h2h3 g4f5
info depth 13 seldepth 30 score cp 27 time 812 nodes 759489 nps 935331 pv d2d4 d7d5 b1c3 e7e6 e2e4 d5e4 c3e4 b8c6 g1f3
info depth 14 seldepth 30 score cp 32 time 1840 nodes 1766784 nps 960208 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3
 b8c6 g1f3 c8g4
info depth 15 seldepth 31 score cp 35 time 3457 nodes 3291572 nps 952146 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 b8c6 b1c3
 g8f6 f1b5 d8e7 f3e5 c8d7 c1f4 c6e5
info depth 16 seldepth 38 score cp 40 time 7135 nodes 6694944 nps 938324 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4 b8c6 g1f3
 g8f6 e4f6 d8f6 c1g5 f6f5 c2c3 f8d6 f1c4
info depth 16 seldepth 38 score cp 40 time 45005 nodes 39324596 nps 873782 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4 b8c6 g1
f3 g8f6 e4f6 d8f6 c1g5 f6f5 c2c3 f8d6 f1c4
bestmove e2e4


Score of Altair0.32 vs Altair0.31: 88 - 87 - 125 [0.502]
...      Altair0.32 playing White: 45 - 41 - 64  [0.513] 150
...      Altair0.32 playing Black: 43 - 46 - 61  [0.490] 150
...      White vs Black: 91 - 84 - 125  [0.512] 300
Elo difference: 1.2 +/- 30.1, LOS: 53.0 %, DrawRatio: 41.7 %
300 of 300 games finished.

Score of Altair0.32 vs bienchen.1.0: 80 - 77 - 43 [0.507]
...      Altair0.32 playing White: 39 - 39 - 22  [0.500] 100
...      Altair0.32 playing Black: 41 - 38 - 21  [0.515] 100
...      White vs Black: 77 - 80 - 43  [0.492] 200
Elo difference: 5.2 +/- 42.8, LOS: 59.5 %, DrawRatio: 21.5 %
200 of 200 games finished.

Score of Altair0.32 vs sofcheck_amd64-popcnt_windows: 33 - 82 - 35 [0.337]
...      Altair0.32 playing White: 15 - 44 - 16  [0.307] 75
...      Altair0.32 playing Black: 18 - 38 - 19  [0.367] 75
...      White vs Black: 53 - 62 - 35  [0.470] 150
Elo difference: -117.8 +/- 51.0, LOS: 0.0 %, DrawRatio: 23.3 %
150 of 150 games finished.
```


### Storing Mate Values in TT + Mate distance pruning


```
info depth 1 seldepth 1 score cp 62 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 5 score cp 61 time 3 nodes 321 nps 107000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 7 score cp 7 time 6 nodes 1306 nps 217666 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 9 score cp 51 time 8 nodes 2067 nps 258375 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 13 score cp 7 time 18 nodes 7376 nps 409777 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 17 score cp 32 time 25 nodes 11532 nps 461280 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 24 score cp 7 time 51 nodes 28273 nps 554372 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4
info depth 9 seldepth 24 score cp 29 time 73 nodes 42020 nps 575616 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 10 time 149 nodes 110482 nps 741489 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 f1b5 c7c6 b5d3 f
8b4 c1d2 d8d6
info depth 11 seldepth 25 score cp 26 time 240 nodes 194563 nps 810679 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 b1c3 f8b4 f3e5 e
8g8 f1b5
info depth 12 seldepth 30 score cp 23 time 370 nodes 321311 nps 868408 pv d2d4 d7d5 b1c3 g8f6 c1f4 b8c6 g1f3 c8g4 e2e3 e
7e6 h2h3 g4f5
info depth 13 seldepth 30 score cp 27 time 827 nodes 759489 nps 918366 pv d2d4 d7d5 b1c3 e7e6 e2e4 d5e4 c3e4 b8c6 g1f3
info depth 14 seldepth 30 score cp 32 time 1871 nodes 1766784 nps 944299 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3
 b8c6 g1f3 c8g4
info depth 15 seldepth 31 score cp 35 time 3644 nodes 3291572 nps 903285 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 b8c6 b1c3
 g8f6 f1b5 d8e7 f3e5 c8d7 c1f4 c6e5
info depth 16 seldepth 38 score cp 40 time 7391 nodes 6694945 nps 905823 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4 b8c6 g1f3
 g8f6 e4f6 d8f6 c1g5 f6f5 c2c3 f8d6 f1c4
info depth 16 seldepth 40 score cp 40 time 45006 nodes 39688395 nps 881846 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4 b8c6 g1
f3 g8f6 e4f6 d8f6 c1g5 f6f5 c2c3 f8d6 f1c4
bestmove e2e4

Score of Altair0.33 vs Altair0.32: 40 - 42 - 68 [0.493]
...      Altair0.33 playing White: 22 - 21 - 32  [0.507] 75
...      Altair0.33 playing Black: 18 - 21 - 36  [0.480] 75
...      White vs Black: 43 - 39 - 68  [0.513] 150
Elo difference: -4.6 +/- 41.2, LOS: 41.3 %, DrawRatio: 45.3 %
150 of 150 games finished.
```


### Big time handling changes

```

5 sec + 0.05
Score of Altair0.34 vs Altair0.33: 38 - 49 - 63 [0.463]
...      Altair0.34 playing White: 20 - 25 - 30  [0.467] 75
...      Altair0.34 playing Black: 18 - 24 - 33  [0.460] 75
...      White vs Black: 44 - 43 - 63  [0.503] 150
Elo difference: -25.5 +/- 42.5, LOS: 11.9 %, DrawRatio: 42.0 %
150 of 150 games finished.

30 sec + 1
Score of Altair0.34 vs GOOBv1: 40 - 11 - 29 [0.681]
...      Altair0.34 playing White: 20 - 5 - 15  [0.688] 40
...      Altair0.34 playing Black: 20 - 6 - 14  [0.675] 40
...      White vs Black: 26 - 25 - 29  [0.506] 80
Elo difference: 131.9 +/- 63.2, LOS: 100.0 %, DrawRatio: 36.3 %
80 of 80 games finished.

10 sec / 40 moves
Score of Altair0.34 vs Altair0.33: 22 - 19 - 59 [0.515]
...      Altair0.34 playing White: 9 - 11 - 30  [0.480] 50
...      Altair0.34 playing Black: 13 - 8 - 29  [0.550] 50
...      White vs Black: 17 - 24 - 59  [0.465] 100
Elo difference: 10.4 +/- 43.8, LOS: 68.0 %, DrawRatio: 59.0 %
100 of 100 games finished.

Score of Altair0.34 vs Altair0.33: 27 - 21 - 72 [0.525]
...      Altair0.34 playing White: 11 - 13 - 36  [0.483] 60
...      Altair0.34 playing Black: 16 - 8 - 36  [0.567] 60
...      White vs Black: 19 - 29 - 72  [0.458] 120
Elo difference: 17.4 +/- 39.4, LOS: 80.7 %, DrawRatio: 60.0 %
120 of 120 games finished.
```


### Time Management improvements
Time management improvements aren't good for very fast games

```
Score of Altair0.35 vs Altair0.34: 30 - 25 - 45 [0.525]
...      Altair0.35 playing White: 12 - 14 - 24  [0.480] 50
...      Altair0.35 playing Black: 18 - 11 - 21  [0.570] 50
...      White vs Black: 23 - 32 - 45  [0.455] 100
Elo difference: 17.4 +/- 50.8, LOS: 75.0 %, DrawRatio: 45.0 %
100 of 100 games finished.

Score of Altair0.35 vs bienchen.1.0: 32 - 42 - 26 [0.450]
...      Altair0.35 playing White: 13 - 22 - 15  [0.410] 50
...      Altair0.35 playing Black: 19 - 20 - 11  [0.490] 50
...      White vs Black: 33 - 41 - 26  [0.460] 100
Elo difference: -34.9 +/- 59.3, LOS: 12.3 %, DrawRatio: 26.0 %
100 of 100 games finished.
```


### Mobility bug fixes + changes


```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 327 nps 109000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 12 score cp 8 time 7 nodes 1409 nps 201285 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 11 nodes 3274 nps 297636 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 16 nodes 6767 nps 422937 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 18 score cp 32 time 22 nodes 10733 nps 487863 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 22 score cp 7 time 41 nodes 26391 nps 643682 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6 c1f4
info depth 9 seldepth 22 score cp 30 time 63 nodes 41623 nps 660682 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 16 time 220 nodes 124819 nps 567359 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4 d
5e4
info depth 11 seldepth 25 score cp 20 time 463 nodes 315137 nps 680641 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6
info depth 12 seldepth 25 score cp 16 time 759 nodes 530447 nps 698876 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6 f1c4 c8g4 c4f7 e
8f7 f3g5 f7e8 d1g4 c6e5
info depth 13 seldepth 30 score cp 38 time 1399 nodes 980458 nps 700827 pv e2e4 b8c6 g1f3 e7e6 d2d4 g8f6 b1c3 f8b4 d4d5
e6d5 e4d5 d8e7 c1e3 c6e5
info depth 14 seldepth 33 score cp 37 time 2058 nodes 1435664 nps 697601 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 e7e6 c2c4
 d5f6 c1f4 b8c6 b1c3 f8b4
info depth 15 seldepth 33 score cp 22 time 6546 nodes 4635225 nps 708100 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
info depth 16 seldepth 38 score cp 17 time 18069 nodes 11315426 nps 626234 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4
c6 d7c6 d1d8 e8d8 f1d3 f8b4 b1c3 b4c3 b2c3 h8e8 c1g5
info depth 16 seldepth 38 score cp 17 time 45001 nodes 29116419 nps 647017 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4
c6 d7c6 d1d8 e8d8 f1d3 f8b4 b1c3 b4c3 b2c3 h8e8 c1g5
bestmove e2e4

Score of Altair0.36 vs Altair0.35: 46 - 33 - 71 [0.543]
...      Altair0.36 playing White: 21 - 16 - 38  [0.533] 75
...      Altair0.36 playing Black: 25 - 17 - 33  [0.553] 75
...      White vs Black: 38 - 41 - 71  [0.490] 150
Elo difference: 30.2 +/- 40.5, LOS: 92.8 %, DrawRatio: 47.3 %
150 of 150 games finished.

1 min + 0
Score of Altair0.36 vs sofcheck_amd64-popcnt_windows: 32 - 51 - 37 [0.421]
...      Altair0.36 playing White: 13 - 27 - 20  [0.383] 60
...      Altair0.36 playing Black: 19 - 24 - 17  [0.458] 60
...      White vs Black: 37 - 46 - 37  [0.463] 120
Elo difference: -55.5 +/- 52.4, LOS: 1.9 %, DrawRatio: 30.8 %
120 of 120 games finished.

5sec + 0.05
Score of Altair0.36 vs bienchen.1.0: 38 - 75 - 45 [0.383]
...      Altair0.36 playing White: 15 - 43 - 21  [0.323] 79
...      Altair0.36 playing Black: 23 - 32 - 24  [0.443] 79
...      White vs Black: 47 - 66 - 45  [0.440] 158
Elo difference: -82.9 +/- 46.8, LOS: 0.0 %, DrawRatio: 28.5 %
```


### (IID) Different IID idea + Reducing in non-pv nodes

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 2 nodes 109 nps 54500 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 4 nodes 327 nps 81750 pv b1c3 b8c6 g1f3
info depth 4 seldepth 12 score cp 8 time 6 nodes 1409 nps 234833 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 8 nodes 3274 nps 409250 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 13 nodes 6767 nps 520538 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 18 score cp 32 time 19 nodes 10733 nps 564894 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 22 score cp 7 time 35 nodes 24375 nps 696428 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6 c1f4
info depth 9 seldepth 22 score cp 30 time 51 nodes 39537 nps 775235 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 16 time 132 nodes 116914 nps 885712 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4
info depth 11 seldepth 25 score cp 22 time 280 nodes 258875 nps 924553 pv e2e4 d7d5 e4e5 d5d4 d2d3 b8c6 g1f3 e7e6 b1d2 f
8b4 f1e2
info depth 12 seldepth 25 score cp 22 time 354 nodes 332542 nps 939384 pv e2e4 d7d5 e4e5 d5d4 d2d3
info depth 13 seldepth 28 score cp 27 time 518 nodes 490496 nps 946903 pv e2e4 d7d5 e4e5 d5d4 d2d3 b8c6 g1f3 e7e6 b1d2 g
8e7 d2e4 e7d5 c1g5
info depth 14 seldepth 28 score cp 27 time 811 nodes 770365 nps 949895 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6 d2d3
info depth 15 seldepth 28 score cp 43 time 1721 nodes 1644719 nps 955676 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6 f1c4 e7e6 e1g1
 g8e7 d2d3 e7d5 c1g5 f8e7
info depth 16 seldepth 31 score cp 40 time 3255 nodes 3121653 nps 959033 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6 f1c4 c8f5 e1g1
 e7e6 d2d3 g8e7 c1g5 h7h6 g5f4
info depth 17 seldepth 31 score cp 34 time 5739 nodes 5522147 nps 962214 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3
 e7e6 g1f3 f8b4 f1e2 e8g8 e1g1 b8c6 c1f4
info depth 17 seldepth 37 score cp 34 time 44999 nodes 40845329 nps 907694 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1
c3 e7e6 g1f3 f8b4 f1e2 e8g8 e1g1 b8c6 c1f4
bestmove e2e4

Score of Altair0.37 vs Altair0.36: 46 - 32 - 72 [0.547]
...      Altair0.37 playing White: 19 - 17 - 39  [0.513] 75
...      Altair0.37 playing Black: 27 - 15 - 33  [0.580] 75
...      White vs Black: 34 - 44 - 72  [0.467] 150
Elo difference: 32.5 +/- 40.2, LOS: 94.4 %, DrawRatio: 48.0 %
150 of 150 games finished.

Score of Altair0.37 vs bienchen.1.0: 50 - 69 - 31 [0.437]
...      Altair0.37 playing White: 22 - 38 - 15  [0.393] 75
...      Altair0.37 playing Black: 28 - 31 - 16  [0.480] 75
...      White vs Black: 53 - 66 - 31  [0.457] 150
Elo difference: -44.2 +/- 50.1, LOS: 4.1 %, DrawRatio: 20.7 %
150 of 150 games finished.

1 min + 0
Score of Altair0.37 vs bienchen.1.0: 33 - 59 - 28 [0.392]
...      Altair0.37 playing White: 19 - 27 - 14  [0.433] 60
...      Altair0.37 playing Black: 14 - 32 - 14  [0.350] 60
...      White vs Black: 51 - 41 - 28  [0.542] 120
Elo difference: -76.5 +/- 55.8, LOS: 0.3 %, DrawRatio: 23.3 %
120 of 120 games finished.

Score of Altair0.37 vs Vice10-64: 94 - 28 - 28 [0.720]
...      Altair0.37 playing White: 45 - 17 - 13  [0.687] 75
...      Altair0.37 playing Black: 49 - 11 - 15  [0.753] 75
...      White vs Black: 56 - 66 - 28  [0.467] 150
Elo difference: 164.1 +/- 54.9, LOS: 100.0 %, DrawRatio: 18.7 %
150 of 150 games finished.

5 sec + 0.05
Score of Altair0.37 vs sofcheck_amd64-popcnt_windows: 21 - 59 - 20 [0.310]
...      Altair0.37 playing White: 10 - 29 - 11  [0.310] 50
...      Altair0.37 playing Black: 11 - 30 - 9  [0.310] 50
...      White vs Black: 40 - 40 - 20  [0.500] 100
Elo difference: -139.0 +/- 65.4, LOS: 0.0 %, DrawRatio: 20.0 %
100 of 100 games finished.
```


### Changing History Heuristic Table Format


```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 327 nps 109000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 12 score cp 8 time 6 nodes 1411 nps 235166 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 10 nodes 3267 nps 326700 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 18 nodes 7114 nps 395222 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 18 score cp 32 time 27 nodes 12035 nps 445740 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 22 score cp 7 time 51 nodes 27264 nps 534588 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4
info depth 9 seldepth 25 score cp 30 time 69 nodes 42496 nps 615884 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 17 time 184 nodes 151885 nps 825461 pv e2e4 d7d5 e4d5 g8f6 d2d4 e7e6 g1f3 f6d5 f1b5 b
8c6 e1g1
info depth 11 seldepth 25 score cp 26 time 269 nodes 228442 nps 849226 pv e2e4 d7d5 e4d5 g8f6 d2d4 c8g4 g1f3 d8d5 b1c3 d
5e6 c1e3 b8c6
info depth 12 seldepth 25 score cp 24 time 386 nodes 337344 nps 873948 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 b8c6 c2c4 d
5f6 b1c3 c8f5
info depth 13 seldepth 27 score cp 28 time 1111 nodes 1034084 nps 930768 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 b4c3 b2c3 d7c6
info depth 14 seldepth 27 score cp 36 time 1363 nodes 1284967 nps 942749 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info depth 15 seldepth 29 score cp 21 time 2138 nodes 2021603 nps 945557 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info depth 16 seldepth 30 score cp 17 time 6090 nodes 5723627 nps 939840 pv b1c3 d7d5 d2d4 b8c6 e2e4 g8f6 e4e5 f6e4 c3e4
 d5e4 g1e2 c8g4 c2c3 e7e6 d1b3 a8b8
info depth 17 seldepth 32 score cp 15 time 8201 nodes 7694421 nps 938229 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 d1d3 b8c6 f3e5
 c6b4 d3b5 c7c6 b5a4 f6d7 c1f4 d7e5 f4e5 d8b6
info depth 17 seldepth 39 score cp 15 time 45012 nodes 40337409 nps 896147 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 d1d3 b8c6 f3
e5 c6b4 d3b5 c7c6 b5a4 f6d7 c1f4 d7e5 f4e5 d8b6
bestmove b1c3

Score of Altair0.38 vs Altair0.37: 59 - 55 - 86 [0.510]
...      Altair0.38 playing White: 28 - 26 - 46  [0.510] 100
...      Altair0.38 playing Black: 31 - 29 - 40  [0.510] 100
...      White vs Black: 57 - 57 - 86  [0.500] 200
Elo difference: 6.9 +/- 36.4, LOS: 64.6 %, DrawRatio: 43.0 %
200 of 200 games finished.
```


### LMR changes

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 327 nps 109000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 12 score cp 8 time 5 nodes 1411 nps 282200 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 8 nodes 3267 nps 408375 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 13 nodes 7114 nps 547230 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 18 score cp 32 time 20 nodes 12035 nps 601750 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 22 score cp 7 time 36 nodes 27264 nps 757333 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4
info depth 9 seldepth 25 score cp 30 time 53 nodes 42496 nps 801811 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 17 time 174 nodes 151885 nps 872902 pv e2e4 d7d5 e4d5 g8f6 d2d4 e7e6 g1f3 f6d5 f1b5 b
8c6 e1g1
info depth 11 seldepth 25 score cp 26 time 255 nodes 228442 nps 895850 pv e2e4 d7d5 e4d5 g8f6 d2d4 c8g4 g1f3 d8d5 b1c3 d
5e6 c1e3 b8c6
info depth 12 seldepth 25 score cp 24 time 368 nodes 337344 nps 916695 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 b8c6 c2c4 d
5f6 b1c3 c8f5
info depth 13 seldepth 27 score cp 28 time 1157 nodes 1034084 nps 893763 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 b4c3 b2c3 d7c6
info depth 14 seldepth 27 score cp 36 time 1410 nodes 1284967 nps 911324 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info depth 15 seldepth 29 score cp 21 time 2175 nodes 2021603 nps 929472 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info depth 16 seldepth 30 score cp 17 time 6266 nodes 5723627 nps 913441 pv b1c3 d7d5 d2d4 b8c6 e2e4 g8f6 e4e5 f6e4 c3e4
 d5e4 g1e2 c8g4 c2c3 e7e6 d1b3 a8b8
info depth 17 seldepth 32 score cp 15 time 8436 nodes 7694421 nps 912093 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 d1d3 b8c6 f3e5
 c6b4 d3b5 c7c6 b5a4 f6d7 c1f4 d7e5 f4e5 d8b6
info depth 17 seldepth 38 score cp 15 time 45005 nodes 39796737 nps 884273 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 d1d3 b8c6 f3
e5 c6b4 d3b5 c7c6 b5a4 f6d7 c1f4 d7e5 f4e5 d8b6
bestmove b1c3

Score of Altair0.39 vs Altair0.38: 57 - 56 - 87 [0.502]
...      Altair0.39 playing White: 24 - 30 - 46  [0.470] 100
...      Altair0.39 playing Black: 33 - 26 - 41  [0.535] 100
...      White vs Black: 50 - 63 - 87  [0.468] 200
Elo difference: 1.7 +/- 36.3, LOS: 53.7 %, DrawRatio: 43.5 %
200 of 200 games finished.


Score of Altair0.39 vs sofcheck_amd64-popcnt_windows: 22 - 52 - 26 [0.350]
...      Altair0.39 playing White: 10 - 24 - 16  [0.360] 50
...      Altair0.39 playing Black: 12 - 28 - 10  [0.340] 50
...      White vs Black: 38 - 36 - 26  [0.510] 100
Elo difference: -107.5 +/- 61.0, LOS: 0.0 %, DrawRatio: 26.0 %
100 of 100 games finished.
```


### Changing Counter moves table format


```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 327 nps 109000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 12 score cp 8 time 5 nodes 1411 nps 282200 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 8 nodes 3267 nps 408375 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 13 nodes 7114 nps 547230 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 18 score cp 32 time 20 nodes 12035 nps 601750 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 22 score cp 7 time 37 nodes 27264 nps 736864 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4
info depth 9 seldepth 25 score cp 30 time 53 nodes 42526 nps 802377 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 21 time 212 nodes 191594 nps 903745 pv e2e4 d7d5 e4e5 b8c6 d2d4 c8f5
info depth 11 seldepth 25 score cp 26 time 327 nodes 297879 nps 910944 pv e2e4 d7d5 e4d5 g8f6 d2d4 c8g4 g1f3 d8d5 b1c3 d
5e6 c1e3 b8c6
info depth 12 seldepth 25 score cp 24 time 414 nodes 384488 nps 928714 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 b8c6 c2c4 d
5f6 b1c3 c8f5
info depth 13 seldepth 27 score cp 38 time 974 nodes 925012 nps 949704 pv e2e4 e7e6 g1f3 b8c6
info depth 14 seldepth 30 score cp 38 time 1200 nodes 1150173 nps 958477 pv e2e4 e7e6 g1f3 b8c6 d2d4 g8f6 b1c3 f8b4
info depth 15 seldepth 30 score cp 34 time 2269 nodes 2182074 nps 961689 pv e2e4 e7e6 g1f3 d7d5 e4e5 d5d4 f1c4 b8c6 d2d3
 g8e7 e1g1 e7g6 c1g5 f8e7 g5e7
info depth 16 seldepth 30 score cp 34 time 3216 nodes 3117949 nps 969511 pv e2e4 e7e6 g1f3 d7d5 e4e5 d5d4 f1c4 b8c6 e1g1
 g8e7 d2d3
info depth 17 seldepth 30 score cp 34 time 4474 nodes 4315429 nps 964557 pv e2e4 e7e6 g1f3 d7d5 e4e5 d5d4 f1c4 b8c6 e1g1
 g8e7 d2d3 e7g6 c1g5 f8e7 g5e7 d8e7
info depth 18 seldepth 35 score cp 34 time 6923 nodes 6602266 nps 953671 pv e2e4 e7e6 g1f3 d7d5 e4e5
info depth 19 seldepth 36 score cp 35 time 23141 nodes 21113326 nps 912377 pv e2e4 b8c6 d2d4 d7d5 b1c3 g8f6 e4e5 f6e4 c3
e4 d5e4 c2c3
info depth 19 seldepth 42 score cp 35 time 45002 nodes 40953882 nps 910045 pv e2e4 b8c6 d2d4 d7d5 b1c3 g8f6 e4e5 f6e4 c3
e4 d5e4 c2c3
bestmove e2e4

Score of Altair0.40 vs Altair0.39: 63 - 56 - 81 [0.517]
...      Altair0.40 playing White: 32 - 25 - 43  [0.535] 100
...      Altair0.40 playing Black: 31 - 31 - 38  [0.500] 100
...      White vs Black: 63 - 56 - 81  [0.517] 200
Elo difference: 12.2 +/- 37.2, LOS: 73.9 %, DrawRatio: 40.5 %
200 of 200 games finished.

Score of Altair0.40 vs sofcheck_amd64-popcnt_windows: 31 - 74 - 45 [0.357]
...      Altair0.40 playing White: 13 - 40 - 22  [0.320] 75
...      Altair0.40 playing Black: 18 - 34 - 23  [0.393] 75
...      White vs Black: 47 - 58 - 45  [0.463] 150
Elo difference: -102.5 +/- 47.9, LOS: 0.0 %, DrawRatio: 30.0 %
150 of 150 games finished.

Score of Altair0.40 vs bienchen.1.0: 35 - 38 - 27 [0.485]
...      Altair0.40 playing White: 21 - 16 - 13  [0.550] 50
...      Altair0.40 playing Black: 14 - 22 - 14  [0.420] 50
...      White vs Black: 43 - 30 - 27  [0.565] 100
Elo difference: -10.4 +/- 58.7, LOS: 36.3 %, DrawRatio: 27.0 %
100 of 100 games finished.

Score of Altair0.40 vs Vice10-64: 74 - 12 - 14 [0.810]
...      Altair0.40 playing White: 35 - 6 - 9  [0.790] 50
...      Altair0.40 playing Black: 39 - 6 - 5  [0.830] 50
...      White vs Black: 41 - 45 - 14  [0.480] 100
Elo difference: 251.9 +/- 79.0, LOS: 100.0 %, DrawRatio: 14.0 %
100 of 100 games finished.

Score of Altair0.40 vs Vice10-64: 74 - 12 - 14 [0.810]
...      Altair0.40 playing White: 35 - 6 - 9  [0.790] 50
...      Altair0.40 playing Black: 39 - 6 - 5  [0.830] 50
...      White vs Black: 41 - 45 - 14  [0.480] 100
Elo difference: 251.9 +/- 79.0, LOS: 100.0 %, DrawRatio: 14.0 %
100 of 100 games finished.

1 min
Score of Altair0.40 vs bienchen.1.0: 9 - 23 - 10 [0.333]
...      Altair0.40 playing White: 3 - 11 - 7  [0.310] 21
...      Altair0.40 playing Black: 6 - 12 - 3  [0.357] 21
...      White vs Black: 15 - 17 - 10  [0.476] 42
Elo difference: -120.4 +/- 98.7, LOS: 0.7 %, DrawRatio: 23.8 %
```


### LMR less aggressive

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 2 nodes 109 nps 54500 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 327 nps 109000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 12 score cp 8 time 6 nodes 1433 nps 238833 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 9 nodes 3387 nps 376333 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 13 nodes 7054 nps 542615 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 18 score cp 32 time 20 nodes 12115 nps 605750 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 c1f4
info depth 8 seldepth 22 score cp 7 time 49 nodes 39896 nps 814204 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6
info depth 9 seldepth 25 score cp 29 time 65 nodes 54544 nps 839138 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 17 time 140 nodes 126661 nps 904721 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4 d
5e4
info depth 11 seldepth 25 score cp 22 time 317 nodes 295682 nps 932750 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6
info depth 12 seldepth 25 score cp 16 time 422 nodes 399653 nps 947045 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6 f1c4 c8g4 c4f7 e
8f7 f3g5 f7e8 d1g4 c6e5
info depth 13 seldepth 27 score cp 16 time 963 nodes 916416 nps 951626 pv e2e4 d7d5 e4e5 d5d4 g1f3
info depth 14 seldepth 28 score cp 32 time 1818 nodes 1730595 nps 951922 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 g1f3 b8c6 d2d4
 f8b4 f1b5 g8e7 a2a3 b4c3 b2c3
info depth 15 seldepth 30 score cp 21 time 3480 nodes 3323400 nps 955000 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6
info depth 16 seldepth 30 score cp 21 time 4449 nodes 4247383 nps 954682 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6
info depth 17 seldepth 31 score cp 21 time 6597 nodes 6255586 nps 948247 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4

info depth 18 seldepth 35 score cp 22 time 15565 nodes 14547643 nps 934638 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
info depth 18 seldepth 38 score cp 22 time 45001 nodes 41005064 nps 911203 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
bestmove e2e4

10 sec
Score of Altair0.41 vs Altair0.40: 42 - 36 - 72 [0.520]
...      Altair0.41 playing White: 23 - 17 - 35  [0.540] 75
...      Altair0.41 playing Black: 19 - 19 - 37  [0.500] 75
...      White vs Black: 42 - 36 - 72  [0.520] 150
Elo difference: 13.9 +/- 40.2, LOS: 75.2 %, DrawRatio: 48.0 %
150 of 150 games finished.

1 min
Score of Altair0.41 vs bienchen.1.0: 39 - 52 - 29 [0.446]
...      Altair0.41 playing White: 21 - 25 - 14  [0.467] 60
...      Altair0.41 playing Black: 18 - 27 - 15  [0.425] 60
...      White vs Black: 48 - 43 - 29  [0.521] 120
Elo difference: -37.8 +/- 54.7, LOS: 8.6 %, DrawRatio: 24.2 %
120 of 120 games finished.
```


### TT probing after qsearch

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 327 nps 109000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 12 score cp 8 time 6 nodes 1433 nps 238833 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 9 nodes 3387 nps 376333 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 14 nodes 7054 nps 503857 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 18 score cp 32 time 20 nodes 12115 nps 605750 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 c1f4
info depth 8 seldepth 22 score cp 7 time 50 nodes 39896 nps 797920 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6
info depth 9 seldepth 25 score cp 29 time 66 nodes 54544 nps 826424 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 17 time 146 nodes 126661 nps 867541 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4 d
5e4
info depth 11 seldepth 25 score cp 22 time 404 nodes 295682 nps 731886 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6
info depth 12 seldepth 25 score cp 16 time 511 nodes 399653 nps 782099 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6 f1c4 c8g4 c4f7 e
8f7 f3g5 f7e8 d1g4 c6e5
info depth 13 seldepth 27 score cp 16 time 1052 nodes 916416 nps 871117 pv e2e4 d7d5 e4e5 d5d4 g1f3
info depth 14 seldepth 28 score cp 32 time 1906 nodes 1730595 nps 907972 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 g1f3 b8c6 d2d4
 f8b4 f1b5 g8e7 a2a3 b4c3 b2c3
info depth 15 seldepth 30 score cp 21 time 3581 nodes 3323400 nps 928064 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6
info depth 16 seldepth 30 score cp 21 time 4551 nodes 4247383 nps 933285 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6
info depth 17 seldepth 31 score cp 21 time 6714 nodes 6255586 nps 931722 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4

info depth 18 seldepth 35 score cp 22 time 16461 nodes 14547643 nps 883764 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
info depth 18 seldepth 38 score cp 22 time 45001 nodes 35270671 nps 783775 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
bestmove e2e4

Score of Altair0.42 vs Altair0.41: 26 - 26 - 48 [0.500]
...      Altair0.42 playing White: 12 - 15 - 23  [0.470] 50
...      Altair0.42 playing Black: 14 - 11 - 25  [0.530] 50
...      White vs Black: 23 - 29 - 48  [0.470] 100
Elo difference: 0.0 +/- 49.4, LOS: 50.0 %, DrawRatio: 48.0 %
100 of 100 games finished.
```


### Move Ordering bug fixes

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 2 nodes 109 nps 54500 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 4 nodes 327 nps 81750 pv b1c3 b8c6 g1f3
info depth 4 seldepth 10 score cp 8 time 6 nodes 1455 nps 242500 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 8 nodes 3314 nps 414250 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 13 nodes 6718 nps 516769 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 19 score cp 32 time 19 nodes 11587 nps 609842 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 22 score cp 7 time 39 nodes 29864 nps 765743 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4
info depth 9 seldepth 25 score cp 29 time 62 nodes 47447 nps 765274 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 25 time 151 nodes 131595 nps 871490 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1f3 g8f6 b1c3 d
5d6
info depth 11 seldepth 25 score cp 16 time 292 nodes 263086 nps 900979 pv e2e4 d7d5 e4e5 d5d4 f1b5 c8d7 b5c4 b8c6 g1f3 d
7g4 c4f7 e8f7 f3g5 f7e8
info depth 12 seldepth 25 score cp 16 time 418 nodes 383693 nps 917925 pv e2e4 d7d5 e4e5 d5d4 f1b5 c8d7 b5c4
info depth 13 seldepth 27 score cp 21 time 656 nodes 609955 nps 929809 pv e2e4 d7d5 e4e5 d5d4 f1c4 b8c6 g1f3 c8g4 c4f7 e
8f7 f3g5 f7e8 d1g4 c6e5 g4h5 g7g6
info depth 14 seldepth 29 score cp 32 time 1374 nodes 1299411 nps 945713 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 g1f3 d5d4 d1e2
 g8e7 c3e4 b8c6 d2d3 c8g4 c1f4
info depth 15 seldepth 30 score cp 37 time 2026 nodes 1935060 nps 955113 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 g8f6 b1c3
 b8c6
info depth 16 seldepth 34 score cp 36 time 3611 nodes 3436173 nps 951584 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 g8f6 b1c3
 b8c6 f1b5 f8e7
info depth 17 seldepth 34 score cp 36 time 5371 nodes 5081004 nps 946007 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 g8f6 b1c3

info depth 18 seldepth 38 score cp 31 time 18099 nodes 15879129 nps 877348 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 b8c6
info depth 18 seldepth 38 score cp 31 time 44999 nodes 33396744 nps 742166 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 b8c6
bestmove e2e4

Score of Altair0.43 vs Altair0.42: 48 - 36 - 66 [0.540]
...      Altair0.43 playing White: 27 - 18 - 30  [0.560] 75
...      Altair0.43 playing Black: 21 - 18 - 36  [0.520] 75
...      White vs Black: 45 - 39 - 66  [0.520] 150
Elo difference: 27.9 +/- 41.8, LOS: 90.5 %, DrawRatio: 44.0 %
150 of 150 games finished.

Score of Altair0.43 vs bienchen.1.0: 63 - 58 - 29 [0.517]
...      Altair0.43 playing White: 29 - 28 - 18  [0.507] 75
...      Altair0.43 playing Black: 34 - 30 - 11  [0.527] 75
...      White vs Black: 59 - 62 - 29  [0.490] 150
Elo difference: 11.6 +/- 50.2, LOS: 67.5 %, DrawRatio: 19.3 %
150 of 150 games finished.
```


### UNUSED CHANGE (Updating things at the end of the move loop)

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 2 nodes 109 nps 54500 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 4 nodes 314 nps 78500 pv b1c3 b8c6 g1f3
info depth 4 seldepth 8 score cp 8 time 7 nodes 1236 nps 176571 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 10 nodes 2319 nps 231900 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 16 nodes 6323 nps 395187 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info depth 7 seldepth 17 score cp 32 time 27 nodes 15750 nps 583333 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info depth 8 seldepth 24 score cp 17 time 61 nodes 47295 nps 775327 pv e2e4 b8c6 b1c3 g8f6
info depth 9 seldepth 25 score cp 29 time 86 nodes 71745 nps 834244 pv b1c3 g8f6 d2d4 d7d5 g1f3 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 15 time 185 nodes 168597 nps 911335 pv b1c3 d7d5 e2e4 d5e4 c3e4 g8f6 e4f6 e7f6 d2d4 d
8e7 g1e2 b8c6
info depth 11 seldepth 26 score cp 21 time 262 nodes 238387 nps 909874 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 d1d3 e7e6 e2e4 f
8b4 e4e5
info depth 12 seldepth 26 score cp 31 time 440 nodes 409166 nps 929922 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info depth 13 seldepth 30 score cp 47 time 1637 nodes 1542176 nps 942074 pv e2e4 b8c6 d2d4 e7e6 b1c3 d7d5 e4e5 g8e7 g1f3
 e7f5 c1f4 f8b4 f1b5
info depth 14 seldepth 30 score cp 37 time 2363 nodes 2221326 nps 940044 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1f3 g8f6 b1c3
 d5d6 d4d5 c6b4 c3b5 d6d5
info depth 15 seldepth 32 score cp 21 time 4790 nodes 4542789 nps 948390 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info depth 16 seldepth 32 score cp 24 time 6936 nodes 6377695 nps 919506 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6
 d7c6 d1d8 e8d8 f1d3 f8b4 c1d2 b4d6 b1c3 h8e8
info depth 17 seldepth 34 score cp 17 time 13852 nodes 12509554 nps 903086 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
info depth 17 seldepth 36 score cp 17 time 45004 nodes 35180545 nps 781720 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
bestmove e2e4

Score of Altair0.44 vs Altair0.43: 37 - 48 - 65 [0.463]
...      Altair0.44 playing White: 21 - 21 - 33  [0.500] 75
...      Altair0.44 playing Black: 16 - 27 - 32  [0.427] 75
...      White vs Black: 48 - 37 - 65  [0.537] 150
Elo difference: -25.5 +/- 42.0, LOS: 11.6 %, DrawRatio: 43.3 %
150 of 150 games finished.

Score of Altair0.44 vs bienchen.1.0: 52 - 49 - 30 [0.511]
...      Altair0.44 playing White: 28 - 24 - 14  [0.530] 66
...      Altair0.44 playing Black: 24 - 25 - 16  [0.492] 65
...      White vs Black: 53 - 48 - 30  [0.519] 131
Elo difference: 8.0 +/- 52.6, LOS: 61.7 %, DrawRatio: 22.9 %
131 of 500 games finished.
```


### Capture History

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 2 nodes 109 nps 54500 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 327 nps 109000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 10 score cp 8 time 5 nodes 1444 nps 288800 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 12 score cp 52 time 8 nodes 3294 nps 411750 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 14 score cp 7 time 12 nodes 6533 nps 544416 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 18 score cp 32 time 19 nodes 11696 nps 615578 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 c1f4
info depth 8 seldepth 24 score cp 7 time 60 nodes 50099 nps 834983 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6
info depth 9 seldepth 25 score cp 30 time 91 nodes 78089 nps 858120 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 13 time 184 nodes 167871 nps 912342 pv b1c3 d7d5 g1f3 g8f6 d2d4
info depth 11 seldepth 25 score cp 14 time 255 nodes 236487 nps 927400 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1g5 c8f5 e2e3 e
7e6 f1b5
info depth 12 seldepth 30 score cp 21 time 411 nodes 382636 nps 930987 pv b1c3 d7d5 d2d4 b8c6 g1f3 g8f6
info depth 13 seldepth 30 score cp 32 time 831 nodes 783063 nps 942314 pv b1c3 g8f6 e2e4 b8c6 d2d4 d7d5 e4e5 f6e4 c3e4 d
5e4 g1e2 c8g4 c1e3
info depth 14 seldepth 31 score cp 37 time 2345 nodes 2206429 nps 940907 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3
 e7e6 g1f3 b8c6 c1f4 f8b4
info depth 15 seldepth 31 score cp 37 time 2793 nodes 2637036 nps 944158 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 b1c3

info depth 16 seldepth 38 score cp 31 time 5053 nodes 4743736 nps 938795 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 b8c6 b1c3

info depth 17 seldepth 38 score cp 31 time 7109 nodes 6635587 nps 933406 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 g8f6 b1c3
 b8c6
info depth 18 seldepth 38 score cp 34 time 12849 nodes 11207050 nps 872211 pv e2e4 e7e6 d2d4 d7d5 b1c3 b8c6 e4e5 f8b4 g1
e2 d8h4 d1d3 g8e7 a2a3 b4c3 d3c3 e8g8 c1f4 e7g6 f4e3
info depth 18 seldepth 38 score cp 34 time 45002 nodes 38707235 nps 860122 pv e2e4 e7e6 d2d4 d7d5 b1c3 b8c6 e4e5 f8b4 g1
e2 d8h4 d1d3 g8e7 a2a3 b4c3 d3c3 e8g8 c1f4 e7g6 f4e3
bestmove e2e4

Score of Altair0.44 vs Altair0.43: 45 - 44 - 61 [0.503]
...      Altair0.44 playing White: 24 - 23 - 28  [0.507] 75
...      Altair0.44 playing Black: 21 - 21 - 33  [0.500] 75
...      White vs Black: 45 - 44 - 61  [0.503] 150
Elo difference: 2.3 +/- 43.0, LOS: 54.2 %, DrawRatio: 40.7 %
150 of 150 games finished.
```


### History Gravity

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info depth 4 seldepth 8 score cp 8 time 5 nodes 954 nps 190800 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 10 score cp 52 time 7 nodes 2082 nps 297428 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 12 score cp 7 time 10 nodes 4819 nps 481900 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 17 score cp 32 time 18 nodes 11144 nps 619111 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 24 score cp 17 time 57 nodes 47144 nps 827087 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5
info depth 9 seldepth 25 score cp 30 time 85 nodes 73530 nps 865058 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 16 time 188 nodes 167693 nps 891984 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info depth 11 seldepth 26 score cp 18 time 285 nodes 258617 nps 907428 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c8g4 f1b5 a
7a6 b5c6 b7c6
info depth 12 seldepth 26 score cp 13 time 583 nodes 537949 nps 922725 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 c1g5 c8g4 e2e3 e
7e6 h2h3 g4f5
info depth 13 seldepth 27 score cp 21 time 793 nodes 724389 nps 913479 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 f6e4 f1d3 c
8f5 e1g1 e4c3 b2c3
info depth 14 seldepth 27 score cp 27 time 1973 nodes 1840459 nps 932822 pv e2e4 d7d5 e4e5 c7c5 f1b5 b8c6 b5c6 b7c6 d2d3
 e7e6 g1f3 g8e7 e1g1 d5d4
info depth 15 seldepth 31 score cp 21 time 3259 nodes 3065552 nps 940641 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info depth 16 seldepth 31 score cp 11 time 4798 nodes 4517872 nps 941615 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 b4c3 b2c3 h8e8
info depth 17 seldepth 31 score cp 11 time 7654 nodes 7201064 nps 940823 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6
info depth 18 seldepth 35 score cp 32 time 14426 nodes 13346201 nps 925149 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4 b8c6 c2
c3 g8f6 e4f6 d8f6 g1f3 e6e5 c1g5 f6d6 d4e5 c6e5 f3e5
info depth 19 seldepth 35 score cp 33 time 18923 nodes 17627099 nps 931517 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 g1f3 b8c6 f1
b5 c5d4 f3d4 g8e7 b1c3
info depth 20 seldepth 35 score cp 33 time 25747 nodes 24045962 nps 933932 pv e2e4 e7e6
info depth 20 seldepth 38 score cp 33 time 45000 nodes 42170397 nps 937119 pv e2e4 e7e6
bestmove e2e4

On Mac M1
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 0 nodes 109 nps 1090000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 0 nodes 302 nps 3020000 pv b1c3 b8c6 g1f3
info depth 4 seldepth 8 score cp 8 time 1 nodes 954 nps 954000 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 10 score cp 52 time 3 nodes 2082 nps 694000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 12 score cp 7 time 8 nodes 4849 nps 606125 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 17 score cp 32 time 18 nodes 11193 nps 621833 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info depth 8 seldepth 24 score cp 17 time 61 nodes 48211 nps 790344 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5
info depth 9 seldepth 25 score cp 30 time 78 nodes 71758 nps 919974 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 17 time 107 nodes 115878 nps 1082971 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 c3e4 d5e4
info depth 11 seldepth 26 score cp 21 time 174 nodes 221043 nps 1270362 pv b1c3 g8f6 e2e4 b8c6 g1f3 d7d5 e4e5 f6e4 f1d3 c8f5 e1g1
info depth 12 seldepth 26 score cp 20 time 292 nodes 405895 nps 1390051 pv b1c3 d7d5 d2d4 b8c6 g1f3 g8f6
info depth 13 seldepth 27 score cp 31 time 528 nodes 775522 nps 1468791 pv b1c3 d7d5 d2d4 b8c6 g1f3 g8f6 e2e3 e7e6 f1b5 f8b4 f3e5 e8g8 e5c6
info depth 14 seldepth 36 score cp 21 time 1083 nodes 1619500 nps 1495383 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 f1c4 b8c6 e1g1 c8e6 f3g5 d8d6 g5e6 d6e6
info depth 15 seldepth 36 score cp 21 time 1898 nodes 2862495 nps 1508163 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info depth 16 seldepth 38 score cp 11 time 2918 nodes 4421013 nps 1515083 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d8 e8d8 c1g5
info depth 17 seldepth 38 score cp 11 time 3981 nodes 6048955 nps 1519456 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4 f8b4
info depth 18 seldepth 38 score cp 17 time 5709 nodes 8709584 nps 1525588 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d8 e8d8 f1d3 h8e8 c1g5
info depth 19 seldepth 38 score cp 17 time 7453 nodes 11445856 nps 1535738 pv e2e4 e7e5 b1c3 g8f6 g1f3
info depth 20 seldepth 38 score cp 17 time 10564 nodes 16321505 nps 1545011 pv e2e4 e7e5
info depth 21 seldepth 38 score cp 22 time 20428 nodes 31642560 nps 1548979 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 e5d4 f3d4
info depth 22 seldepth 38 score cp 40 time 29446 nodes 45644489 nps 1550108 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5f3 f6e4 b1c3 e4c3 d2c3 f8e7 f1b5 c7c6 b5d3 e8g8 e1g1 b8d7 f1e1 d7c5 c1f4 c8e6 f3d4
info depth 22 seldepth 41 score cp 40 time 45000 nodes 69787666 nps 1550837 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5f3 f6e4 b1c3 e4c3 d2c3 f8e7 f1b5 c7c6 b5d3 e8g8 e1g1 b8d7 f1e1 d7c5 c1f4 c8e6 f3d4
bestmove e2e4

Score of Altair0.45 vs Altair0.44: 43 - 32 - 75 [0.537]
...      Altair0.45 playing White: 26 - 17 - 32  [0.560] 75
...      Altair0.45 playing Black: 17 - 15 - 43  [0.513] 75
...      White vs Black: 41 - 34 - 75  [0.523] 150
Elo difference: 25.5 +/- 39.4, LOS: 89.8 %, DrawRatio: 50.0 %
150 of 150 games finished.

Score of Altair0.45 vs Altair0.44: 4 - 0 - 16 [0.600]
...      Altair0.45 playing White: 3 - 0 - 7  [0.650] 10
...      Altair0.45 playing Black: 1 - 0 - 9  [0.550] 10
...      White vs Black: 3 - 1 - 16  [0.550] 20
Elo difference: 70.4 +/- 64.2, LOS: 97.7 %, DrawRatio: 80.0 %

Score of Altair0.45 vs bienchen.1.0: 113 - 112 - 77 [0.502]
...      Altair0.45 playing White: 57 - 54 - 40  [0.510] 151
...      Altair0.45 playing Black: 56 - 58 - 37  [0.493] 151
...      White vs Black: 115 - 110 - 77  [0.508] 302
Elo difference: 1.2 +/- 33.9, LOS: 52.7 %, DrawRatio: 25.5 %

1 min
Score of Altair0.45 vs sofcheck_amd64-popcnt_windows: 32 - 51 - 37 [0.421]
...      Altair0.45 playing White: 16 - 27 - 17  [0.408] 60
...      Altair0.45 playing Black: 16 - 24 - 20  [0.433] 60
...      White vs Black: 40 - 43 - 37  [0.487] 120
Elo difference: -55.5 +/- 52.4, LOS: 1.9 %, DrawRatio: 30.8 %
120 of 120 games finished.
```


### Small Changes
Lower RFP margin by 10, and do not do mate distance pruning at root of search

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info depth 4 seldepth 8 score cp 8 time 5 nodes 953 nps 190600 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 10 score cp 52 time 7 nodes 2080 nps 297142 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 12 score cp 7 time 10 nodes 4677 nps 467700 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 20 score cp 32 time 18 nodes 11506 nps 639222 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info depth 8 seldepth 24 score cp 7 time 52 nodes 42459 nps 816519 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info depth 9 seldepth 24 score cp 30 time 72 nodes 61311 nps 851541 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 20 time 120 nodes 105876 nps 882300 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c8e6 f1b5 d
8d6
info depth 11 seldepth 25 score cp 26 time 182 nodes 163668 nps 899274 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c8e6 f1b5 a
7a6 b5c6 b7c6
info depth 12 seldepth 30 score cp 24 time 424 nodes 391955 nps 924422 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5f6 g1f3 b
8c6 b1c3 c8f5
info depth 13 seldepth 30 score cp 43 time 877 nodes 803185 nps 915832 pv e2e4 b8c6 b1c3 e7e6 g1f3 d7d5 d2d4 f8b4 e4d5 e
6d5 f3e5 g8f6 f1b5
info depth 14 seldepth 30 score cp 27 time 1264 nodes 1169201 nps 925000 pv e2e4 b8c6 b1c3 e7e6 g1f3 d7d5 d2d4 f8b4 e4e5
 g8e7 f1b5 e8g8 e1g1 e7f5
info depth 15 seldepth 30 score cp 44 time 2289 nodes 2152818 nps 940505 pv e2e4 b8c6 b1c3 e7e6 g1f3 d7d5 d2d4 f8b4 e4d5
 e6d5 f1b5 g8f6 d1e2 f6e4 e1g1 c8f5
info depth 16 seldepth 38 score cp 29 time 4761 nodes 4517335 nps 948820 pv e2e4 e7e5 d2d4 e5d4 g1f3 b8c6 f3d4 g8f6 d4c6
 d7c6 d1d8 e8d8 b1d2 f8c5 f1d3 h8e8 e1g1
info depth 17 seldepth 38 score cp 29 time 5857 nodes 5574546 nps 951774 pv e2e4 e7e5 d2d4 e5d4 g1f3 b8c6
info depth 18 seldepth 38 score cp 37 time 9919 nodes 9425520 nps 950249 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 e5d4 f3d4
 f8b4 d4c6 b7c6 d1d4 d8e7 e4e5 e8g8 c1g5 c6c5
info depth 19 seldepth 38 score cp 37 time 14020 nodes 12731529 nps 908097 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 e5d4 f3
d4
info depth 20 seldepth 38 score cp 37 time 16894 nodes 15487627 nps 916753 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
info depth 21 seldepth 38 score cp 30 time 25230 nodes 23527706 nps 932528 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 e5d4 f3
d4 f8b4 d4c6 b7c6 f1d3 e8g8 e1g1 d7d5 e4e5 c8g4 d1d2 f6e4
info depth 22 seldepth 38 score cp 30 time 34468 nodes 31687819 nps 919340 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
bestmove e2e4

8 + 0.05
Score of Altair0.46 vs Altair0.45: 50 - 49 - 101 [0.502]
...      Altair0.46 playing White: 29 - 24 - 47  [0.525] 100
...      Altair0.46 playing Black: 21 - 25 - 54  [0.480] 100
...      White vs Black: 54 - 45 - 101  [0.522] 200
Elo difference: 1.7 +/- 33.9, LOS: 54.0 %, DrawRatio: 50.5 %
200 of 200 games finished.

1 min
Score of Altair0.46 vs sofcheck_amd64-popcnt_windows: 36 - 51 - 33 [0.438]
...      Altair0.46 playing White: 17 - 27 - 16  [0.417] 60
...      Altair0.46 playing Black: 19 - 24 - 17  [0.458] 60
...      White vs Black: 41 - 46 - 33  [0.479] 120
Elo difference: -43.7 +/- 53.6, LOS: 5.4 %, DrawRatio: 27.5 %
120 of 120 games finished.
```


### Reformatting TT to not allow returning scores if it causes a draw

```
info depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info depth 3 seldepth 7 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info depth 4 seldepth 8 score cp 8 time 5 nodes 953 nps 190600 pv b1c3 b8c6 g1f3 g8f6
info depth 5 seldepth 10 score cp 52 time 8 nodes 2080 nps 260000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info depth 6 seldepth 12 score cp 7 time 12 nodes 4677 nps 389750 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info depth 7 seldepth 20 score cp 32 time 20 nodes 11116 nps 555800 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info depth 8 seldepth 24 score cp 7 time 58 nodes 45144 nps 778344 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info depth 9 seldepth 25 score cp 30 time 75 nodes 60300 nps 804000 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 c1f4 c8f5 e2e3
info depth 10 seldepth 25 score cp 17 time 176 nodes 146029 nps 829710 pv e2e4 b8c6 b1c3 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4 d
5e4
info depth 11 seldepth 25 score cp 42 time 305 nodes 266021 nps 872200 pv e2e4 b8c6 b1c3 g8f6 d2d4 d7d5 e4e5 f6e4 c3e4 d
5e4 g1e2
info depth 12 seldepth 27 score cp 41 time 521 nodes 469045 nps 900278 pv e2e4 b8c6 g1f3 e7e6 b1c3 d7d5 d2d4 g8f6 c1g5 h
7h6 e4d5 e6d5
info depth 13 seldepth 27 score cp 36 time 945 nodes 866953 nps 917410 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6
info depth 14 seldepth 27 score cp 36 time 1267 nodes 1172504 nps 925417 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4
 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info depth 15 seldepth 34 score cp 21 time 2205 nodes 2049976 nps 929694 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4 e5d4 f3d4
 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info depth 16 seldepth 34 score cp 21 time 2814 nodes 2626489 nps 933364 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6
info depth 17 seldepth 34 score cp 21 time 4163 nodes 3899478 nps 936699 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4

info depth 18 seldepth 34 score cp 21 time 9416 nodes 7908353 nps 839884 pv e2e4 e7e5
info depth 19 seldepth 34 score cp 21 time 12351 nodes 10578404 nps 856481 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6
info depth 20 seldepth 36 score cp 21 time 17131 nodes 14916633 nps 870739 pv e2e4 e7e5
info depth 21 seldepth 36 score cp 37 time 28605 nodes 25381808 nps 887320 pv e2e4 e7e5 b1c3 b8c6 g1f3 f8c5 f3e5 g8f6 e5
c6 d7c6 e4e5 d8d4 d1e2 f6g4 c3e4 c5e7 c2c3 d4e5 d2d4 e5e6
info depth 22 seldepth 36 score cp 37 time 37106 nodes 33266794 nps 896534 pv e2e4 e7e5 b1c3 b8c6 g1f3 f8c5 f3e5 g8f6 e5
c6 d7c6 e4e5
bestmove e2e4

Score of Altair0.47 vs Altair0.46: 61 - 53 - 86 [0.520]
...      Altair0.47 playing White: 32 - 22 - 46  [0.550] 100
...      Altair0.47 playing Black: 29 - 31 - 40  [0.490] 100
...      White vs Black: 63 - 51 - 86  [0.530] 200
Elo difference: 13.9 +/- 36.4, LOS: 77.3 %, DrawRatio: 43.0 %
200 of 200 games finished.

Score of Altair0.47 vs sofcheck_amd64-popcnt_windows: 43 - 46 - 31 [0.487]
...      Altair0.47 playing White: 20 - 21 - 19  [0.492] 60
...      Altair0.47 playing Black: 23 - 25 - 12  [0.483] 60
...      White vs Black: 45 - 44 - 31  [0.504] 120
Elo difference: -8.7 +/- 53.9, LOS: 37.5 %, DrawRatio: 25.8 %
120 of 120 games finished.

Score of Altair1.0.0 vs Cosette-Win64: 73 - 140 - 37 [0.366]
...      Altair1.0.0 playing White: 26 - 79 - 20  [0.288] 125
...      Altair1.0.0 playing Black: 47 - 61 - 17  [0.444] 125
...      White vs Black: 87 - 126 - 37  [0.422] 250
Elo difference: -95.4 +/- 41.2, LOS: 0.0 %, DrawRatio: 14.8 %
250 of 250 games finished.
```


```
Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   1 Cosette-Win64                  86      41     240     126      68      46    149.0   62.1%   19.2%   62.9%   61.3% 
   2 Loki3.5.0-x64                  70      39     240     117      69      54    144.0   60.0%   22.5%   60.8%   59.2% 
   3 sofcheck_amd64-popcnt_windows      57      37     240     105      66      69    139.5   58.1%   28.7%   58.3%   57.9% 
   4 Altair1.0.0                   -29      39     240      84     104      52    110.0   45.8%   21.7%   44.6%   47.1% 
   5 GOOBv1                       -201      46     240      40     165      35     57.5   24.0%   14.6%   25.0%   22.9% 

600 of 600 games finished.
```


### 1.0.1
go infinite command implemented. threading input / search implemented

### 1.0.2

Allowing en passant, castling, and promotions for LMR
Razoring

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 7 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 8 score cp 8 time 4 nodes 954 nps 238500 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 10 score cp 52 time 7 nodes 2082 nps 297428 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 12 score cp 7 time 12 nodes 4750 nps 395833 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 20 score cp 32 time 21 nodes 11638 nps 554190 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info multipv 1 depth 8 seldepth 24 score cp 8 time 63 nodes 42357 nps 672333 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6
info multipv 1 depth 9 seldepth 24 score cp 30 time 86 nodes 62369 nps 725220 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 25 score cp 16 time 137 nodes 106136 nps 774715 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3 c
8f5 f1d3 e7e6
info multipv 1 depth 11 seldepth 26 score cp 22 time 390 nodes 326412 nps 836953 pv e2e4 d7d5 e4e5 d5d4 g1f3 b8c6
info multipv 1 depth 12 seldepth 30 score cp 18 time 658 nodes 562138 nps 854313 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3 f
6e4 d1d3 c8f5 c3e4 f5e4
info multipv 1 depth 13 seldepth 30 score cp 26 time 975 nodes 848484 nps 870240 pv b1c3 d7d5 e2e3 g8f6 g1f3 b8c6 d2d4 f
6e4
info multipv 1 depth 14 seldepth 30 score cp 25 time 1450 nodes 1278371 nps 881635 pv b1c3 d7d5 e2e3 g8f6 g1f3 b8d7 d2d4
 e7e6 f1d3 f8b4 e1g1 e8g8 a2a3 b4c3
info multipv 1 depth 15 seldepth 30 score cp 21 time 3424 nodes 2964505 nps 865801 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5 h8e8
info multipv 1 depth 16 seldepth 34 score cp 15 time 4819 nodes 4047764 nps 839959 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 f1d3 f8b4 c1d2 b4c5 b1c3 h8e8
info multipv 1 depth 17 seldepth 34 score cp 28 time 6260 nodes 5356320 nps 855642 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5
info multipv 1 depth 18 seldepth 34 score cp 28 time 7681 nodes 6618674 nps 861694 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4
info multipv 1 depth 19 seldepth 34 score cp 28 time 12357 nodes 9610756 nps 777758 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d
4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 c8g4
info multipv 1 depth 20 seldepth 38 score cp 42 time 24655 nodes 18653278 nps 756571 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f3
e5 e8g8 e5d3 b4c3 d2c3 f6e4 f1e2 d7d5 e1g1 b8c6 f2f3 e4f6 c1g5 f8e8
info multipv 1 depth 21 seldepth 38 score cp 42 time 30606 nodes 23424234 nps 765347 pv e2e4 e7e5 g1f3 g8f6
info multipv 1 depth 21 seldepth 38 score cp 42 time 44999 nodes 35717137 nps 793731 pv e2e4 e7e5 g1f3 g8f6
bestmove e2e4
```

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 7 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 8 score cp 8 time 5 nodes 954 nps 190800 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 10 score cp 52 time 9 nodes 2082 nps 231333 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 12 score cp 7 time 12 nodes 4696 nps 391333 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 20 score cp 32 time 21 nodes 11388 nps 542285 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info multipv 1 depth 8 seldepth 24 score cp 8 time 61 nodes 45602 nps 747573 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6
info multipv 1 depth 9 seldepth 24 score cp 30 time 76 nodes 58559 nps 770513 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 25 score cp 17 time 121 nodes 97739 nps 807760 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3 c8
g4 h2h3 g4f5
info multipv 1 depth 11 seldepth 25 score cp 20 time 208 nodes 152361 nps 732504 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 d1d3 e
7e6 e2e4 f8b4 e4e5
info multipv 1 depth 12 seldepth 30 score cp 21 time 438 nodes 344440 nps 786392 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c
8g4 e2e3 e7e6 h2h3 g4f5
info multipv 1 depth 13 seldepth 30 score cp 38 time 1033 nodes 853159 nps 825904 pv e2e4 b8c6 g1f3 e7e6 d2d4 g8f6 b1c3
f8b4 d4d5 e6d5 e4d5 d8e7 c1e3 c6e5
info multipv 1 depth 14 seldepth 30 score cp 43 time 1585 nodes 1341413 nps 846317 pv e2e4 b8c6 g1f3 e7e5 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4
info multipv 1 depth 15 seldepth 33 score cp 21 time 2849 nodes 2469838 nps 866914 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8
info multipv 1 depth 16 seldepth 38 score cp 28 time 3922 nodes 3424009 nps 873026 pv e2e4 e7e5 d2d4 e5d4 g1f3 b8c6 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1d2 f8c5 f1d3 h8e8 e1g1
info multipv 1 depth 17 seldepth 38 score cp 14 time 6720 nodes 5353840 nps 796702 pv e2e4 e7e5 d2d4 e5d4 g1f3 f8b4 c1d2
 b4d2 d1d2 c7c5 f1c4 b8c6 e1g1 g8f6 d2g5 e8g8 b1d2 d7d6 a1d1
info multipv 1 depth 18 seldepth 38 score cp 14 time 9911 nodes 7434034 nps 750079 pv e2e4 e7e5
info multipv 1 depth 19 seldepth 38 score cp 28 time 12355 nodes 9417677 nps 762256 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d
4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 c8g4 g5f6 g7f6 f1e2 b4c3 b2c3
info multipv 1 depth 20 seldepth 38 score cp 35 time 25737 nodes 18668724 nps 725365 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 b8c6 g1f3 f8e7 f1b5 g8f6 b5c6 b7c6 e4f6 e7f6 e1g1 e8g8 f1e1 d8d6 f3e5
info multipv 1 depth 21 seldepth 39 score cp 31 time 36069 nodes 26798111 nps 742967 pv e2e4 e7e6 d2d4 d7d5 b1c3 g8f6 e4
e5 f6e4 c3e4 d5e4 f1c4 b8c6 c2c3 d8d7 d1c2 c6a5 c4e2 d7d5 c1g5 a5c6 g1h3
bestmove e2e4

Score of Altair1.0.2 vs Altair1.0.1: 168 - 162 - 170 [0.506]
...      Altair1.0.2 playing White: 70 - 84 - 96  [0.472] 250
...      Altair1.0.2 playing Black: 98 - 78 - 74  [0.540] 250
...      White vs Black: 148 - 182 - 170  [0.466] 500
Elo difference: 4.2 +/- 24.7, LOS: 62.9 %, DrawRatio: 34.0 %
500 of 500 games finished.

Score of Altair1.0.2 vs Altair1.0.1: 69 - 67 - 104 [0.504]
...      Altair1.0.2 playing White: 34 - 37 - 49  [0.487] 120
...      Altair1.0.2 playing Black: 35 - 30 - 55  [0.521] 120
...      White vs Black: 64 - 72 - 104  [0.483] 240
Elo difference: 2.9 +/- 33.1, LOS: 56.8 %, DrawRatio: 43.3 %
240 of 240 games finished.
```


### 1.0.3
Move ordering bug fix of en passant. Lowered to the equivalent of a pawn capturing half a free pawn instead of
a pawn capturing a queen.

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 7 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 8 score cp 8 time 5 nodes 954 nps 190800 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 10 score cp 52 time 9 nodes 2082 nps 231333 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 12 score cp 7 time 17 nodes 4696 nps 276235 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 20 score cp 32 time 29 nodes 11380 nps 392413 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info multipv 1 depth 8 seldepth 24 score cp 8 time 72 nodes 45566 nps 632861 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6
info multipv 1 depth 9 seldepth 24 score cp 30 time 87 nodes 58528 nps 672735 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 25 score cp 17 time 139 nodes 97674 nps 702690 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3 c8
g4 h2h3 g4f5
info multipv 1 depth 11 seldepth 25 score cp 20 time 218 nodes 152305 nps 698646 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 d1d3 e
7e6 e2e4 f8b4 e4e5
info multipv 1 depth 12 seldepth 30 score cp 21 time 433 nodes 344481 nps 795568 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c
8g4 e2e3 e7e6 h2h3 g4f5
info multipv 1 depth 13 seldepth 30 score cp 32 time 1054 nodes 907505 nps 861010 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4
b8c6 g1f3
info multipv 1 depth 14 seldepth 30 score cp 36 time 1622 nodes 1408721 nps 868508 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
info multipv 1 depth 15 seldepth 34 score cp 21 time 2165 nodes 1899162 nps 877211 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 16 seldepth 37 score cp 11 time 3461 nodes 3100617 nps 895873 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 b4c3 b2c3 h8e8
info multipv 1 depth 17 seldepth 37 score cp 11 time 4282 nodes 3837041 nps 896086 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
info multipv 1 depth 18 seldepth 37 score cp 35 time 7141 nodes 6529647 nps 914388 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4
 e7e6 c2c4 d5f6 b1c3 b8c6 f1e2 f8d6 e1g1 e8g8 c1g5 e6e5
info multipv 1 depth 19 seldepth 37 score cp 35 time 9470 nodes 8710885 nps 919840 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4

info multipv 1 depth 20 seldepth 37 score cp 44 time 13620 nodes 12615334 nps 926235 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1
f3 e7e6 c2c4 f8b4 c1d2 b4d2 d1d2 d5f6 f1e2 b8c6 e1g1 e8g8 b1c3 d8d6 c3b5 d6d7
info multipv 1 depth 21 seldepth 38 score cp 44 time 24653 nodes 22738517 nps 922342 pv e2e4 d7d5 e4d5 g8f6 d2d4
info multipv 1 depth 21 seldepth 39 score cp 44 time 45001 nodes 39010333 nps 866877 pv e2e4 d7d5 e4d5 g8f6 d2d4
bestmove e2e4

Score of Altair1.0.3 vs Altair1.0.2: 58 - 40 - 62 [0.556]
...      Altair1.0.3 playing White: 30 - 19 - 31  [0.569] 80
...      Altair1.0.3 playing Black: 28 - 21 - 31  [0.544] 80
...      White vs Black: 51 - 47 - 62  [0.512] 160
Elo difference: 39.3 +/- 42.4, LOS: 96.5 %, DrawRatio: 38.8 %
160 of 160 games finished.
```


### Razoring Changes


```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 4 nodes 954 nps 238500 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 6 nodes 2082 nps 347000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 10 nodes 4750 nps 475000 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 9 score cp 32 time 19 nodes 11576 nps 609263 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info multipv 1 depth 8 seldepth 10 score cp 8 time 53 nodes 42119 nps 794698 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6
info multipv 1 depth 9 seldepth 12 score cp 30 time 75 nodes 62032 nps 827093 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 13 score cp 16 time 122 nodes 105417 nps 864073 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3 c
8f5 f1d3 e7e6
info multipv 1 depth 11 seldepth 16 score cp 21 time 316 nodes 277145 nps 877041 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 c1f4 c
8f5 e2e3 e7e6 f1b5
info multipv 1 depth 12 seldepth 16 score cp 18 time 571 nodes 515393 nps 902614 pv b1c3 g8f6 g1f3 d7d5 d2d4 b8c6 e2e3 f
6e4 d1d3 c8f5 c3e4 f5e4
info multipv 1 depth 13 seldepth 17 score cp 26 time 909 nodes 832667 nps 916025 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info multipv 1 depth 14 seldepth 18 score cp 41 time 2065 nodes 1848764 nps 895285 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 c2c4
 d5f6 b1c3 b8c6 d2d4 c8f5 f1d3 e7e6
info multipv 1 depth 15 seldepth 20 score cp 45 time 3144 nodes 2726836 nps 867314 pv e2e4 e7e6 g1f3 d7d5 e4e5 c7c5 b1c3
 b8c6 f1b5 d5d4 c3e4 f7f5 e5f6 g8f6 d2d3
info multipv 1 depth 16 seldepth 20 score cp 43 time 4164 nodes 3597186 nps 863877 pv e2e4 e7e6 g1f3 d7d5 e4e5 c7c5 b1c3
 b8c6 f1b5 d5d4 c3e4 f7f5 e5f6 g8f6 e4f6 d8f6 e1g1
info multipv 1 depth 17 seldepth 21 score cp 43 time 5227 nodes 4594341 nps 878963 pv e2e4 e7e6 g1f3 d7d5 e4e5 c7c5 b1c3

info multipv 1 depth 18 seldepth 24 score cp 42 time 10138 nodes 8928132 nps 880660 pv e2e4 e7e6 g1f3 d7d5 e4e5 c7c5 b1c
3 b8c6 f1b5 d5d4 c3e4 f7f5 e4g3 c8d7 b5c4 d8c7 d1e2
info multipv 1 depth 19 seldepth 25 score cp 36 time 15286 nodes 13177377 nps 862055 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2
d4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 c8g4 f1d3 h8e8 e1g1 d8c8
info multipv 1 depth 20 seldepth 25 score cp 36 time 19172 nodes 16420783 nps 856498 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2
d4 e5d4 f3d4
info multipv 1 depth 21 seldepth 28 score cp 24 time 29468 nodes 25675230 nps 871291 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8c5 f3
e5 b8c6 e5d3 c5d4 f1e2 e8g8 e4e5 c6e5 d3e5 d4e5 d2d4 e5d6 e1g1 f8e8 c1g5
info multipv 1 depth 21 seldepth 29 score cp 24 time 45000 nodes 39469057 nps 877090 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8c5 f3
e5 b8c6 e5d3 c5d4 f1e2 e8g8 e4e5 c6e5 d3e5 d4e5 d2d4 e5d6 e1g1 f8e8 c1g5
bestmove e2e4

Score of Altair1.0.4 vs Altair1.0.3: 111 - 104 - 135 [0.510]
...      Altair1.0.4 playing White: 55 - 47 - 73  [0.523] 175
...      Altair1.0.4 playing Black: 56 - 57 - 62  [0.497] 175
...      White vs Black: 112 - 103 - 135  [0.513] 350
Elo difference: 6.9 +/- 28.6, LOS: 68.3 %, DrawRatio: 38.6 %
350 of 350 games finished.
```

### 1.0.5
No LMR for captures

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 5 nodes 954 nps 190800 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 7 nodes 2082 nps 297428 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 10 nodes 4750 nps 475000 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 9 score cp 32 time 19 nodes 11576 nps 609263 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info multipv 1 depth 8 seldepth 10 score cp 16 time 53 nodes 42426 nps 800490 pv e2e4 d7d5 e4e5 b8c6 g1f3 c8g4 d2d4
info multipv 1 depth 9 seldepth 12 score cp 29 time 102 nodes 79084 nps 775333 pv b1c3 g8f6 g1f3 b8c6 d2d4 d7d5 c1f4 c8f
5 e2e3
info multipv 1 depth 10 seldepth 14 score cp 17 time 235 nodes 156763 nps 667076 pv b1c3 g8f6 g1f3 b8c6 d2d4 d7d5 e2e3 c
8g4 h2h3 g4f5
info multipv 1 depth 11 seldepth 16 score cp 30 time 381 nodes 266146 nps 698545 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info multipv 1 depth 12 seldepth 16 score cp 26 time 526 nodes 368484 nps 700539 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c
8g4 h2h3 g4f5 f1d3 e7e6
info multipv 1 depth 13 seldepth 16 score cp 26 time 829 nodes 593030 nps 715355 pv b1c3 d7d5 d2d4
info multipv 1 depth 14 seldepth 20 score cp 33 time 2653 nodes 1956616 nps 737510 pv e2e4 e7e6 b1c3 d7d5 d2d4 g8f6 e4e5
 f6e4 c3e4 d5e4 f1b5 c8d7 b5c4 b8c6 g1e2
info multipv 1 depth 15 seldepth 20 score cp 31 time 3281 nodes 2377408 nps 724598 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4
 b8c6 f1d3 g8f6 g1f3 f8e7 c2c3 f6e4 d3e4
info multipv 1 depth 16 seldepth 21 score cp 36 time 4786 nodes 3332123 nps 696222 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4
 b8c6 g1f3 g8f6 e4f6 d8f6 c1g5 f6f5 c2c3 f8d6 f1c4
info multipv 1 depth 17 seldepth 21 score cp 36 time 6300 nodes 4622544 nps 733737 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4
info multipv 1 depth 18 seldepth 23 score cp 36 time 11435 nodes 8885888 nps 777078 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c
4 d5f6 b1c3 b8c6 g1f3 e7e6 d4d5 e6d5 c4d5 d8e7 f1e2 c6b4 c1f4
info multipv 1 depth 19 seldepth 24 score cp 36 time 13537 nodes 10891480 nps 804571 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2
c4
info multipv 1 depth 20 seldepth 24 score cp 38 time 19781 nodes 14204082 nps 718066 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2
c4 d5f6 g1f3 e7e6 b1c3 b8c6 f1e2
info multipv 1 depth 21 seldepth 30 score cp 32 time 39881 nodes 30631418 nps 768070 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2
d4 f8b4 d4d5 f6e4 d5c6 e4c3 b2c3 b4c3 c1d2 c3a1 d1a1 f7f6 c6b7 c8b7 a1c3 e8g8
bestmove e2e4

Score of Altair1.0.5 vs Altair1.0.4: 112 - 89 - 99 [0.538]
...      Altair1.0.5 playing White: 50 - 45 - 55  [0.517] 150
...      Altair1.0.5 playing Black: 62 - 44 - 44  [0.560] 150
...      White vs Black: 94 - 107 - 99  [0.478] 300
Elo difference: 26.7 +/- 32.3, LOS: 94.8 %, DrawRatio: 33.0 %
300 of 300 games finished.

1 min
Score of Altair1.0.5 vs sofcheck_amd64-popcnt_windows: 43 - 41 - 36 [0.508]
...      Altair1.0.5 playing White: 21 - 22 - 17  [0.492] 60
...      Altair1.0.5 playing Black: 22 - 19 - 19  [0.525] 60
...      White vs Black: 40 - 44 - 36  [0.483] 120
Elo difference: 5.8 +/- 52.3, LOS: 58.6 %, DrawRatio: 30.0 %
120 of 120 games finished.
```


### Blockers

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 3 nodes 302 nps 100666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 4 nodes 954 nps 238500 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 6 nodes 2082 nps 347000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 10 nodes 4750 nps 475000 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 9 score cp 32 time 18 nodes 11576 nps 643111 pv b1c3 b8c6 d2d4 g8f6 g1f3 d7d5 c1f4
info multipv 1 depth 8 seldepth 10 score cp 16 time 52 nodes 42426 nps 815884 pv e2e4 d7d5 e4e5 b8c6 g1f3 c8g4 d2d4
info multipv 1 depth 9 seldepth 12 score cp 29 time 91 nodes 79075 nps 868956 pv b1c3 g8f6 g1f3 b8c6 d2d4 d7d5 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 14 score cp 17 time 174 nodes 156751 nps 900867 pv b1c3 g8f6 g1f3 b8c6 d2d4 d7d5 e2e3 c
8g4 h2h3 g4f5
info multipv 1 depth 11 seldepth 16 score cp 30 time 301 nodes 266152 nps 884225 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info multipv 1 depth 12 seldepth 16 score cp 26 time 411 nodes 368482 nps 896549 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c
8g4 h2h3 g4f5 f1d3 e7e6
info multipv 1 depth 13 seldepth 16 score cp 26 time 704 nodes 593043 nps 842390 pv b1c3 d7d5 d2d4
info multipv 1 depth 14 seldepth 20 score cp 33 time 2205 nodes 1957024 nps 887539 pv e2e4 e7e6 b1c3 d7d5 d2d4 g8f6 e4e5
 f6e4 c3e4 d5e4 f1b5 c8d7 b5c4 b8c6 g1e2
info multipv 1 depth 15 seldepth 20 score cp 31 time 2647 nodes 2377652 nps 898244 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4
 b8c6 f1d3 g8f6 g1f3 f8e7 c2c3 f6e4 d3e4
info multipv 1 depth 16 seldepth 21 score cp 36 time 3748 nodes 3422427 nps 913134 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4
 b8c6 g1f3 g8f6 e4f6 d8f6 c1g5 f6f5 c2c3 f8d6 f1c4
info multipv 1 depth 17 seldepth 22 score cp 16 time 6899 nodes 6373334 nps 923805 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b5
 f8b4 a2a3 b4c3 d2c3 f6e4 e1g1 d7d6 f1e1 c8f5 c1e3
info multipv 1 depth 18 seldepth 24 score cp 15 time 10721 nodes 9848491 nps 918616 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b
5 f8c5 f3e5 c6e5 d2d4 a7a6 b5e2 c5b4 d4e5 f6e4 e1g1
info multipv 1 depth 19 seldepth 24 score cp 15 time 14174 nodes 12978030 nps 915622 pv e2e4 e7e5 b1c3 b8c6 g1f3
info multipv 1 depth 20 seldepth 28 score cp 15 time 26699 nodes 24611941 nps 921830 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1
b5 f8c5 f3e5 c6e5 d2d4 a7a6 b5e2 c5b4 d4e5 f6e4 e1g1 e4c3 b2c3
info multipv 1 depth 21 seldepth 28 score cp 29 time 41874 nodes 38592303 nps 921629 pv e2e4 e7e6 b1c3 d7d5 d2d4 g8f6 e4
e5 f6e4 c3e4 d5e4 g1e2 c7c5 c1f4 d8b6 a1b1 b8c6 c2c3 f8e7 e2g3 e8g8
bestmove e2e4

Score of Altair1.0.6 vs Altair1.0.5: 74 - 53 - 73 [0.552]
...      Altair1.0.6 playing White: 34 - 28 - 38  [0.530] 100
...      Altair1.0.6 playing Black: 40 - 25 - 35  [0.575] 100
...      White vs Black: 59 - 68 - 73  [0.477] 200
Elo difference: 36.6 +/- 38.6, LOS: 96.9 %, DrawRatio: 36.5 %
```

### 1.0.7
Not resetting history and capture history tables every move

```
Score of Altair1.0.7 vs Altair1.0.6: 107 - 98 - 145 [0.513]
...      Altair1.0.7 playing White: 60 - 49 - 66  [0.531] 175
...      Altair1.0.7 playing Black: 47 - 49 - 79  [0.494] 175
...      White vs Black: 109 - 96 - 145  [0.519] 350
Elo difference: 8.9 +/- 27.9, LOS: 73.5 %, DrawRatio: 41.4 %
350 of 350 games finished.

Score of Altair1.0.7 vs sofcheck_amd64-popcnt_windows: 77 - 81 - 82 [0.492]
...      Altair1.0.7 playing White: 37 - 40 - 43  [0.487] 120
...      Altair1.0.7 playing Black: 40 - 41 - 39  [0.496] 120
...      White vs Black: 78 - 80 - 82  [0.496] 240
Elo difference: -5.8 +/- 35.7, LOS: 37.5 %, DrawRatio: 34.2 %

Score of Altair1.0.7 vs Altair1.0.1: 63 - 35 - 52 [0.593]
...      Altair1.0.7 playing White: 32 - 17 - 26  [0.600] 75
...      Altair1.0.7 playing Black: 31 - 18 - 26  [0.587] 75
...      White vs Black: 50 - 48 - 52  [0.507] 150
Elo difference: 65.6 +/- 45.5, LOS: 99.8 %, DrawRatio: 34.7 %
150 of 150 games finished.
 ```


### 1.0.8
Bug fixes in the search thread

```
Score of Altair1.0.8 vs Altair1.0.7: 39 - 26 - 35 [0.565]
...      Altair1.0.8 playing White: 18 - 13 - 19  [0.550] 50
...      Altair1.0.8 playing Black: 21 - 13 - 16  [0.580] 50
...      White vs Black: 31 - 34 - 35  [0.485] 100
Elo difference: 45.4 +/- 55.5, LOS: 94.7 %, DrawRatio: 35.0 %

Score of Altair1.0.8 vs Loki3.5.0-x64: 346 - 478 - 176 [0.434]
...      Altair1.0.8 playing White: 165 - 255 - 80  [0.410] 500
...      Altair1.0.8 playing Black: 181 - 223 - 96  [0.458] 500
...      White vs Black: 388 - 436 - 176  [0.476] 1000
Elo difference: -46.1 +/- 19.7, LOS: 0.0 %, DrawRatio: 17.6 %
1000 of 1000 games finished.
```


### 1.0.9
Late Move Pruning

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 2 nodes 257 nps 128500 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 4 nodes 707 nps 176750 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 7 nodes 1351 nps 193000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 14 nodes 4196 nps 299714 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 32 time 21 nodes 7992 nps 380571 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 10 score cp 17 time 36 nodes 18816 nps 522666 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 17 time 75 nodes 50954 nps 679386 pv b1c3 b8c6 e2e4 g8f6 g1f3 d7d5
info multipv 1 depth 10 seldepth 14 score cp 21 time 121 nodes 89521 nps 739842 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 d1d3 e7
e6
info multipv 1 depth 11 seldepth 14 score cp 20 time 171 nodes 125359 nps 733093 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 d1d3 e
7e6 e2e4 f8b4 e4e5
info multipv 1 depth 12 seldepth 17 score cp 24 time 323 nodes 247090 nps 764984 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d
5f6 g1f3 b8c6 b1c3 c8f5
info multipv 1 depth 13 seldepth 17 score cp 30 time 754 nodes 604172 nps 801289 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 g
8f6 b1c3 b8c6 f1e2 f6e4 e1g1
info multipv 1 depth 14 seldepth 18 score cp 29 time 1053 nodes 847192 nps 804550 pv e2e4 e7e6 g1f3 d7d5 e4e5 d5d4 f1b5
c7c6 b5c4 b8d7 e1g1 d7b6 c4d3 g8e7 b1a3
info multipv 1 depth 15 seldepth 22 score cp 29 time 1860 nodes 1442416 nps 775492 pv e2e4 e7e6 g1f3 d7d5 e4e5 d5d4 f1b5

info multipv 1 depth 16 seldepth 22 score cp 25 time 4137 nodes 3210733 nps 776101 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 c8d7 d2e4 d5e4 c1g5 f8b4 c2c3
info multipv 1 depth 17 seldepth 23 score cp 34 time 5203 nodes 4083752 nps 784884 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8b4 c2c3 b4c5 d2e4 d5e4 d1d8 e8d8
info multipv 1 depth 18 seldepth 23 score cp 34 time 6287 nodes 4998638 nps 795075 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5

info multipv 1 depth 19 seldepth 25 score cp 18 time 10688 nodes 8250932 nps 771980 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d
4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 d7d5 e4d5 d8e7 d3e2 f6d5 e1g1 d5c3
info multipv 1 depth 20 seldepth 25 score cp 18 time 13613 nodes 10463585 nps 768646 pv e2e4 e7e5 g1f3 b8c6
info multipv 1 depth 21 seldepth 26 score cp 30 time 20229 nodes 13770951 nps 680752 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 e8g8 e1g1 d7d5 e4e5 c8g4 d1d2 f6e4
info multipv 1 depth 22 seldepth 26 score cp 30 time 25962 nodes 18024391 nps 694260 pv e2e4 e7e5 g1f3
info multipv 1 depth 22 seldepth 31 score cp 30 time 45000 nodes 32624657 nps 724992 pv e2e4 e7e5 g1f3
bestmove e2e4

Testing from Gedas
Score of AltairNew vs Altair: 213 - 111 - 176  [0.602] 500
...      AltairNew playing White: 129 - 30 - 91  [0.698] 250
...      AltairNew playing Black: 84 - 81 - 85  [0.506] 250
...      White vs Black: 210 - 114 - 176  [0.596] 500
Elo difference: 71.9 +/- 24.8, LOS: 100.0 %, DrawRatio: 35.2 %

My own tests
Score of Altair1.0.9 vs Altair1.0.8: 44 - 23 - 33 [0.605]
...      Altair1.0.9 playing White: 20 - 13 - 17  [0.570] 50
...      Altair1.0.9 playing Black: 24 - 10 - 16  [0.640] 50
...      White vs Black: 30 - 37 - 33  [0.465] 100
Elo difference: 74.1 +/- 56.8, LOS: 99.5 %, DrawRatio: 33.0 %
100 of 100 games finished.
```


### 1.1.0
LMR changes

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 3 nodes 257 nps 85666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 5 nodes 1467 nps 293400 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 7 nodes 2132 nps 304571 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 12 nodes 6366 nps 530500 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 28 time 19 nodes 10679 nps 562052 pv b1c3 b8c6 e2e3 e7e5 g1f3 g8f6 d2d4
info multipv 1 depth 8 seldepth 11 score cp 17 time 36 nodes 24717 nps 686583 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 11 score cp 29 time 56 nodes 40677 nps 726375 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 13 score cp 24 time 150 nodes 116841 nps 778940 pv g1f3 b8c6 d2d4 d7d5 d1d3 g8f6 b1c3
info multipv 1 depth 11 seldepth 16 score cp 17 time 270 nodes 217547 nps 805729 pv g1f3 b8c6 d2d4 d7d5 b1c3 c8f5 f3e5 c
6e5 d4e5 e7e6 e2e3
info multipv 1 depth 12 seldepth 16 score cp 31 time 354 nodes 288006 nps 813576 pv g1f3 b8c6 d2d4 d7d5 b1c3 c8f5 e2e3 g
8f6 f1d3 f6e4 c3e4 d5e4
info multipv 1 depth 13 seldepth 18 score cp 31 time 1673 nodes 1372673 nps 820485 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 b1c3
info multipv 1 depth 14 seldepth 18 score cp 38 time 1963 nodes 1601340 nps 815761 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4
 d5f6 g1f3 e7e6 b1c3 b8c6 c1f4 f8b4
info multipv 1 depth 15 seldepth 21 score cp 42 time 2618 nodes 2147414 nps 820249 pv e2e4 e7e6 d2d4 b8c6 b1c3 g8f6 e4e5
 f6d5 c3d5 e6d5 c1f4 d7d6 g1f3 c8g4 f1b5
info multipv 1 depth 16 seldepth 21 score cp 35 time 3949 nodes 3142993 nps 795895 pv e2e4 e7e6 g1f3 d7d5 e4e5 d5d4 f1c4
 b8c6 d2d3 g8e7 e1g1 e7g6 c1g5 f8e7 g5e7 d8e7
info multipv 1 depth 17 seldepth 24 score cp 25 time 6682 nodes 5373548 nps 804182 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4
 f8b4 d4d5 f6e4 d5c6 e4c3 b2c3 b4c3 c1d2 c3a1 d1a1 d7d6
info multipv 1 depth 18 seldepth 24 score cp 25 time 8342 nodes 6771426 nps 811726 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4
 f8b4 d4d5
info multipv 1 depth 19 seldepth 24 score cp 40 time 10371 nodes 8479687 nps 817634 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d
4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 b4c3 b2c3 c8g4 g5f6 g7f6 h2h3 g4e6
info multipv 1 depth 20 seldepth 25 score cp 40 time 13191 nodes 10828557 nps 820904 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4
info multipv 1 depth 21 seldepth 26 score cp 40 time 17920 nodes 14388642 nps 802937 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6
info multipv 1 depth 22 seldepth 28 score cp 40 time 29085 nodes 22524807 nps 774447 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3
d4 d8f6 d4f3 c6e5 f1e2 f8c5 b1c3 g8e7 e1g1 e8g8 f3e5 f6e5 d1d3 d7d6 c1e3
info multipv 1 depth 23 seldepth 30 score cp 35 time 44877 nodes 34997106 nps 779845 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 e8g8 e1g1 d7d5 e4d5 c6d5 c1g5 h7h6 g5f6 d8f6
bestmove e2e4

Score of Altair1.1.0 vs Altair1.0.9: 155 - 135 - 210 [0.520]
...      Altair1.1.0 playing White: 73 - 69 - 108  [0.508] 250
...      Altair1.1.0 playing Black: 82 - 66 - 102  [0.532] 250
...      White vs Black: 139 - 151 - 210  [0.488] 500
Elo difference: 13.9 +/- 23.2, LOS: 88.0 %, DrawRatio: 42.0 %
500 of 500 games finished.
```


### 1.1.1
More aggressive LMP for quiets

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 2 nodes 109 nps 54500 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 3 nodes 251 nps 83666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 6 nodes 910 nps 151666 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 8 nodes 1551 nps 193875 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 13 nodes 5371 nps 413153 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 31 time 18 nodes 9442 nps 524555 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 10 score cp 17 time 27 nodes 15631 nps 578925 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 21 time 53 nodes 35821 nps 675867 pv d2d4 d7d5 b1c3 b8c6 e2e3 g8f6 g1f3 c8f5
 f1b5
info multipv 1 depth 10 seldepth 13 score cp 17 time 82 nodes 60186 nps 733975 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e
4 c3e4 d5e4
info multipv 1 depth 11 seldepth 15 score cp 26 time 245 nodes 196371 nps 801514 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f
6e4 f1b5 e7e6 e1g1
info multipv 1 depth 12 seldepth 15 score cp 28 time 319 nodes 260186 nps 815630 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5 d2d4 e
5d4 f3d4 f8b4
info multipv 1 depth 13 seldepth 17 score cp 14 time 597 nodes 497547 nps 833412 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 c1f4 f
8d6 e2e3 b8c6 f1b5 e8g8 e1g1
info multipv 1 depth 14 seldepth 19 score cp 36 time 1160 nodes 978995 nps 843961 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 20 score cp 21 time 1610 nodes 1356121 nps 842311 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 16 seldepth 22 score cp 21 time 2155 nodes 1832874 nps 850521 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4

info multipv 1 depth 17 seldepth 22 score cp 30 time 3040 nodes 2591889 nps 852595 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 f8b4 f3e5 f6e4 d1f3 e4f6 c1e3 e8g8 a1d1 f8e8 e3f4
info multipv 1 depth 18 seldepth 22 score cp 30 time 4024 nodes 3448442 nps 856968 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 f8b4 f3e5 f6e4 d1f3 e4f6
info multipv 1 depth 19 seldepth 25 score cp 29 time 7636 nodes 6500774 nps 851332 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4
 e7e6 c2c4 d5f6 b1c3 b8c6 c1f4 f8b4 f1e2 f6e4 e1g1 e4c3 b2c3
info multipv 1 depth 20 seldepth 28 score cp 38 time 15838 nodes 13506157 nps 852769 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 b8c6 g1f3 f8e7 f1b5 g8f6 e4f6 e7f6 b5c6 b7c6 e1g1 e8g8 f3e5 c8b7 c1f4 d8d6
info multipv 1 depth 21 seldepth 28 score cp 35 time 19949 nodes 17064809 nps 855421 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 b8c6 g1f3 f8e7 f1b5 g8f6 f3e5 c8d7 e5c6 d7c6 b5c6 b7c6 e4f6 e7f6 c2c3 e8g8 e1g1
info multipv 1 depth 22 seldepth 29 score cp 35 time 26354 nodes 22521578 nps 854579 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 b8c6 g1f3
info multipv 1 depth 23 seldepth 30 score cp 46 time 44638 nodes 36835331 nps 825201 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 b8c6 f1d3 f8e7 g1f3 g8f6 e1g1 e8g8 c2c3 f8e8 f3e5 f6e4 d3e4 c6e5
bestmove e2e4

Score of Altair1.1.1 vs Altair1.1.0: 78 - 55 - 68 [0.557]
...      Altair1.1.1 playing White: 41 - 32 - 28  [0.545] 101
...      Altair1.1.1 playing Black: 37 - 23 - 40  [0.570] 100
...      White vs Black: 64 - 69 - 68  [0.488] 201
Elo difference: 39.9 +/- 39.3, LOS: 97.7 %, DrawRatio: 33.8 %

Score of Altair1.1.1 vs sofcheck_amd64-popcnt_windows: 98 - 72 - 70 [0.554]
...      Altair1.1.1 playing White: 48 - 37 - 35  [0.546] 120
...      Altair1.1.1 playing Black: 50 - 35 - 35  [0.563] 120
...      White vs Black: 83 - 87 - 70  [0.492] 240
Elo difference: 37.8 +/- 37.2, LOS: 97.7 %, DrawRatio: 29.2 %
240 of 240 games finished.
```

### 1.1.2
More aggressive adaptive null move pruning

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 3 nodes 251 nps 83666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 5 nodes 910 nps 182000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 7 nodes 1509 nps 215571 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 10 nodes 3888 nps 388800 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 32 time 15 nodes 7364 nps 490933 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 c1f4
info multipv 1 depth 8 seldepth 11 score cp 7 time 32 nodes 22329 nps 697781 pv b1c3 d7d5 g1f3 g8f6 d2d4
info multipv 1 depth 9 seldepth 12 score cp 30 time 50 nodes 35547 nps 710940 pv b1c3 d7d5 d2d4 b8c6 g1f3 g8f6
info multipv 1 depth 10 seldepth 13 score cp 21 time 70 nodes 51660 nps 738000 pv b1c3 d7d5 d2d4 b8c6 g1f3 g8f6 d1d3 e7e
6 e2e4 f8b4
info multipv 1 depth 11 seldepth 14 score cp 39 time 193 nodes 155898 nps 807761 pv e2e4 b8c6 d2d4 d7d5 e4e5 g8h6 g1f3 c
8g4 c1h6 g7h6 b1c3
info multipv 1 depth 12 seldepth 17 score cp 33 time 411 nodes 335982 nps 817474 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 d2d4 b
8c6 g1f3 g8e7 f3e5 c6e5
info multipv 1 depth 13 seldepth 17 score cp 41 time 516 nodes 425115 nps 823866 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 d2d4 g
8e7 c1g5 b8c6 g1f3 c8f5 f1b5
info multipv 1 depth 14 seldepth 18 score cp 41 time 784 nodes 659512 nps 841214 pv e2e4 e7e6 d2d4 b8c6 g1f3 g8f6 b1c3 f
8b4 d4d5 e6d5 e4d5 b4c3 b2c3 d8e7 c1e3 c6e5
info multipv 1 depth 15 seldepth 20 score cp 21 time 1684 nodes 1311027 nps 778519 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 16 seldepth 22 score cp 11 time 3019 nodes 2257512 nps 747768 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 17 seldepth 24 score cp 41 time 3929 nodes 2955730 nps 752285 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3
 g8f6 f1b5 c7c6 b5d3 f8b4 c2c3 d8e7 f3e5 b4d6 e1g1 d6e5 d4e5 e7e5
info multipv 1 depth 18 seldepth 25 score cp 37 time 5421 nodes 4023327 nps 742174 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 g1f3
 b8c6 f1b5 c8d7 b1c3 c5d4 b5c6 d4c3 c6b7 c3b2 c1b2 f8b4 c2c3
info multipv 1 depth 19 seldepth 25 score cp 37 time 6787 nodes 5160620 nps 760368 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 g1f3
 b8c6 f1b5 c8d7 b1c3 c5d4 b5c6 d4c3 c6b7 c3b2
info multipv 1 depth 20 seldepth 26 score cp 31 time 11225 nodes 8710875 nps 776024 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d
4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 b4c3 b2c3 d8e7 d1e2 d7d5 f2f3 d5e4 f3e4
info multipv 1 depth 21 seldepth 26 score cp 31 time 13813 nodes 10832936 nps 784256 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 b4c3
info multipv 1 depth 22 seldepth 30 score cp 40 time 22422 nodes 17320984 nps 772499 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 f8e7 g1f3 g8f6 f1d3 f6e4 d3e4 e8g8 e1g1 b8d7 f1e1 d7f6 e4d3 d8d6 c1g5 c8d7
info multipv 1 depth 23 seldepth 30 score cp 40 time 27755 nodes 21571682 nps 777217 pv e2e4 e7e6 d2d4
info multipv 1 depth 24 seldepth 30 score cp 34 time 41720 nodes 29162974 nps 699016 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 f8e7 g1f3 g8f6 e4f6 e7f6 f1c4 b8c6 c2c3 e8g8 e1g1 d8d6 c1e3 c8d7 f1e1 a8d8 d1b3 d7c8
info multipv 1 depth 25 seldepth 32 score cp 30 time 91435 nodes 64704945 nps 707660 pv e2e4 e7e6 d2d4 d7d5 b1c3 g8f6 e4
e5 f6e4 c3e4 d5e4 f1b5 b8c6 b5c6 b7c6 g1e2 c8a6 e1g1 f8e7 f1e1 c6c5
bestmove e2e4

Score of Altair1.1.2 vs Altair1.1.1: 104 - 79 - 117 [0.542]
...      Altair1.1.2 playing White: 43 - 48 - 59  [0.483] 150
...      Altair1.1.2 playing Black: 61 - 31 - 58  [0.600] 150
...      White vs Black: 74 - 109 - 117  [0.442] 300
Elo difference: 29.0 +/- 30.8, LOS: 96.8 %, DrawRatio: 39.0 %
300 of 300 games finished.

Score of Altair1.1.2 vs Vice10-64: 414 - 41 - 45 [0.873]
...      Altair1.1.2 playing White: 208 - 23 - 19  [0.870] 250
...      Altair1.1.2 playing Black: 206 - 18 - 26  [0.876] 250
...      White vs Black: 226 - 229 - 45  [0.497] 500
Elo difference: 334.9 +/- 41.3, LOS: 100.0 %, DrawRatio: 9.0 %
500 of 500 games finished.

Score of Altair1.1.2 vs Altair1.0.1: 92 - 23 - 85 [0.672]
...      Altair1.1.2 playing White: 47 - 9 - 44  [0.690] 100
...      Altair1.1.2 playing Black: 45 - 14 - 41  [0.655] 100
...      White vs Black: 61 - 54 - 85  [0.517] 200
Elo difference: 125.0 +/- 37.0, LOS: 100.0 %, DrawRatio: 42.5 %
200 of 200 games finished.

STS Rating v14.2
Engine: Altair
Hash: 128, Threads: 1, time/pos: 0.150s

Number of positions in ./epd/STS1-STS15_LAN_v4.epd: 1500
Max score = 1500 x 10 = 15000
Test duration: 00h:03m:36s
Expected time to finish: 00h:04m:30s
STS rating: 2770

  STS ID   STS1   STS2   STS3   STS4   STS5   STS6   STS7   STS8   STS9  STS10  STS11  STS12  STS13  STS14  STS15    ALL
  NumPos    100    100    100    100    100    100    100    100    100    100    100    100    100    100    100   1500
 BestCnt     46     34     49     34     58     50     35     23     28     54     14     44     49     51     22    591
   Score    693    595    673    613    802    890    628    487    550    812    551    730    759    739    628  10150
Score(%)   69.3   59.5   67.3   61.3   80.2   89.0   62.8   48.7   55.0   81.2   55.1   73.0   75.9   73.9   62.8   67.7
  Rating   2843   2406   2754   2486   3328   3720   2553   1925   2206   3372   2210   3007   3136   3047   2553   2770

:: STS ID and Titles ::
STS 01: Undermining
STS 02: Open Files and Diagonals
STS 03: Knight Outposts
STS 04: Square Vacancy
STS 05: Bishop vs Knight
STS 06: Re-Capturing
STS 07: Offer of Simplification
STS 08: Advancement of f/g/h Pawns
STS 09: Advancement of a/b/c Pawns
STS 10: Simplification
STS 11: Activity of the King
STS 12: Center Control
STS 13: Pawn Play in the Center
STS 14: Queens and Rooks to the 7th rank
STS 15: Avoid Pointless Exchange

:: Top 5 STS with high result ::
1. STS 06, 89.0%, "Re-Capturing"
2. STS 10, 81.2%, "Simplification"
3. STS 05, 80.2%, "Bishop vs Knight"
4. STS 13, 75.9%, "Pawn Play in the Center"
5. STS 14, 73.9%, "Queens and Rooks to the 7th rank"

:: Top 5 STS with low result ::
1. STS 08, 48.7%, "Advancement of f/g/h Pawns"
2. STS 09, 55.0%, "Advancement of a/b/c Pawns"
3. STS 11, 55.1%, "Activity of the King"
4. STS 02, 59.5%, "Open Files and Diagonals"
5. STS 04, 61.3%, "Square Vacancy"

STS Rating v14.2
Engine: Altair
Hash: 128, Threads: 1, time/pos: 1.000s

Number of positions in ./epd/STS1-STS15_LAN_v4.epd: 1500
Max score = 1500 x 10 = 15000
Test duration: 00h:20m:21s
Expected time to finish: 00h:25m:45s

  STS ID   STS1   STS2   STS3   STS4   STS5   STS6   STS7   STS8   STS9  STS10  STS11  STS12  STS13  STS14  STS15    ALL
  NumPos    100    100    100    100    100    100    100    100    100    100    100    100    100    100    100   1500
 BestCnt     49     41     54     41     58     51     43     29     32     57     28     48     50     52     29    662
   Score    724    653    728    649    823    884    705    582    604    847    592    762    768    789    689  10799
Score(%)   72.4   65.3   72.8   64.9   82.3   88.4   70.5   58.2   60.4   84.7   59.2   76.2   76.8   78.9   68.9   72.0

:: STS ID and Titles ::
STS 01: Undermining
STS 02: Open Files and Diagonals
STS 03: Knight Outposts
STS 04: Square Vacancy
STS 05: Bishop vs Knight
STS 06: Re-Capturing
STS 07: Offer of Simplification
STS 08: Advancement of f/g/h Pawns
STS 09: Advancement of a/b/c Pawns
STS 10: Simplification
STS 11: Activity of the King
STS 12: Center Control
STS 13: Pawn Play in the Center
STS 14: Queens and Rooks to the 7th rank
STS 15: Avoid Pointless Exchange

:: Top 5 STS with high result ::
1. STS 06, 88.4%, "Re-Capturing"
2. STS 10, 84.7%, "Simplification"
3. STS 05, 82.3%, "Bishop vs Knight"
4. STS 14, 78.9%, "Queens and Rooks to the 7th rank"
5. STS 13, 76.8%, "Pawn Play in the Center"

:: Top 5 STS with low result ::
1. STS 08, 58.2%, "Advancement of f/g/h Pawns"
2. STS 11, 59.2%, "Activity of the King"
3. STS 09, 60.4%, "Advancement of a/b/c Pawns"
4. STS 04, 64.9%, "Square Vacancy"
5. STS 02, 65.3%, "Open Files and Diagonals"
```


### 1.1.3
Improving Drawishness calculator. Hand tuning some other eval terms.

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 3 nodes 251 nps 83666 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 5 nodes 910 nps 182000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 7 nodes 1510 nps 215714 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 12 nodes 3891 nps 324250 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 32 time 18 nodes 7371 nps 409500 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 c1f4
info multipv 1 depth 8 seldepth 10 score cp 7 time 38 nodes 22311 nps 587131 pv b1c3 d7d5 g1f3 g8f6 d2d4
info multipv 1 depth 9 seldepth 11 score cp 29 time 55 nodes 34281 nps 623290 pv b1c3 d7d5 d2d4 e7e6 g1f3 b8c6 e2e4 g8f6

info multipv 1 depth 10 seldepth 13 score cp 13 time 130 nodes 85337 nps 656438 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 d8
d6 c3b5 d6b4 b5c3
info multipv 1 depth 11 seldepth 13 score cp 29 time 176 nodes 122751 nps 697448 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 f
6e4 c3e4 d5e4 f3g5
info multipv 1 depth 12 seldepth 16 score cp 31 time 222 nodes 158156 nps 712414 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c
8f5 f1d3 f6e4 c3e4 d5e4
info multipv 1 depth 13 seldepth 17 score cp 42 time 975 nodes 727225 nps 745871 pv e2e4 e7e6 d2d4 g8f6 e4e5 f6e4 b1d2 d
7d5 d2e4 d5e4 c1f4 b8c6 g1e2
info multipv 1 depth 14 seldepth 18 score cp 36 time 1260 nodes 948751 nps 752976 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4
e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 19 score cp 21 time 1560 nodes 1183600 nps 758717 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 16 seldepth 20 score cp 23 time 2046 nodes 1563994 nps 764415 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b5
 f8b4 a2a3 b4c5 e1g1 e8g8 b2b4 c5b6 b5c6 d7c6
info multipv 1 depth 17 seldepth 23 score cp 21 time 2738 nodes 2114003 nps 772097 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b5
 f8b4 a2a3 b4c3 d2c3 f6e4 e1g1 d7d6 d1d5 c8f5 c1e3
info multipv 1 depth 18 seldepth 23 score cp 24 time 3885 nodes 3021191 nps 777655 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b5
 f8c5 e1g1 e8g8 d2d3 c6d4 f3d4 c5d4 c3e2 d4c5 c1e3 d7d6
info multipv 1 depth 19 seldepth 25 score cp 37 time 5379 nodes 4204676 nps 781683 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4
 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 d7d5 e4e5 f6e4 e1g1 e4c3 b2c3
info multipv 1 depth 20 seldepth 27 score cp 37 time 7572 nodes 5813321 nps 767739 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 21 seldepth 28 score cp 26 time 16531 nodes 11191162 nps 676980 pv e2e4 e7e5 b1c3 b8c6 g1f3 f8c5 f3
e5 g8f6 e5c6 d7c6 f1e2 e8g8 e1g1 f8e8 e2f3 d8d6 d2d3 c8e6 c1g5 c5d4 a1c1
info multipv 1 depth 22 seldepth 28 score cp 26 time 22572 nodes 15642319 nps 692996 pv e2e4 e7e5 b1c3 b8c6
info multipv 1 depth 23 seldepth 28 score cp 28 time 30801 nodes 21698656 nps 704478 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 b4c5 d4a4 e8g8 e1g1 a8b8 f1d1 e7e6
info multipv 1 depth 23 seldepth 31 score cp 28 time 44999 nodes 28944443 nps 643224 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 b4c5 d4a4 e8g8 e1g1 a8b8 f1d1 e7e6
bestmove e2e4

Score of Altair1.1.3 vs Altair1.1.2: 97 - 86 - 117 [0.518]
...      Altair1.1.3 playing White: 45 - 46 - 59  [0.497] 150
...      Altair1.1.3 playing Black: 52 - 40 - 58  [0.540] 150
...      White vs Black: 85 - 98 - 117  [0.478] 300
Elo difference: 12.7 +/- 30.8, LOS: 79.2 %, DrawRatio: 39.0 %
300 of 300 games finished.

1 min
Score of Altair1.1.3 vs cinnamon_2.4_x64-INTEL: 61 - 36 - 23 [0.604]
...      Altair1.1.3 playing White: 27 - 20 - 13  [0.558] 60
...      Altair1.1.3 playing Black: 34 - 16 - 10  [0.650] 60
...      White vs Black: 43 - 54 - 23  [0.454] 120
Elo difference: 73.5 +/- 57.3, LOS: 99.4 %, DrawRatio: 19.2 %
120 of 120 games finished.

Score of Altair1.1.3 vs bienchen.1.0: 482 - 328 - 190 [0.577]
...      Altair1.1.3 playing White: 242 - 167 - 91  [0.575] 500
...      Altair1.1.3 playing Black: 240 - 161 - 99  [0.579] 500
...      White vs Black: 403 - 407 - 190  [0.498] 1000
Elo difference: 53.9 +/- 19.6, LOS: 100.0 %, DrawRatio: 19.0 %
1000 of 1000 games finished.

Score of Altair1.1.3 vs tantabus-windows-2019-x86-64-v3: 291 - 499 - 210 [0.396]
...      Altair1.1.3 playing White: 141 - 256 - 103  [0.385] 500
...      Altair1.1.3 playing Black: 150 - 243 - 107  [0.407] 500
...      White vs Black: 384 - 406 - 210  [0.489] 1000
Elo difference: -73.3 +/- 19.4, LOS: 0.0 %, DrawRatio: 21.0 %
1000 of 1000 games finished.

Score of Altair1.1.3 vs Cosette-Win64: 173 - 228 - 99 [0.445]
...      Altair1.1.3 playing White: 90 - 118 - 42  [0.444] 250
...      Altair1.1.3 playing Black: 83 - 110 - 57  [0.446] 250
...      White vs Black: 200 - 201 - 99  [0.499] 500
Elo difference: -38.4 +/- 27.4, LOS: 0.3 %, DrawRatio: 19.8 %
500 of 500 games finished.

Score of Altair1.1.3 vs kimbo-0.3.0: 355 - 431 - 214 [0.462]
...      Altair1.1.3 playing White: 184 - 207 - 109  [0.477] 500
...      Altair1.1.3 playing Black: 171 - 224 - 105  [0.447] 500
...      White vs Black: 408 - 378 - 214  [0.515] 1000
Elo difference: -26.5 +/- 19.1, LOS: 0.3 %, DrawRatio: 21.4 %
1000 of 1000 games finished.

1 min
Score of Altair1.1.3 vs eggnog-chess-engine-avx2-win: 33 - 23 - 4 [0.583]
...      Altair1.1.3 playing White: 23 - 6 - 1  [0.783] 30
...      Altair1.1.3 playing Black: 10 - 17 - 3  [0.383] 30
...      White vs Black: 40 - 16 - 4  [0.700] 60
Elo difference: 58.5 +/- 87.9, LOS: 90.9 %, DrawRatio: 6.7 %
60 of 60 games finished.
```

### 1.1.4
set_state function to eliminate repeated tasks;
improving for RFP

```
Depth 6 startpos
Move a2a3: 4463267
Move a2a4: 5363555
Move b2b3: 5310358
Move b2b4: 5293555
Move c2c3: 5417640
Move c2c4: 5866666
Move d2d3: 8073082
Move d2d4: 8879566
Move e2e3: 9726018
Move e2e4: 9771632
Move f2f3: 4404141
Move f2f4: 4890429
Move g2g3: 5346260
Move g2g4: 5239875
Move h2h3: 4463070
Move h2h4: 5385554
Move b1a3: 4856835
Move b1c3: 5708064
Move g1f3: 5723523
Move g1h3: 4877234
Nodes searched: 119060324
Perft speed: 13.6521mn/s
Total time: 8721

info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 2 nodes 251 nps 125500 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 4 nodes 909 nps 227250 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 6 nodes 1507 nps 251166 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 10 nodes 3885 nps 388500 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 32 time 15 nodes 7339 nps 489266 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 c1f4
info multipv 1 depth 8 seldepth 10 score cp 7 time 29 nodes 18723 nps 645620 pv b1c3 d7d5 g1f3 g8f6 d2d4
info multipv 1 depth 9 seldepth 12 score cp 30 time 51 nodes 35772 nps 701411 pv b1c3 d7d5 d2d4 b8c6 g1f3 g8f6
info multipv 1 depth 10 seldepth 13 score cp 16 time 100 nodes 74340 nps 743400 pv g1f3 b8c6 e2e4 g8f6 b1c3 d7d5 e4e5 f6
e4 c3e4 d5e4
info multipv 1 depth 11 seldepth 14 score cp 25 time 168 nodes 131075 nps 780208 pv g1f3 d7d5 d2d4 g8f6 b1c3 d8d6 d1d3 b
8c6 e2e4 c8g4 e4e5
info multipv 1 depth 12 seldepth 16 score cp 20 time 247 nodes 195014 nps 789530 pv g1f3 d7d5 d2d4 g8f6 b1c3 e7e6 e2e3 b
8d7 f1d3 f8d6 e1g1 e8g8
info multipv 1 depth 13 seldepth 17 score cp 21 time 395 nodes 309104 nps 782541 pv g1f3 d7d5 d2d4 g8f6 e2e3 b8d7 f1d3 e
7e6 e1g1 f8d6 b1c3
info multipv 1 depth 14 seldepth 18 score cp 15 time 665 nodes 533818 nps 802733 pv g1f3 d7d5 e2e3 g8f6 b1c3 b8d7 d2d4 e
7e6 f1d3 f8b4 e1g1 e8g8 c1d2
info multipv 1 depth 15 seldepth 20 score cp 21 time 1523 nodes 1239707 nps 813990 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 16 seldepth 21 score cp 37 time 2052 nodes 1685260 nps 821276 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8 d2d3 d7d6 c3d5 h7h6 c1e3 c5e3
info multipv 1 depth 17 seldepth 22 score cp 37 time 3421 nodes 2808447 nps 820943 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8 d2d3 d7d6 c3d5 h7h6 c1e3 c5e3 f2e3
info multipv 1 depth 18 seldepth 24 score cp 45 time 5692 nodes 4665386 nps 819639 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5 b4c3 b2c3 d8e8 g5f6
info multipv 1 depth 19 seldepth 26 score cp 43 time 8072 nodes 6592914 nps 816763 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4
 b8c6 g1f3 f8e7 f1b5 g8f6 e4f6 e7f6 b5c6 b7c6 e1g1 e8g8 f3e5 a8b8 e5c6
info multipv 1 depth 20 seldepth 26 score cp 39 time 11229 nodes 9155235 nps 815320 pv e2e4 e7e6 d2d4 d7d5 b1c3 f8b4 e4e
5 g8e7 g1f3 e8g8 f1e2 c7c5 e1g1 c5d4 c3b5 b8c6 b5d4 c8d7 c1g5 a8c8
info multipv 1 depth 21 seldepth 28 score cp 34 time 19810 nodes 15578199 nps 786380 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2
d4 b8c6 f1b5 f8b4 c1d2 b4d2 d1d2 g8e7 e1g1 e8g8 b1c3 c8g4 f3e5 c6e5 d4e5 a8c8
info multipv 1 depth 22 seldepth 29 score cp 37 time 26750 nodes 20848104 nps 779368 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4
info multipv 1 depth 22 seldepth 31 score cp 37 time 45001 nodes 34895911 nps 775447 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4
bestmove e2e4

Score of Altair1.1.4 vs Altair1.1.3: 105 - 84 - 161 [0.530]
...      Altair1.1.4 playing White: 54 - 42 - 79  [0.534] 175
...      Altair1.1.4 playing Black: 51 - 42 - 82  [0.526] 175
...      White vs Black: 96 - 93 - 161  [0.504] 350
Elo difference: 20.9 +/- 26.8, LOS: 93.7 %, DrawRatio: 46.0 %
350 of 350 games finished.
```


### 1.1.5
Improving Heuristic for LMR

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 2 nodes 109 nps 54500 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 63 time 4 nodes 251 nps 62750 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 6 nodes 909 nps 151500 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 52 time 7 nodes 1507 nps 215285 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 11 nodes 3906 nps 355090 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 9 score cp 32 time 17 nodes 7430 nps 437058 pv b1c3 b8c6 g1f3 d7d5 d2d4 g8f6 c1f4
info multipv 1 depth 8 seldepth 10 score cp 16 time 26 nodes 14314 nps 550538 pv b1c3 b8c6 g1f3 d7d5 e2e4 g8f6 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 16 time 44 nodes 26659 nps 605886 pv b1c3 b8c6 e2e4 g8f6 g1f3 d7d5 e4e5
info multipv 1 depth 10 seldepth 13 score cp 16 time 109 nodes 74298 nps 681633 pv b1c3 b8c6 e2e4 g8f6 g1f3 d7d5 e4e5 f6
e4 c3e4 d5e4
info multipv 1 depth 11 seldepth 15 score cp 31 time 235 nodes 173881 nps 739919 pv d2d4 d7d5 g1f3 g8f6 e2e3 b8c6 b1c3 c
8f5 f1d3 f6e4 c3e4
info multipv 1 depth 12 seldepth 15 score cp 34 time 440 nodes 340964 nps 774918 pv g1f3 b8c6 b1c3 d7d5 d2d4 g8f6 e2e3
info multipv 1 depth 13 seldepth 17 score cp 34 time 1142 nodes 805742 nps 705553 pv b1c3 d7d5 d2d4 b8c6 g1f3 g8f6
info multipv 1 depth 14 seldepth 18 score cp 38 time 1992 nodes 1290934 nps 648059 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4
 e7e6 c2c4 d5f6 b1c3 b8c6 c1f4 f8b4
info multipv 1 depth 15 seldepth 19 score cp 21 time 2845 nodes 1910080 nps 671381 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 16 seldepth 21 score cp 25 time 3610 nodes 2509503 nps 695153 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 c1g5 f8b4 c2c3 b4e7 b1d2 h8e8
info multipv 1 depth 17 seldepth 22 score cp 31 time 4542 nodes 3267653 nps 719430 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 d8f6 d4f5 g8e7 f5e3 f6d4 d1d4 c6d4 b1c3 d7d6 f1c4
info multipv 1 depth 18 seldepth 25 score cp 36 time 9002 nodes 6522661 nps 724579 pv e2e4 e7e6 d2d4 d7d5 b1d2 d5e4 d2e4
 b8c6 g1f3 f8e7 f1c4 g8f6 e4f6 e7f6 c1e3 e8g8 e1g1 d8d6 d1d3
info multipv 1 depth 19 seldepth 26 score cp 36 time 10969 nodes 7883094 nps 718670 pv e2e4 e7e6 d2d4 d7d5 b1d2 d5e4 d2e
4 b8c6 g1f3 f8e7 f1c4 g8f6
info multipv 1 depth 20 seldepth 27 score cp 36 time 13802 nodes 10015852 nps 725681 pv e2e4 e7e6 d2d4 d7d5 b1d2 d5e4 d2
e4
info multipv 1 depth 21 seldepth 27 score cp 36 time 20383 nodes 14870475 nps 729552 pv e2e4 e7e6
info multipv 1 depth 22 seldepth 29 score cp 37 time 30886 nodes 23448163 nps 759184 pv e2e4 e7e6 d2d4 d7d5 b1c3 g8f6 e4
e5 f6e4 c3e4 d5e4 g1e2 c7c5 c1e3 b8c6 d4c5 d8a5 e2c3 f8c5 e3c5 a5c5 c3e4
info multipv 1 depth 23 seldepth 29 score cp 36 time 42260 nodes 32715717 nps 774153 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 f8e7 g1f3 g8f6 f1d3 e8g8 e1g1 f6e4 d3e4 b8d7 f1e1 d7f6 e4d3 e7b4 c1d2
bestmove e2e4

Score of Altair1.1.5 vs Altair1.1.4: 103 - 103 - 144 [0.500]
...      Altair1.1.5 playing White: 50 - 53 - 72  [0.491] 175
...      Altair1.1.5 playing Black: 53 - 50 - 72  [0.509] 175
...      White vs Black: 100 - 106 - 144  [0.491] 350
Elo difference: 0.0 +/- 27.9, LOS: 50.0 %, DrawRatio: 41.1 %
350 of 350 games finished.
```


### 1.1.6
Calculating Tropism with abs(x_dif) + abs(y_dif) instead of using the distance formula


```
info multipv 1 depth 1 seldepth 1 score cp 64 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 65 time 3 nodes 253 nps 84333 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 5 nodes 759 nps 151800 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 51 time 7 nodes 1719 nps 245571 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 11 nodes 4273 nps 388454 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 32 time 16 nodes 7633 nps 477062 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 7 time 54 nodes 34254 nps 634333 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4
info multipv 1 depth 9 seldepth 12 score cp 30 time 68 nodes 45366 nps 667147 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info multipv 1 depth 10 seldepth 12 score cp 16 time 135 nodes 101402 nps 751125 pv b1c3 d7d5 d2d4 c8f5 g1f3 g8f6 e2e3 b
8c6 f1d3 e7e6
info multipv 1 depth 11 seldepth 14 score cp 24 time 188 nodes 143039 nps 760845 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c
8g4 f1e2 f6e4 c3e4
info multipv 1 depth 12 seldepth 16 score cp 30 time 413 nodes 321016 nps 777278 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 f3e5 c
8f5 e5c6 b7c6 c1f4 e7e6
info multipv 1 depth 13 seldepth 18 score cp 39 time 803 nodes 644779 nps 802962 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 b
8c6 b1c3 g8f6 f1e2 f6e4 e1g1
info multipv 1 depth 14 seldepth 18 score cp 39 time 1174 nodes 948692 nps 808085 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 20 score cp 33 time 1572 nodes 1279267 nps 813783 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 d1d8 e8d8
info multipv 1 depth 16 seldepth 21 score cp 36 time 2092 nodes 1710638 nps 817704 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 d1d8 e8d8 c1g5 d8e8
info multipv 1 depth 17 seldepth 23 score cp 36 time 2986 nodes 2379490 nps 796882 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5

info multipv 1 depth 18 seldepth 25 score cp 31 time 4233 nodes 3395289 nps 802099 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 b5c6 b7c6 d1d8 e8d8 c1g5 d8e8
info multipv 1 depth 19 seldepth 25 score cp 14 time 8524 nodes 6531044 nps 766194 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 f3e5
 d7d5 b1d2 b8d7 d1e2 d7e5 d4e5 e4c5 e2f3 c7c6 f1e2 c8e6
info multipv 1 depth 20 seldepth 27 score cp 26 time 22538 nodes 16657710 nps 739094 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6
info multipv 1 depth 21 seldepth 27 score cp 26 time 26321 nodes 19714479 nps 749001 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 e8g8
info multipv 1 depth 22 seldepth 27 score cp 26 time 32311 nodes 24464413 nps 757154 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6
bestmove e2e4

Score of Altair1.1.6 vs Altair1.1.5: 94 - 90 - 116 [0.507]
...      Altair1.1.6 playing White: 43 - 47 - 60  [0.487] 150
...      Altair1.1.6 playing Black: 51 - 43 - 56  [0.527] 150
...      White vs Black: 86 - 98 - 116  [0.480] 300
Elo difference: 4.6 +/- 30.8, LOS: 61.6 %, DrawRatio: 38.7 %
300 of 300 games finished.
```


### 1.1.7
Make is_attacked() function more efficient
17M nps perft now

```
info multipv 1 depth 1 seldepth 1 score cp 64 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 65 time 3 nodes 253 nps 84333 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 5 nodes 759 nps 151800 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 51 time 6 nodes 1719 nps 286500 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 11 nodes 4273 nps 388454 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 32 time 17 nodes 7633 nps 449000 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 7 time 49 nodes 34254 nps 699061 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4
info multipv 1 depth 9 seldepth 12 score cp 30 time 63 nodes 45366 nps 720095 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info multipv 1 depth 10 seldepth 12 score cp 16 time 127 nodes 101402 nps 798440 pv b1c3 d7d5 d2d4 c8f5 g1f3 g8f6 e2e3 b
8c6 f1d3 e7e6
info multipv 1 depth 11 seldepth 14 score cp 24 time 175 nodes 143039 nps 817365 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c
8g4 f1e2 f6e4 c3e4
info multipv 1 depth 12 seldepth 16 score cp 30 time 378 nodes 321016 nps 849248 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 f3e5 c
8f5 e5c6 b7c6 c1f4 e7e6
info multipv 1 depth 13 seldepth 18 score cp 39 time 757 nodes 644779 nps 851755 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 b
8c6 b1c3 g8f6 f1e2 f6e4 e1g1
info multipv 1 depth 14 seldepth 18 score cp 39 time 1103 nodes 948692 nps 860101 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 20 score cp 33 time 1478 nodes 1279267 nps 865539 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 d1d8 e8d8
info multipv 1 depth 16 seldepth 21 score cp 36 time 1954 nodes 1710638 nps 875454 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 d1d8 e8d8 c1g5 d8e8
info multipv 1 depth 17 seldepth 23 score cp 36 time 2715 nodes 2379490 nps 876423 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5

info multipv 1 depth 18 seldepth 25 score cp 31 time 3839 nodes 3395289 nps 884420 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 b5c6 b7c6 d1d8 e8d8 c1g5 d8e8
info multipv 1 depth 19 seldepth 25 score cp 14 time 7439 nodes 6531044 nps 877946 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 f3e5
 d7d5 b1d2 b8d7 d1e2 d7e5 d4e5 e4c5 e2f3 c7c6 f1e2 c8e6
info multipv 1 depth 20 seldepth 27 score cp 26 time 19446 nodes 16657710 nps 856613 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6
info multipv 1 depth 21 seldepth 27 score cp 26 time 23234 nodes 19714479 nps 848518 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 e8g8
info multipv 1 depth 22 seldepth 27 score cp 26 time 28601 nodes 24464413 nps 855369 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6
info multipv 1 depth 22 seldepth 32 score cp 26 time 45002 nodes 37711887 nps 838004 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6
bestmove e2e4

Score of Altair1.1.7 vs Altair1.1.6: 155 - 108 - 137 [0.559]
...      Altair1.1.7 playing White: 75 - 60 - 65  [0.537] 200
...      Altair1.1.7 playing Black: 80 - 48 - 72  [0.580] 200
...      White vs Black: 123 - 140 - 137  [0.479] 400
Elo difference: 41.0 +/- 27.7, LOS: 99.8 %, DrawRatio: 34.3 %
400 of 400 games finished.
```


### 1.1.8
Piece List Index board to keep track of the piece's index in the piece lists.
Perft now at 20M nps.

```
info multipv 1 depth 1 seldepth 1 score cp 64 time 0 nodes 27 nps 270000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 109 nps 109000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 65 time 2 nodes 253 nps 126500 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 4 nodes 759 nps 189750 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 51 time 6 nodes 1719 nps 286500 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 9 nodes 4273 nps 474777 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 32 time 14 nodes 7633 nps 545214 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 7 time 43 nodes 34254 nps 796604 pv b1c3 d7d5 g1f3 g8f6 d2d4 b8c6 c1f4
info multipv 1 depth 9 seldepth 12 score cp 30 time 56 nodes 45366 nps 810107 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6
info multipv 1 depth 10 seldepth 12 score cp 16 time 116 nodes 101402 nps 874155 pv b1c3 d7d5 d2d4 c8f5 g1f3 g8f6 e2e3 b
8c6 f1d3 e7e6
info multipv 1 depth 11 seldepth 14 score cp 24 time 165 nodes 143039 nps 866903 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 e2e3 c
8g4 f1e2 f6e4 c3e4
info multipv 1 depth 12 seldepth 16 score cp 30 time 357 nodes 321016 nps 899204 pv b1c3 d7d5 d2d4 g8f6 g1f3 b8c6 f3e5 c
8f5 e5c6 b7c6 c1f4 e7e6
info multipv 1 depth 13 seldepth 18 score cp 39 time 705 nodes 644779 nps 914580 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 b
8c6 b1c3 g8f6 f1e2 f6e4 e1g1
info multipv 1 depth 14 seldepth 18 score cp 39 time 1033 nodes 948692 nps 918385 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
e5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 20 score cp 33 time 1387 nodes 1279267 nps 922326 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 d1d8 e8d8
info multipv 1 depth 16 seldepth 21 score cp 36 time 1838 nodes 1710638 nps 930706 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 d1d8 e8d8 c1g5 d8e8
info multipv 1 depth 17 seldepth 23 score cp 36 time 2555 nodes 2379490 nps 931307 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5

info multipv 1 depth 18 seldepth 25 score cp 31 time 3615 nodes 3395289 nps 939222 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8c5 d2e4 d5e4 b5c6 b7c6 d1d8 e8d8 c1g5 d8e8
info multipv 1 depth 19 seldepth 25 score cp 14 time 7108 nodes 6531044 nps 918830 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 f3e5
 d7d5 b1d2 b8d7 d1e2 d7e5 d4e5 e4c5 e2f3 c7c6 f1e2 c8e6
info multipv 1 depth 20 seldepth 27 score cp 26 time 19042 nodes 16657710 nps 874787 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6
info multipv 1 depth 21 seldepth 27 score cp 26 time 22456 nodes 19714479 nps 877915 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 e8g8
info multipv 1 depth 22 seldepth 27 score cp 26 time 27563 nodes 24464413 nps 887581 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6
info multipv 1 depth 22 seldepth 32 score cp 26 time 45001 nodes 39346176 nps 874340 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6
bestmove e2e4

Score of Altair1.1.8 vs Altair1.1.7: 138 - 138 - 124 [0.500]
...      Altair1.1.8 playing White: 68 - 69 - 63  [0.497] 200
...      Altair1.1.8 playing Black: 70 - 69 - 61  [0.502] 200
...      White vs Black: 137 - 139 - 124  [0.497] 400
Elo difference: 0.0 +/- 28.3, LOS: 50.0 %, DrawRatio: 31.0 %
400 of 400 games finished.

Score of Altair1.1.8 vs Altair1.0.0: 165 - 58 - 127 [0.653]
...      Altair1.1.8 playing White: 79 - 35 - 61  [0.626] 175
...      Altair1.1.8 playing Black: 86 - 23 - 66  [0.680] 175
...      White vs Black: 102 - 121 - 127  [0.473] 350
Elo difference: 109.7 +/- 29.7, LOS: 100.0 %, DrawRatio: 36.3 %
350 of 350 games finished.

Score of Altair1.1.8 vs sofcheck_amd64-popcnt_windows: 99 - 53 - 48 [0.615]
...      Altair1.1.8 playing White: 50 - 29 - 21  [0.605] 100
...      Altair1.1.8 playing Black: 49 - 24 - 27  [0.625] 100
...      White vs Black: 74 - 78 - 48  [0.490] 200
Elo difference: 81.4 +/- 42.9, LOS: 100.0 %, DrawRatio: 24.0 %
200 of 200 games finished.
```


### 1.1.9
Mobility changes. More bonus for attacking opponent's pieces with the bishop and knight

```
info multipv 1 depth 1 seldepth 1 score cp 64 time 0 nodes 28 nps 280000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 2 nodes 110 nps 55000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 252 nps 84000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 5 score cp 8 time 6 nodes 910 nps 151666 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 53 time 9 nodes 1843 nps 204777 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 13 nodes 4428 nps 340615 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6
info multipv 1 depth 7 seldepth 9 score cp 33 time 20 nodes 10868 nps 543400 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 17 time 32 nodes 19955 nps 623593 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 23 time 58 nodes 43218 nps 745137 pv b1c3 b8c6 d2d4 d7d5 d1d3 g8f6 g1f3 c6b4
 d3b5 b4c6
info multipv 1 depth 10 seldepth 14 score cp 20 time 136 nodes 109954 nps 808485 pv g1f3 g8f6 d2d4 d7d5 b1c3 c8f5 e2e3 b
8c6 f1d3 e7e6
info multipv 1 depth 11 seldepth 15 score cp 22 time 179 nodes 147757 nps 825458 pv g1f3 g8f6 d2d4 d7d5 b1c3 b8c6 d1d3 e
7e6 e2e4 f8b4 e4e5
info multipv 1 depth 12 seldepth 16 score cp 28 time 237 nodes 200976 nps 848000 pv g1f3 g8f6 d2d4 d7d5 b1c3 b8c6 e2e3 e
7e6 f1b5 f8b4 b5c6 b7c6 e1g1
info multipv 1 depth 13 seldepth 17 score cp 22 time 723 nodes 641333 nps 887044 pv g1f3 g8f6 d2d4 d7d5 b1c3 e7e6 e2e3 f
8b4 d1d3 b8c6 a2a3 b4d6 f1e2
info multipv 1 depth 14 seldepth 19 score cp 37 time 1653 nodes 1489554 nps 901121 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3
 b8c6 b1c3 f8b4
info multipv 1 depth 15 seldepth 20 score cp 40 time 1960 nodes 1772177 nps 904171 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4
 g8f6 e4f6 d8f6 g1f3 b8c6 c1g5 f6f5 f1d3 f8b4 c2c3
info multipv 1 depth 16 seldepth 22 score cp 46 time 3170 nodes 2870261 nps 905445 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4
 b8d7 g1f3 g8f6 f1d3 f6e4 d3e4 d7f6 c1g5 f8b4 c2c3
info multipv 1 depth 17 seldepth 23 score cp 40 time 4401 nodes 3997849 nps 908395 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5 d8e8 g5f6 g7f6
info multipv 1 depth 18 seldepth 25 score cp 40 time 5592 nodes 5027333 nps 899022 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5
info multipv 1 depth 19 seldepth 25 score cp 40 time 6787 nodes 6114013 nps 900841 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4

info multipv 1 depth 20 seldepth 29 score cp 29 time 10531 nodes 9425225 nps 894998 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d
4 d8f6 d4f3 f8c5 b1c3 g8e7 c1g5 f6e6 f1e2 e8g8 e1g1 h7h6 g5f4 d7d6
info multipv 1 depth 21 seldepth 29 score cp 29 time 13296 nodes 11916733 nps 896264 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3
d4
info multipv 1 depth 22 seldepth 29 score cp 29 time 16779 nodes 15011614 nps 894666 pv e2e4 e7e5 g1f3
info multipv 1 depth 23 seldepth 29 score cp 29 time 23056 nodes 20673582 nps 896668 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3
d4 d8f6 d4b5 f8c5 d1d2 c5b6 b1c3 g8e7 d2f4 f6e5 c1e3 e8g8 a1d1 b6e3 f4e3
info multipv 1 depth 24 seldepth 31 score cp 24 time 36650 nodes 32394659 nps 883892 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 e8g8 e1g1 d7d5 e4d5 c6d5 c1g5 h7h6 g5f6 d8f6 c3d5
bestmove e2e4

Score of Altair1.1.9 vs Altair1.1.8: 131 - 123 - 146 [0.510]
...      Altair1.1.9 playing White: 67 - 59 - 74  [0.520] 200
...      Altair1.1.9 playing Black: 64 - 64 - 72  [0.500] 200
...      White vs Black: 131 - 123 - 146  [0.510] 400
Elo difference: 6.9 +/- 27.2, LOS: 69.2 %, DrawRatio: 36.5 %
400 of 400 games finished.
```


### 1.2.0
Improving for Razoring (no other engine does this?)


```
info multipv 1 depth 1 seldepth 1 score cp 64 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 252 nps 84000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 5 score cp 8 time 5 nodes 910 nps 182000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 53 time 6 nodes 1844 nps 307333 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 10 nodes 4431 nps 443100 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6
info multipv 1 depth 7 seldepth 9 score cp 33 time 19 nodes 10872 nps 572210 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 17 time 30 nodes 19983 nps 666100 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 23 time 57 nodes 43200 nps 757894 pv b1c3 b8c6 d2d4 d7d5 d1d3 g8f6 g1f3 c6b4
 d3b5 b4c6
info multipv 1 depth 10 seldepth 14 score cp 25 time 116 nodes 94489 nps 814560 pv b1c3 d7d5 d2d4 g8f6 d1d3 e7e6 g1f3 b8
c6 e2e4 f8b4
info multipv 1 depth 11 seldepth 15 score cp 25 time 232 nodes 195504 nps 842689 pv g1f3 g8f6 e2e3 b8c6 d2d4 d7d5 b1c3 c
8g4
info multipv 1 depth 12 seldepth 16 score cp 28 time 352 nodes 290555 nps 825440 pv g1f3 g8f6 d2d4 d7d5 b1c3 b8c6 e2e3
info multipv 1 depth 13 seldepth 18 score cp 7 time 995 nodes 861161 nps 865488 pv g1f3 g8f6 d2d4 d7d5 b1c3 e7e6 e2e3 f8
d6 f1d3 b8c6 e1g1 e8g8 c1d2
info multipv 1 depth 14 seldepth 18 score cp 39 time 1504 nodes 1317838 nps 876222 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4
 d5b4 d1a4 b8c6 a2a3 e7e5 a3b4 e5d4 c1d2
info multipv 1 depth 15 seldepth 20 score cp 9 time 2518 nodes 2224239 nps 883335 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4
e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8
info multipv 1 depth 16 seldepth 22 score cp 36 time 3049 nodes 2709124 nps 888528 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1d2 f8b4 c2c3 b4c5 f1c4
info multipv 1 depth 17 seldepth 23 score cp 40 time 3926 nodes 3518690 nps 896253 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5 d8e8 g5f6 g7f6
info multipv 1 depth 18 seldepth 24 score cp 39 time 5027 nodes 4526514 nps 900440 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 d8f6 d4f3 c6e5 b1c3 e5f3 d1f3 f6f3 g2f3 g8e7 c1f4 d7d6 a1d1
info multipv 1 depth 19 seldepth 24 score cp 39 time 6368 nodes 5740936 nps 901528 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 d8f6
info multipv 1 depth 20 seldepth 26 score cp 21 time 9672 nodes 8706343 nps 900159 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4
 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 b4c5 d4a4 e8g8 e1g1
info multipv 1 depth 21 seldepth 26 score cp 27 time 14330 nodes 12046394 nps 840641 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 b4c5 d4a4 e8g8 e1g1 a8b8 f1d1
info multipv 1 depth 22 seldepth 26 score cp 27 time 18861 nodes 15450307 nps 819166 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4
info multipv 1 depth 23 seldepth 27 score cp 27 time 24729 nodes 20294681 nps 820683 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 c6c5 d4e3 c8b7 c1d2 e8g8 e1g1 b4c3
info multipv 1 depth 24 seldepth 32 score cp 44 time 38337 nodes 32584763 nps 849955 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5
f3 f6e4 b1c3 e4c3 d2c3 f8e7 f1c4 e8g8 e1g1 b8c6 f1e1 c8f5 c1f4 d8d7 d1e2 a8e8 a1d1 e7g5
info multipv 1 depth 24 seldepth 32 score cp 44 time 45001 nodes 38805538 nps 862326 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5
f3 f6e4 b1c3 e4c3 d2c3 f8e7 f1c4 e8g8 e1g1 b8c6 f1e1 c8f5 c1f4 d8d7 d1e2 a8e8 a1d1 e7g5
bestmove e2e4

Score of Altair1.2.0 vs Altair1.1.9: 168 - 153 - 179 [0.515]
...      Altair1.2.0 playing White: 82 - 70 - 98  [0.524] 250
...      Altair1.2.0 playing Black: 86 - 83 - 81  [0.506] 250
...      White vs Black: 165 - 156 - 179  [0.509] 500
Elo difference: 10.4 +/- 24.4, LOS: 79.9 %, DrawRatio: 35.8 %
500 of 500 games finished.

Score of Altair1.2.0 vs bienchen.1.0: 522 - 281 - 197 [0.621]
...      Altair1.2.0 playing White: 250 - 150 - 100  [0.600] 500
...      Altair1.2.0 playing Black: 272 - 131 - 97  [0.641] 500
...      White vs Black: 381 - 422 - 197  [0.479] 1000
Elo difference: 85.4 +/- 19.7, LOS: 100.0 %, DrawRatio: 19.7 %
1000 of 1000 games finished.

Score of Altair1.2.0 vs Cosette-Win64: 162 - 240 - 98 [0.422]
...      Altair1.2.0 playing White: 88 - 117 - 45  [0.442] 250
...      Altair1.2.0 playing Black: 74 - 123 - 53  [0.402] 250
...      White vs Black: 211 - 191 - 98  [0.520] 500
Elo difference: -54.6 +/- 27.6, LOS: 0.0 %, DrawRatio: 19.6 %
500 of 500 games finished.

Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.2.0                    -0      11    3000    1189    1190     621   1499.5   50.0%   20.7%   50.1%   49.9% 
   1 tantabus-windows...            23      19    1000     434     369     197    532.5   53.3%   19.7%   53.8%   52.7% 
   2 kimbo-0.3.0                    -6      19    1000     392     408     200    492.0   49.2%   20.0%   51.2%   47.2% 
   3 sofcheck_amd64-popcnt_windows -17      19    1000     364     412     224    476.0   47.6%   22.4%   45.4%   49.8% 

3000 of 3000 games finished.

Equivalent to -23 against tantabus-windows-2019-x86-64-v3
Equivalent to +6  against kimbo-0.3.0
Equivalent to +17 against sofcheck_amd64-popcnt_windows
```


### 1.2.1
Not doing RFP in pv_nodes

```
info multipv 1 depth 1 seldepth 1 score cp 64 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 252 nps 84000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 5 score cp 8 time 5 nodes 910 nps 182000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 53 time 7 nodes 1844 nps 263428 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 12 nodes 4431 nps 369250 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6
info multipv 1 depth 7 seldepth 9 score cp 33 time 21 nodes 10872 nps 517714 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 17 time 34 nodes 19983 nps 587735 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 23 time 63 nodes 43186 nps 685492 pv b1c3 b8c6 d2d4 d7d5 d1d3 g8f6 g1f3 c6b4
 d3b5 b4c6
info multipv 1 depth 10 seldepth 14 score cp 20 time 134 nodes 101937 nps 760723 pv d2d4 g8f6 g1f3 e7e6 b1c3 d7d5 c1g5 f
8e7 f3e5 e8g8
info multipv 1 depth 11 seldepth 14 score cp 21 time 171 nodes 136492 nps 798198 pv d2d4 g8f6 g1f3 e7e6 b1c3 d7d5 d1d3 b
8c6 e2e4 f8b4 e4e5
info multipv 1 depth 12 seldepth 17 score cp 32 time 405 nodes 345662 nps 853486 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e
5d4 f3d4 f8b4 d4c6 d7c6
info multipv 1 depth 13 seldepth 17 score cp 29 time 521 nodes 434460 nps 833896 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4 f
8b4 e1g1 e8g8 d2d3 d7d6 c1g5
info multipv 1 depth 14 seldepth 19 score cp 45 time 901 nodes 783914 nps 870048 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e
5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 20 score cp 34 time 1271 nodes 1126195 nps 886070 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4
 f8b4 a2a3 b4c5 e1g1 e8g8 d2d3 d7d6
info multipv 1 depth 16 seldepth 21 score cp 20 time 3126 nodes 2652322 nps 848471 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 e2e3
 f8b4 f1d3 e8g8 e1g1 b8c6 a2a3 b4d6
info multipv 1 depth 17 seldepth 22 score cp 40 time 6763 nodes 5498651 nps 813049 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5 d8e8 g5f6 g7f6
info multipv 1 depth 18 seldepth 22 score cp 40 time 7676 nodes 6268698 nps 816662 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3
info multipv 1 depth 19 seldepth 25 score cp 40 time 8875 nodes 7343972 nps 827489 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6
info multipv 1 depth 20 seldepth 26 score cp 40 time 11213 nodes 9181958 nps 818867 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d
4 g8f6 d4c6 d7c6 d1d8 e8d8 b1d2 f8c5 f1c4 h8e8 e1g1 f6e4 c4f7 e8e5
info multipv 1 depth 21 seldepth 27 score cp 22 time 17002 nodes 13964492 nps 821344 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 b4c5 d4a4 e8g8 e1g1 a8b8 f1d1
info multipv 1 depth 22 seldepth 27 score cp 22 time 21043 nodes 17654365 nps 838966 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4
info multipv 1 depth 23 seldepth 27 score cp 22 time 26991 nodes 22984571 nps 851564 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6
info multipv 1 depth 24 seldepth 30 score cp 37 time 38598 nodes 33324063 nps 863362 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 f8b4 d4d5 c6e7 d1d3 e7g6 a2a3 b4c3 b2c3 e8g8 f1e2
info multipv 1 depth 24 seldepth 34 score cp 37 time 45000 nodes 39032911 nps 867398 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 f8b4 d4d5 c6e7 d1d3 e7g6 a2a3 b4c3 b2c3 e8g8 f1e2
bestmove e2e4

Score of Altair1.2.1 vs Altair1.2.0: 327 - 304 - 369 [0.511]
...      Altair1.2.1 playing White: 211 - 99 - 190  [0.612] 500
...      Altair1.2.1 playing Black: 116 - 205 - 179  [0.411] 500
...      White vs Black: 416 - 215 - 369  [0.601] 1000
Elo difference: 8.0 +/- 17.1, LOS: 82.0 %, DrawRatio: 36.9 %
1000 of 1000 games finished.
```


### 1.2.2
Razoring after RFP

```
info multipv 1 depth 1 seldepth 1 score cp 64 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 252 nps 84000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 5 score cp 8 time 5 nodes 910 nps 182000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 53 time 7 nodes 1844 nps 263428 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 12 nodes 4431 nps 369250 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6
info multipv 1 depth 7 seldepth 9 score cp 33 time 21 nodes 10872 nps 517714 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 17 time 34 nodes 19983 nps 587735 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 23 time 63 nodes 43186 nps 685492 pv b1c3 b8c6 d2d4 d7d5 d1d3 g8f6 g1f3 c6b4
 d3b5 b4c6
info multipv 1 depth 10 seldepth 14 score cp 20 time 134 nodes 101937 nps 760723 pv d2d4 g8f6 g1f3 e7e6 b1c3 d7d5 c1g5 f
8e7 f3e5 e8g8
info multipv 1 depth 11 seldepth 14 score cp 21 time 171 nodes 136492 nps 798198 pv d2d4 g8f6 g1f3 e7e6 b1c3 d7d5 d1d3 b
8c6 e2e4 f8b4 e4e5
info multipv 1 depth 12 seldepth 17 score cp 32 time 405 nodes 345662 nps 853486 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e
5d4 f3d4 f8b4 d4c6 d7c6
info multipv 1 depth 13 seldepth 17 score cp 29 time 521 nodes 434460 nps 833896 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4 f
8b4 e1g1 e8g8 d2d3 d7d6 c1g5
info multipv 1 depth 14 seldepth 19 score cp 45 time 901 nodes 783914 nps 870048 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e
5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 20 score cp 34 time 1271 nodes 1126195 nps 886070 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4
 f8b4 a2a3 b4c5 e1g1 e8g8 d2d3 d7d6
info multipv 1 depth 16 seldepth 21 score cp 20 time 3126 nodes 2652322 nps 848471 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 e2e3
 f8b4 f1d3 e8g8 e1g1 b8c6 a2a3 b4d6
info multipv 1 depth 17 seldepth 22 score cp 40 time 6763 nodes 5498651 nps 813049 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5 d8e8 g5f6 g7f6
info multipv 1 depth 18 seldepth 22 score cp 40 time 7676 nodes 6268698 nps 816662 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3
info multipv 1 depth 19 seldepth 25 score cp 40 time 8875 nodes 7343972 nps 827489 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6
info multipv 1 depth 20 seldepth 26 score cp 40 time 11213 nodes 9181958 nps 818867 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d
4 g8f6 d4c6 d7c6 d1d8 e8d8 b1d2 f8c5 f1c4 h8e8 e1g1 f6e4 c4f7 e8e5
info multipv 1 depth 21 seldepth 27 score cp 22 time 17002 nodes 13964492 nps 821344 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 b4c5 d4a4 e8g8 e1g1 a8b8 f1d1
info multipv 1 depth 22 seldepth 27 score cp 22 time 21043 nodes 17654365 nps 838966 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4
info multipv 1 depth 23 seldepth 27 score cp 22 time 26991 nodes 22984571 nps 851564 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6
info multipv 1 depth 24 seldepth 30 score cp 37 time 38598 nodes 33324063 nps 863362 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 f8b4 d4d5 c6e7 d1d3 e7g6 a2a3 b4c3 b2c3 e8g8 f1e2
info multipv 1 depth 24 seldepth 34 score cp 37 time 45000 nodes 39032911 nps 867398 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 f8b4 d4d5 c6e7 d1d3 e7g6 a2a3 b4c3 b2c3 e8g8 f1e2
bestmove e2e4

Score of Altair1.2.2 vs Altair1.2.1: 286 - 243 - 271 [0.527]
...      Altair1.2.2 playing White: 194 - 77 - 129  [0.646] 400
...      Altair1.2.2 playing Black: 92 - 166 - 142  [0.407] 400
...      White vs Black: 360 - 169 - 271  [0.619] 800
Elo difference: 18.7 +/- 19.6, LOS: 96.9 %, DrawRatio: 33.9 %
800 of 800 games finished.
```


### 1.2.3
No razoring in pv nodes

```
info multipv 1 depth 1 seldepth 1 score cp 64 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 252 nps 84000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 5 score cp 8 time 5 nodes 910 nps 182000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 53 time 7 nodes 1844 nps 263428 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 8 score cp 7 time 11 nodes 4431 nps 402818 pv e2e4 b8c6 g1f3 e7e5 b1c3 g8f6
info multipv 1 depth 7 seldepth 9 score cp 33 time 19 nodes 10872 nps 572210 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 11 score cp 17 time 30 nodes 19983 nps 666100 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4

info multipv 1 depth 9 seldepth 12 score cp 23 time 56 nodes 43186 nps 771178 pv b1c3 b8c6 d2d4 d7d5 d1d3 g8f6 g1f3 c6b4
 d3b5 b4c6
info multipv 1 depth 10 seldepth 14 score cp 20 time 119 nodes 101937 nps 856613 pv d2d4 g8f6 g1f3 e7e6 b1c3 d7d5 c1g5 f
8e7 f3e5 e8g8
info multipv 1 depth 11 seldepth 14 score cp 21 time 158 nodes 136492 nps 863873 pv d2d4 g8f6 g1f3 e7e6 b1c3 d7d5 d1d3 b
8c6 e2e4 f8b4 e4e5
info multipv 1 depth 12 seldepth 17 score cp 32 time 387 nodes 345688 nps 893250 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e
5d4 f3d4 f8b4 d4c6 d7c6
info multipv 1 depth 13 seldepth 17 score cp 29 time 479 nodes 434485 nps 907066 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4 f
8b4 e1g1 e8g8 d2d3 d7d6 c1g5
info multipv 1 depth 14 seldepth 19 score cp 45 time 895 nodes 783928 nps 875897 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e
5d4 f3d4 f8b4 d4c6 b4c3 b2c3 d7c6 d1d3
info multipv 1 depth 15 seldepth 20 score cp 34 time 1266 nodes 1126209 nps 889580 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4
 f8b4 a2a3 b4c5 e1g1 e8g8 d2d3 d7d6
info multipv 1 depth 16 seldepth 21 score cp 20 time 2890 nodes 2652383 nps 917779 pv b1c3 d7d5 d2d4 g8f6 g1f3 e7e6 e2e3
 f8b4 f1d3 e8g8 e1g1 b8c6 a2a3 b4d6
info multipv 1 depth 17 seldepth 22 score cp 40 time 7603 nodes 5498820 nps 723243 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1g5 d8e8 g5f6 g7f6
info multipv 1 depth 18 seldepth 22 score cp 40 time 8642 nodes 6268867 nps 725395 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3
info multipv 1 depth 19 seldepth 25 score cp 40 time 10384 nodes 7487223 nps 721034 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d
4 g8f6
info multipv 1 depth 20 seldepth 26 score cp 37 time 12890 nodes 9527873 nps 739167 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d
4 g8f6 d4c6 b7c6 f1d3 d7d5 e4d5 c6d5 e1g1 f8e7 b1c3 e8g8 c1f4 c8g4
info multipv 1 depth 21 seldepth 26 score cp 37 time 16433 nodes 12422515 nps 755949 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4
info multipv 1 depth 22 seldepth 29 score cp 42 time 40256 nodes 33665507 nps 836285 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 g8f6 e4f6 d8f6 g1f3 h7h6 f1c4 b8c6 e1g1 f8d6 c2c3
info multipv 1 depth 22 seldepth 31 score cp 42 time 45000 nodes 37746707 nps 838815 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3
e4 g8f6 e4f6 d8f6 g1f3 h7h6 f1c4 b8c6 e1g1 f8d6 c2c3
bestmove e2e4

Score of Altair1.2.3 vs Altair1.2.2: 280 - 246 - 274 [0.521]
...      Altair1.2.3 playing White: 175 - 96 - 129  [0.599] 400
...      Altair1.2.3 playing Black: 105 - 150 - 145  [0.444] 400
...      White vs Black: 325 - 201 - 274  [0.578] 800
Elo difference: 14.8 +/- 19.5, LOS: 93.1 %, DrawRatio: 34.3 %
800 of 800 games finished.

Score of Altair1.2.3 vs sofcheck_amd64-popcnt_windows: 115 - 65 - 60 [0.604]
...      Altair1.2.3 playing White: 59 - 27 - 34  [0.633] 120
...      Altair1.2.3 playing Black: 56 - 38 - 26  [0.575] 120
...      White vs Black: 97 - 83 - 60  [0.529] 240
Elo difference: 73.5 +/- 38.8, LOS: 100.0 %, DrawRatio: 25.0 %
240 of 240 games finished.

Score of Altair1.2.3 vs Cosette-Win64: 181 - 229 - 90 [0.452]
...      Altair1.2.3 playing White: 117 - 87 - 46  [0.560] 250
...      Altair1.2.3 playing Black: 64 - 142 - 44  [0.344] 250
...      White vs Black: 259 - 151 - 90  [0.608] 500
Elo difference: -33.5 +/- 27.7, LOS: 0.9 %, DrawRatio: 18.0 %
500 of 500 games finished.

Score of Altair1.2.3 vs Altair1.0.0: 282 - 63 - 155 [0.719]
...      Altair1.2.3 playing White: 160 - 21 - 69  [0.778] 250
...      Altair1.2.3 playing Black: 122 - 42 - 86  [0.660] 250
...      White vs Black: 202 - 143 - 155  [0.559] 500
Elo difference: 163.2 +/- 26.6, LOS: 100.0 %, DrawRatio: 31.0 %
500 of 500 games finished.
```

### 1.2.4
Tuning TT depth preferred placement. if (depth + n >= tt_entry.depth)
```
Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.2.3                     1      11    2327     758     751     818   1167.0   50.2%   35.2%   60.3%   40.0% 
   1 Altair1.2.4-6                   5      22     580     187     179     214    294.0   50.7%   36.9%   61.9%   39.5% 
   2 Altair1.2.4-2                   4      23     583     199     192     192    295.0   50.6%   32.9%   62.2%   39.0% 
   3 Altair1.2.4-5                  -7      23     582     190     201     191    285.5   49.1%   32.8%   56.4%   41.8% 
   4 Altair1.2.4-4                  -7      22     582     175     186     221    285.5   49.1%   38.0%   59.5%   38.7% 

2331 of 4000 games finished.

Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.2.3                     7      18    1000     341     322     337    509.5   50.9%   33.7%   62.8%   39.1% 
   1 Altair1.2.4-2                   4      25     500     170     164     166    253.0   50.6%   33.2%   62.2%   39.0% 
   2 Altair1.2.4-6                 -17      25     500     152     177     171    237.5   47.5%   34.2%   59.6%   35.4% 

1000 of 1000 games finished.

Altair1.2.4: W 369 L 356 D 358 | Points: 548 / 1083 | Win Percent: 50.6 | Elo: +4 Error: +-17
```


### 1.2.5
Tuning LMR divisor value. 1.9 -> 1.8


```
Result:
--------------------------------------------------------------------------
  #  name          games    wins   draws  losses   score    elo    +    -
  1. Altair125-18   1500     495     559     446   774.5      5    8    8
  2. Altair124      1500     446     559     495   725.5     -5    8    8

Results based on https://www.3dkingdoms.com/chess/elo.htm:
  Elo difference: +11
  Error Margin: +-14

Tech:
--------------------------------------------------------------------------

Tech (average nodes, depths, time/m per move, others per game), counted for computing moves only,
ignored moves with zero nodes:

  #  name            nodes/m         NPS  depth/m   time/m    moves     time
  1. Altair125-18        90K     1579467     12.8      0.1     68.5      3.9
  2. Altair124           90K     1579771     12.6      0.1     68.5      3.9
```

### 1.2.6
Tuning LMR +n value. 1.2 -> 1.1

```
W 482 L 464 D 554

Results based on https://www.3dkingdoms.com/chess/elo.htm:
  Elo difference: +4
  Error Margin: +-11

3 min + 2 sec 
Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.2.6                    52       9    4262    1962    1323     977   2450.5   57.5%   22.9%   58.0%   57.0% 
   1 tantabus-windows-2019-x86-64-v3      47      20     852     378     263     211    483.5   56.7%   24.8%   56.3%   57.2% 
   2 Cosette-Win64                 -38      21     853     286     380     187    379.5   44.5%   21.9%   45.3%   43.7% 
   3 kimbo-0.3.0                   -67      21     852     249     412     191    344.5   40.4%   22.4%   40.0%   40.8% 
   4 sofcheck_amd64-popcnt_windows    -103      21     852     193     438     221    303.5   35.6%   25.9%   39.2%   32.0% 
   5 bienchen.1.0                 -106      22     853     217     469     167    300.5   35.2%   19.6%   34.0%   36.5% 

4266 of 20000 games finished.
```


### 1.2.7
Specific set of values for MVV-LVA, and giving a value for a king

```
info multipv 1 depth 1 seldepth 1 score cp 64 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 2 nodes 252 nps 126000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 8 time 3 nodes 627 nps 209000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 53 time 5 nodes 1446 nps 289200 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 9 nodes 3922 nps 435777 pv b1c3 b8c6 e2e4 g8f6 g1f3 e7e5
info multipv 1 depth 7 seldepth 8 score cp 33 time 12 nodes 6734 nps 561166 pv b1c3 b8c6 g1f3 g8f6 d2d4 d7d5 c1f4
info multipv 1 depth 8 seldepth 10 score cp 17 time 21 nodes 13310 nps 633809 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4
info multipv 1 depth 9 seldepth 11 score cp 17 time 31 nodes 21653 nps 698483 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4 c3e4
info multipv 1 depth 10 seldepth 13 score cp 17 time 70 nodes 57144 nps 816342 pv b1c3 b8c6 g1f3 g8f6 e2e4 d7d5 e4e5 f6e4 c3e4 d5e4
info multipv 1 depth 11 seldepth 14 score cp 51 time 143 nodes 124134 nps 868069 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1f3 d5e4 c1e3 c8f5 f1d3 e4d5
info multipv 1 depth 12 seldepth 15 score cp 34 time 263 nodes 235829 nps 896688 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 c2c4 d5f6 d2d4 e7e6 b1c3 b8c6
info multipv 1 depth 13 seldepth 17 score cp 58 time 488 nodes 443371 nps 908547 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 c2c4 d5f6 d2d4 e7e6 b1c3 b8c6 c1f4
info multipv 1 depth 14 seldepth 17 score cp 46 time 574 nodes 526974 nps 918073 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 c2c4 d5f6 d2d4 e7e6 b1c3 b8c6 c1f4 f8b4
info multipv 1 depth 15 seldepth 20 score cp 50 time 960 nodes 887122 nps 924085 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 c2c4 d5f6 d2d4 e7e6 b1c3 b8c6 c1f4 f8d6 f3e5
info multipv 1 depth 16 seldepth 20 score cp 38 time 1343 nodes 1254954 nps 934440 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 e7e6 f1c4 b8c6 e1g1 f8e7 b1d2 d5f6 c2c3 e8g8
info multipv 1 depth 17 seldepth 24 score cp 41 time 2082 nodes 1955567 nps 939273 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 e7e6 c2c4 d5f6 b1c3 b8c6 f1e2 f8b4 e1g1
info multipv 1 depth 18 seldepth 24 score cp 37 time 2805 nodes 2654590 nps 946377 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 e7e6 c2c4 d5f6 b1c3 b8c6 f1e2 f8d6 e1g1 e8g8 c1g5 e6e5
info multipv 1 depth 19 seldepth 25 score cp 42 time 4607 nodes 4314493 nps 936508 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 e7e6 c2c4 d5f6 b1c3 b8c6 f1e2 f8d6 e1g1 e8g8 c1e3 e6e5 d1d3
info multipv 1 depth 20 seldepth 25 score cp 42 time 5784 nodes 5435728 nps 939786 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 e7e6 c2c4 d5f6
info multipv 1 depth 21 seldepth 25 score cp 42 time 7960 nodes 7519657 nps 944680 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 e7e6 c2c4 d5f6 b1c3 b8c6 f1e2 f8d6
info multipv 1 depth 22 seldepth 25 score cp 42 time 10010 nodes 9461927 nps 945247 pv e2e4 d7d5 e4d5
info multipv 1 depth 23 seldepth 27 score cp 42 time 13714 nodes 12937848 nps 943404 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 e7e6 c2c4 d5f6 b1c3
info multipv 1 depth 23 seldepth 32 score cp 42 time 44999 nodes 40591381 nps 902050 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 e7e6 c2c4 d5f6 b1c3
bestmove e2e4

Score of Altair1.2.7 vs Altair1.2.6: 271 - 260 - 269 [0.507]
...      Altair1.2.7 playing White: 170 - 104 - 126  [0.583] 400
...      Altair1.2.7 playing Black: 101 - 156 - 143  [0.431] 400
...      White vs Black: 326 - 205 - 269  [0.576] 800
Elo difference: 4.8 +/- 19.6, LOS: 68.3 %, DrawRatio: 33.6 %
800 of 800 games finished.
```


### 1.2.8
Eval tweaks

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 256 nps 85333 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 4 nodes 666 nps 166500 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 49 time 6 nodes 1162 nps 193666 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 8 nodes 2467 nps 308375 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 29 time 13 nodes 5907 nps 454384 pv b1c3 b8c6 d2d4 d7d5 e2e3 g8f6 g1f3
info multipv 1 depth 8 seldepth 10 score cp 25 time 31 nodes 21775 nps 702419 pv b1c3 b8c6 d2d4 d7d5 g1f3 e7e6 e2e4 g8f6

info multipv 1 depth 9 seldepth 11 score cp 22 time 45 nodes 33106 nps 735688 pv b1c3 b8c6 d2d4 d7d5 g1f3 c8f5 f3h4 f5g4
 h4f3
info multipv 1 depth 10 seldepth 12 score cp 21 time 63 nodes 46507 nps 738206 pv b1c3 b8c6 d2d4 d7d5 g1f3 c8f5 e2e3 g8f
6 f1d3 d8d7
info multipv 1 depth 11 seldepth 14 score cp 27 time 115 nodes 92878 nps 807634 pv g1f3 b8c6 d2d4 d7d5 e2e3 g8f6 b1c3 c8
g4 h2h3 g4f5 f1b5
info multipv 1 depth 12 seldepth 14 score cp 40 time 176 nodes 146711 nps 833585 pv g1f3 b8c6 d2d4 d7d5 e2e3 g8f6 b1c3 d
8d6 f1d3 c6b4 e1g1 b4d3
info multipv 1 depth 13 seldepth 17 score cp 12 time 761 nodes 616196 nps 809718 pv b1c3 g8f6 d2d4 d7d5 e2e3 b8d7 g1f3 e
7e6 f1d3 f8b4 e1g1 e8g8 c1d2
info multipv 1 depth 14 seldepth 20 score cp 17 time 1309 nodes 1115758 nps 852374 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 f1b5
 f8b4 e1g1 e8g8 f1e1 b4c5 b5c6 d7c6
info multipv 1 depth 15 seldepth 20 score cp 33 time 1616 nodes 1397776 nps 864960 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6
info multipv 1 depth 16 seldepth 22 score cp 42 time 2073 nodes 1796061 nps 866406 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8 d2d3 d7d6 c3d5 h7h6 c1e3 c8g4
info multipv 1 depth 17 seldepth 23 score cp 42 time 2565 nodes 2225598 nps 867679 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8
info multipv 1 depth 18 seldepth 23 score cp 36 time 3387 nodes 2990402 nps 882905 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8 d2d3 d7d6 c3d5 h7h6 c1e3 c5e3 d5e3 c8e6
info multipv 1 depth 19 seldepth 24 score cp 36 time 4725 nodes 4224266 nps 894024 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8 d2d3 d7d6 c3d5 c6a5 c1g5 a5c4 d3c4 c8g4
info multipv 1 depth 20 seldepth 26 score cp 26 time 6958 nodes 6261377 nps 899881 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8 d2d3 d7d6 c3d5 f6d5 c4d5 c6d4 f3d4 c5d4 d1f3 d8h4
info multipv 1 depth 21 seldepth 29 score cp 45 time 12938 nodes 11680952 nps 902840 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3
d4 g8f6 d4c6 b7c6 f1d3 f8d6 e1g1 e8g8 b1d2 d8e7 d2c4 f6e4
info multipv 1 depth 22 seldepth 29 score cp 45 time 15918 nodes 14400969 nps 904697 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4
info multipv 1 depth 23 seldepth 29 score cp 21 time 25575 nodes 23199470 nps 907115 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6
info multipv 1 depth 24 seldepth 29 score cp 21 time 33871 nodes 30742058 nps 907621 pv e2e4 e7e5 g1f3
info multipv 1 depth 24 seldepth 30 score cp 21 time 45000 nodes 40863763 nps 908083 pv e2e4 e7e5 g1f3
bestmove e2e4

Score of Altair1.2.8 vs Altair1.2.7: 218 - 188 - 194 [0.525]
...      Altair1.2.8 playing White: 137 - 68 - 95  [0.615] 300
...      Altair1.2.8 playing Black: 81 - 120 - 99  [0.435] 300
...      White vs Black: 257 - 149 - 194  [0.590] 600
Elo difference: 17.4 +/- 22.9, LOS: 93.2 %, DrawRatio: 32.3 %
600 of 600 games finished.

Score of Altair1.2.8 vs tantabus-windows-2019-x86-64-v3: 91 - 107 - 42 [0.467]
...      Altair1.2.8 playing White: 48 - 52 - 20  [0.483] 120
...      Altair1.2.8 playing Black: 43 - 55 - 22  [0.450] 120
...      White vs Black: 103 - 95 - 42  [0.517] 240
Elo difference: -23.2 +/- 40.1, LOS: 12.8 %, DrawRatio: 17.5 %
240 of 240 games finished.

noob 4 moves book
Score of Altair1.2.8 vs Altair1.0.0: 258 - 96 - 146 [0.662]
...      Altair1.2.8 playing White: 133 - 53 - 64  [0.660] 250
...      Altair1.2.8 playing Black: 125 - 43 - 82  [0.664] 250
...      White vs Black: 176 - 178 - 146  [0.498] 500
Elo difference: 116.8 +/- 26.5, LOS: 100.0 %, DrawRatio: 29.2 %

1 min
Score of Altair1.2.8 vs kimbo-0.3.0: 71 - 53 - 29 [0.559]
...      Altair1.2.8 playing White: 31 - 29 - 16  [0.513] 76
...      Altair1.2.8 playing Black: 40 - 24 - 13  [0.604] 77
...      White vs Black: 55 - 69 - 29  [0.454] 153
Elo difference: 41.1 +/- 50.1, LOS: 94.7 %, DrawRatio: 19.0 %
153 of 240 games finished.
```


### 1.2.9
Some safety checks to prevent index out of bounds.
Also, not immediately playing mates.

```
Score of Altair1.2.9 vs Altair1.2.8: 321 - 326 - 353 [0.497]
...      Altair1.2.9 playing White: 204 - 124 - 172  [0.580] 500
...      Altair1.2.9 playing Black: 117 - 202 - 181  [0.415] 500
...      White vs Black: 406 - 241 - 353  [0.583] 1000
Elo difference: -1.7 +/- 17.3, LOS: 42.2 %, DrawRatio: 35.3 %
1000 of 1000 games finished.

Score of Altair1.2.9 vs admete_1.5.0_windows_x86-64: 243 - 209 - 48 [0.534]
...      Altair1.2.9 playing White: 145 - 82 - 23  [0.626] 250
...      Altair1.2.9 playing Black: 98 - 127 - 25  [0.442] 250
...      White vs Black: 272 - 180 - 48  [0.592] 500
Elo difference: 23.7 +/- 29.0, LOS: 94.5 %, DrawRatio: 9.6 %
500 of 500 games finished.
```


### 1.3.0
Less history bonus in a null move search root

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 2 nodes 256 nps 128000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 3 nodes 666 nps 222000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 49 time 4 nodes 1162 nps 290500 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 7 nodes 2467 nps 352428 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 29 time 11 nodes 5907 nps 537000 pv b1c3 b8c6 d2d4 d7d5 e2e3 g8f6 g1f3
info multipv 1 depth 8 seldepth 9 score cp 25 time 26 nodes 16821 nps 646961 pv b1c3 b8c6 d2d4 d7d5 g1f3 e7e6 e2e4 g8f6
info multipv 1 depth 9 seldepth 10 score cp 24 time 45 nodes 31761 nps 705800 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 d1d3 c6b4 d3b5 b4c6
info multipv 1 depth 10 seldepth 12 score cp 20 time 65 nodes 49821 nps 766476 pv b1c3 b8c6 e2e4 g8f6 g1f3 d7d5 e4e5 f6e4 c3e4 d5e4
info multipv 1 depth 11 seldepth 14 score cp 39 time 161 nodes 134893 nps 837844 pv g1f3 g8f6 d2d4 d7d5 e2e3 b8c6 b1c3
info multipv 1 depth 12 seldepth 15 score cp 32 time 294 nodes 257254 nps 875013 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6
info multipv 1 depth 13 seldepth 17 score cp 26 time 594 nodes 527237 nps 887604 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 e2e3 f6e4 c3e4 d5e4 f3d2 c8f5 f1c4
info multipv 1 depth 14 seldepth 18 score cp 36 time 950 nodes 853346 nps 898258 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4
info multipv 1 depth 15 seldepth 20 score cp 18 time 1419 nodes 1276514 nps 899587 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4 f8c5 e1g1 e8g8 d2d3 d7d6 c1e3 c8g4 c3d5
info multipv 1 depth 16 seldepth 21 score cp 41 time 2354 nodes 2134699 nps 906838 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 c8f5 f1b5 b8d7 e1g1 e7e6 b1d2 c7c6 b5c4
info multipv 1 depth 17 seldepth 21 score cp 41 time 3019 nodes 2740978 nps 907909 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 c8f5 f1b5 b8d7 e1g1 a7a6 b5c4 d7b6 c4d3 f5d3 d1d3 e7e6
info multipv 1 depth 18 seldepth 23 score cp 41 time 3863 nodes 3521527 nps 911604 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 c8f5 f1b5 b8d7 e1g1 a7a6
info multipv 1 depth 19 seldepth 23 score cp 41 time 4717 nodes 4320760 nps 915997 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 d2d4 c8f5 f1b5
info multipv 1 depth 20 seldepth 28 score cp 25 time 15160 nodes 13669536 nps 901684 pv e2e4 e7e6 d2d4 d7d5 b1c3 f8b4 e4e5 c7c5 g1f3 b8c6 a2a3 b4a5 f1b5 c8d7 c1g5 g8e7 e1g1 a5c3 b5c6 d7c6
info multipv 1 depth 21 seldepth 29 score cp 27 time 18266 nodes 16197921 nps 886779 pv e2e4 e7e6 g1f3 d7d5 e4e5 d5d4 f1b5 c7c6 b5e2 b8d7 e1g1 g8h6 c2c3 h6f5 c3d4 d8b6 b1c3 f5d4 f3d4 b6d4
info multipv 1 depth 22 seldepth 29 score cp 31 time 26734 nodes 23715620 nps 887095 pv e2e4 e7e6 b1c3 d7d5 d2d4 f8b4 e4e5 g8e7 g1f3 c7c5 a2a3 c5d4 a3b4 d4c3 b2c3 b8d7 c3c4 e8g8 c1g5 f7f6 e5f6 d7f6
info multipv 1 depth 23 seldepth 29 score cp 31 time 30391 nodes 27029798 nps 889401 pv e2e4 e7e6 b1c3
info multipv 1 depth 23 seldepth 29 score cp 31 time 45001 nodes 40142886 nps 892044 pv e2e4 e7e6 b1c3
bestmove e2e4

Score of Altair1.3.0 vs Altair1.2.9: 354 - 320 - 326 [0.517]
...      Altair1.3.0 playing White: 225 - 118 - 157  [0.607] 500
...      Altair1.3.0 playing Black: 129 - 202 - 169  [0.427] 500
...      White vs Black: 427 - 247 - 326  [0.590] 1000
Elo difference: 11.8 +/- 17.7, LOS: 90.5 %, DrawRatio: 32.6 %
1000 of 1000 games finished.
```


### 1.3.1
More aggressive LMR in a null move search root

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 2 nodes 110 nps 55000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 256 nps 85333 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 5 nodes 666 nps 133200 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 49 time 7 nodes 1162 nps 166000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 10 nodes 2467 nps 246700 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 29 time 15 nodes 5907 nps 393800 pv b1c3 b8c6 d2d4 d7d5 e2e3 g8f6 g1f3
info multipv 1 depth 8 seldepth 9 score cp 25 time 30 nodes 16821 nps 560700 pv b1c3 b8c6 d2d4 d7d5 g1f3 e7e6 e2e4 g8f6

info multipv 1 depth 9 seldepth 10 score cp 24 time 48 nodes 31761 nps 661687 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 d1d3 c6b4
 d3b5 b4c6
info multipv 1 depth 10 seldepth 12 score cp 20 time 68 nodes 49815 nps 732573 pv b1c3 b8c6 e2e4 g8f6 g1f3 d7d5 e4e5 f6e
4 c3e4 d5e4
info multipv 1 depth 11 seldepth 14 score cp 39 time 166 nodes 136323 nps 821222 pv g1f3 g8f6 d2d4 d7d5 e2e3 b8c6 b1c3
info multipv 1 depth 12 seldepth 16 score cp 8 time 381 nodes 306569 nps 804643 pv g1f3 g8f6 d2d4 e7e6 e2e3 d7d5 b1c3 f8
b4 f1b5 c7c6 b5d3 f6e4 e1g1
info multipv 1 depth 13 seldepth 17 score cp 40 time 577 nodes 480959 nps 833551 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 f1c4 b
8c6 e1g1 c6a5 c4d5 d8d5 b1c3
info multipv 1 depth 14 seldepth 19 score cp 37 time 755 nodes 636569 nps 843137 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 f1c4 b
8c6 e1g1 c8e6 f3g5 d8d6 g5e6 d6e6
info multipv 1 depth 15 seldepth 20 score cp 25 time 1477 nodes 1278126 nps 865352 pv e2e4 e7e5 b1c3 b8c6 g1f3
info multipv 1 depth 16 seldepth 20 score cp 25 time 1852 nodes 1619608 nps 874518 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 17 seldepth 23 score cp 24 time 2862 nodes 2525874 nps 882555 pv e2e4 e7e5 d2d4 e5d4 g1f3 c7c5 c2c3
 d7d5 e4d5 g8f6 f1c4 d8e7 e1f1 b8d7 f1g1 d7e5 f3e5 e7e5
info multipv 1 depth 18 seldepth 24 score cp 10 time 4547 nodes 4037316 nps 887907 pv e2e4 e7e5 d2d4 e5d4 g1f3 f8c5 f3d4
 g8f6 d4b3 f6e4 b3c5 e4c5 b1c3 e8g8 f1c4 b8c6 e1g1 f8e8
info multipv 1 depth 19 seldepth 24 score cp 17 time 6277 nodes 5600350 nps 892201 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 f3e5
 d7d6 e5f3 b8c6 b1d2 c8f5 d4d5 c6e5 f1b5 c7c6 f3e5 c6b5 d2e4 f5e4
info multipv 1 depth 20 seldepth 27 score cp 31 time 9175 nodes 8248955 nps 899068 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5f3
 f6e4 b1c3 e4c3 d2c3 b8d7 f1c4 d7b6 c4b3 f8e7 e1g1 e8g8 f1e1 c8f5
info multipv 1 depth 21 seldepth 27 score cp 31 time 12030 nodes 10807440 nps 898374 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5
f3 f6e4 b1c3 e4c3
info multipv 1 depth 22 seldepth 29 score cp 35 time 18950 nodes 16981090 nps 896099 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 f8b4 d4d5 c6e7 f1d3 b4c3 b2c3 e7g6 e1g1 e8g8 a1b1 d7d6 f1e1
info multipv 1 depth 23 seldepth 31 score cp 35 time 42456 nodes 38100957 nps 897422 pv e2e4 e7e5
info multipv 1 depth 23 seldepth 31 score cp 35 time 45001 nodes 40427546 nps 898369 pv e2e4 e7e5
bestmove e2e4

Score of Altair1.3.1 vs Altair1.3.0: 420 - 357 - 223 [0.531]
...      Altair1.3.1 playing White: 261 - 130 - 109  [0.631] 500
...      Altair1.3.1 playing Black: 159 - 227 - 114  [0.432] 500
...      White vs Black: 488 - 289 - 223  [0.600] 1000
Elo difference: 21.9 +/- 19.0, LOS: 98.8 %, DrawRatio: 22.3 %
1000 of 1000 games finished.

Score of Altair1.3.1 vs tantabus-windows-2019-x86-64-v3: 121 - 90 - 29 [0.565]
...      Altair1.3.1 playing White: 58 - 44 - 18  [0.558] 120
...      Altair1.3.1 playing Black: 63 - 46 - 11  [0.571] 120
...      White vs Black: 104 - 107 - 29  [0.494] 240
Elo difference: 45.1 +/- 41.7, LOS: 98.4 %, DrawRatio: 12.1 %
240 of 240 games finished.

Score of Altair1.3.1 vs admete_1.5.0_windows_x86-64: 129 - 92 - 19 [0.577]
...      Altair1.3.1 playing White: 60 - 51 - 9  [0.537] 120
...      Altair1.3.1 playing Black: 69 - 41 - 10  [0.617] 120
...      White vs Black: 101 - 120 - 19  [0.460] 240
Elo difference: 54.0 +/- 42.8, LOS: 99.4 %, DrawRatio: 7.9 %
240 of 240 games finished.

Score of Altair1.3.1 vs kimbo-0.3.0: 138 - 77 - 25 [0.627]
...      Altair1.3.1 playing White: 75 - 32 - 13  [0.679] 120
...      Altair1.3.1 playing Black: 63 - 45 - 12  [0.575] 120
...      White vs Black: 120 - 95 - 25  [0.552] 240
Elo difference: 90.3 +/- 43.0, LOS: 100.0 %, DrawRatio: 10.4 %
240 of 240 games finished.
```


### 1.3.2
More aggressive RFP

```
go movetime 50000
45000
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 2 nodes 256 nps 128000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 3 nodes 666 nps 222000 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 49 time 5 nodes 1162 nps 232400 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 7 nodes 2467 nps 352428 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 29 time 12 nodes 5914 nps 492833 pv b1c3 b8c6 d2d4 d7d5 e2e3 g8f6 g1f3
info multipv 1 depth 8 seldepth 10 score cp 25 time 37 nodes 26544 nps 717405 pv b1c3 b8c6 d2d4 d7d5 g1f3 e7e6 e2e4 g8f6
info multipv 1 depth 9 seldepth 11 score cp 24 time 47 nodes 34964 nps 743914 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 d1d3 c6b4 d3b5 b4c6
info multipv 1 depth 10 seldepth 12 score cp 23 time 63 nodes 48428 nps 768698 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 f3e5 d8d6 c1f4 c8f5
info multipv 1 depth 11 seldepth 14 score cp 23 time 93 nodes 75226 nps 808881 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 f3e5 d8d6 c1f4 c8f5 e2e3
info multipv 1 depth 12 seldepth 15 score cp 30 time 164 nodes 139966 nps 853451 pv b1c3 b8c6 d2d4 d7d5 g1f3 c8f5 e2e3 c6b4 e3e4 d5e4 f3h4 e7e6
info multipv 1 depth 13 seldepth 16 score cp 31 time 250 nodes 221527 nps 886108 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 f3e5 c6e5 d4e5 d5d4 e5f6 d4c3 d1d8 e8d8
info multipv 1 depth 14 seldepth 19 score cp 36 time 807 nodes 737048 nps 913318 pv e2e4 e7e5 b1c3 b8c6 f1c4 g8f6 g1f3 f8b4 e1g1 d7d6 d2d3 e8g8 c3d5
info multipv 1 depth 15 seldepth 20 score cp 35 time 1017 nodes 934176 nps 918560 pv e2e4 e7e5 b1c3 b8c6 f1c4 g8f6 g1f3 f8b4 a2a3 b4c5 e1g1 e8g8 d2d3 d7d6 c1g5
info multipv 1 depth 16 seldepth 23 score cp 41 time 1528 nodes 1382683 nps 904897 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 e7e6 f1c4 f8e7 e1g1 e8g8 b1d2 b8c6 d2e4 e7b4
info multipv 1 depth 17 seldepth 23 score cp 42 time 2377 nodes 2160870 nps 909074 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 c2c4 d5f6 d2d4 e7e6 f1e2 f8b4 b1c3 e8g8 e1g1 b8c6 c1f4 f6g4
info multipv 1 depth 18 seldepth 23 score cp 42 time 3158 nodes 2846854 nps 901473 pv e2e4 d7d5 e4d5 g8f6 g1f3 f6d5 c2c4
info multipv 1 depth 19 seldepth 26 score cp 19 time 7458 nodes 6518897 nps 874081 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1c4 f8d6 e1g1 e8g8 a2a3 d6c5 d2d3 d7d6 c1g5 h7h6 g5e3 c8g4 c3d5
info multipv 1 depth 20 seldepth 26 score cp 19 time 9093 nodes 8035780 nps 883732 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6
info multipv 1 depth 21 seldepth 27 score cp 41 time 11594 nodes 10229474 nps 882307 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 f1c4 f8d6 d2d4 e8g8 e1g1 e5d4 f3d4 c6d4 d1d4 f6g4 f2f4 d8h4 h2h3 h4f6
info multipv 1 depth 22 seldepth 27 score cp 35 time 15574 nodes 13906381 nps 892922 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 f1c4 f8d6 e1g1 e8g8 a2a3 c6d4 d2d3 c7c6 c1e3 b7b5 c4a2 d8b6 a1c1 c8b7 f3d4 e5d4
info multipv 1 depth 23 seldepth 27 score cp 35 time 18861 nodes 16979962 nps 900268 pv e2e4 e7e5 b1c3 g8f6 g1f3
info multipv 1 depth 24 seldepth 29 score cp 23 time 32215 nodes 29406274 nps 912813 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 f8c5 d4b3 c5e7 f1d3 g8f6 e1g1 e8g8 b1c3 f8e8 c1f4 d7d6 c3d5 c8e6 d5e7 d8e7 f1e1 c6e5
info multipv 1 depth 24 seldepth 31 score cp 23 time 45002 nodes 41728016 nps 927248 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 f8c5 d4b3 c5e7 f1d3 g8f6 e1g1 e8g8 b1c3 f8e8 c1f4 d7d6 c3d5 c8e6 d5e7 d8e7 f1e1 c6e5
bestmove e2e4

Score of Altair1.3.2 vs Altair1.3.1: 624 - 567 - 309 [0.519]
...      Altair1.3.2 playing White: 344 - 240 - 166  [0.569] 750
...      Altair1.3.2 playing Black: 280 - 327 - 143  [0.469] 750
...      White vs Black: 671 - 520 - 309  [0.550] 1500
Elo difference: 13.2 +/- 15.7, LOS: 95.1 %, DrawRatio: 20.6 %
1500 of 1500 games finished.
```


### 1.3.3
No LMP or quiet LMP in check

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 256 nps 85333 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 5 nodes 666 nps 133200 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 49 time 7 nodes 1162 nps 166000 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 10 nodes 2467 nps 246700 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 29 time 15 nodes 5914 nps 394266 pv b1c3 b8c6 d2d4 d7d5 e2e3 g8f6 g1f3
info multipv 1 depth 8 seldepth 10 score cp 25 time 39 nodes 26544 nps 680615 pv b1c3 b8c6 d2d4 d7d5 g1f3 e7e6 e2e4 g8f6

info multipv 1 depth 9 seldepth 11 score cp 24 time 50 nodes 34964 nps 699280 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 d1d3 c6b4
 d3b5 b4c6
info multipv 1 depth 10 seldepth 12 score cp 23 time 66 nodes 48429 nps 733772 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 f3e5 d8d
6 c1f4 c8f5
info multipv 1 depth 11 seldepth 14 score cp 23 time 96 nodes 75227 nps 783614 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 f3e5 d8d
6 c1f4 c8f5 e2e3
info multipv 1 depth 12 seldepth 15 score cp 30 time 166 nodes 139968 nps 843180 pv b1c3 b8c6 d2d4 d7d5 g1f3 c8f5 e2e3 c
6b4 e3e4 d5e4 f3h4 e7e6
info multipv 1 depth 13 seldepth 16 score cp 31 time 260 nodes 221530 nps 852038 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 f3e5 c
6e5 d4e5 d5d4 e5f6 d4c3 d1d8 e8d8
info multipv 1 depth 14 seldepth 19 score cp 18 time 922 nodes 804372 nps 872420 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5 d2d4 e
5d4 f3d4 f8b4 c1g5 e8g8 a2a3 b4c3 b2c3
info multipv 1 depth 15 seldepth 20 score cp 36 time 1572 nodes 1416443 nps 901045 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 c1g5 f8e7 b1c3 h8e8
info multipv 1 depth 16 seldepth 20 score cp 28 time 2174 nodes 1980383 nps 910939 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3
 e7e6 c2c4 d5f6 f1e2 b8c6 e1g1 f8e7 b1c3 e8g8
info multipv 1 depth 17 seldepth 21 score cp 36 time 2564 nodes 2352019 nps 917324 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3
 e7e6 c2c4 d5f6 f1e2 b8c6 b1c3 f8b4 e1g1 e8g8
info multipv 1 depth 18 seldepth 23 score cp 41 time 3141 nodes 2898694 nps 922857 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3
 e7e6 c2c4 d5f6 b1c3 b8c6 f1e2
info multipv 1 depth 19 seldepth 24 score cp 36 time 4914 nodes 4519082 nps 919634 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8e7 d4f3 d7d5 b1c3 d5e4 d1d8 e8d8 c3e4 d8e8 f1b5 c8f5 e4c5 a8b8
info multipv 1 depth 20 seldepth 27 score cp 33 time 7907 nodes 7334337 nps 927575 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8e7 f1b5 a7a6 b5c4 c6e5 c4e2 d7d5 b1c3 d5e4 c3e4 e7c6 d4c6 d8d1 e2d1
info multipv 1 depth 21 seldepth 27 score cp 20 time 12045 nodes 10515503 nps 873018 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 b4c3 b2c3 e8g8 e1g1 d7d5 f2f3 d5e4 f3e4 c8g4
info multipv 1 depth 22 seldepth 28 score cp 20 time 15286 nodes 13185334 nps 862575 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6
info multipv 1 depth 23 seldepth 30 score cp 20 time 24275 nodes 21468048 nps 884368 pv e2e4 e7e5
info multipv 1 depth 24 seldepth 30 score cp 30 time 34793 nodes 30889443 nps 887806 pv e2e4 e7e5 g1f3 g8f6 f3e5 d8e7 d2
d4 d7d6 e5c4 e7e4 c4e3 f6d5 b1c3 d5c3 b2c3 f8e7 f1d3 e4c6 d4d5 c6c5 e1g1 e8g8
info multipv 1 depth 24 seldepth 30 score cp 30 time 45000 nodes 40155162 nps 892336 pv e2e4 e7e5 g1f3 g8f6 f3e5 d8e7 d2
d4 d7d6 e5c4 e7e4 c4e3 f6d5 b1c3 d5c3 b2c3 f8e7 f1d3 e4c6 d4d5 c6c5 e1g1 e8g8
bestmove e2e4

Score of Altair1.3.3 vs Altair1.3.2: 589 - 576 - 335 [0.504]
...      Altair1.3.3 playing White: 349 - 234 - 167  [0.577] 750
...      Altair1.3.3 playing Black: 240 - 342 - 168  [0.432] 750
...      White vs Black: 691 - 474 - 335  [0.572] 1500
Elo difference: 3.0 +/- 15.5, LOS: 64.8 %, DrawRatio: 22.3 %
1500 of 1500 games finished.
```


### 1.3.4
More logical eval values. 
Passed pawn bonuses for 8 ranks, not just a coefficient.
Coefficients for blockers so the penalty is not applied as heavily on low rank passed pawns.

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 2 nodes 256 nps 128000 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 4 nodes 666 nps 166500 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 49 time 5 nodes 1162 nps 232400 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 7 nodes 2467 nps 352428 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 29 time 12 nodes 5970 nps 497500 pv b1c3 b8c6 d2d4 d7d5 e2e3 g8f6 g1f3
info multipv 1 depth 8 seldepth 9 score cp 25 time 24 nodes 15194 nps 633083 pv b1c3 b8c6 d2d4 d7d5 g1f3 e7e6 e2e4 g8f6

info multipv 1 depth 9 seldepth 11 score cp 26 time 44 nodes 27938 nps 634954 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 13 score cp 6 time 120 nodes 94844 nps 790366 pv b1c3 d7d5 d2d4 g8f6 g1f3 c8f5 c1f4 b8c
6
info multipv 1 depth 11 seldepth 15 score cp 44 time 242 nodes 190560 nps 787438 pv e2e4 b8c6 d2d4 d7d5 e4d5 d8d5 g1f3 d
5e6 c1e3 g8f6 b1c3 c8d7
info multipv 1 depth 12 seldepth 16 score cp 15 time 385 nodes 291513 nps 757176 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e
5d4 f3d4 f8b4 c1g5 e8g8
info multipv 1 depth 13 seldepth 16 score cp 9 time 636 nodes 511083 nps 803589 pv g1f3 d7d5 e2e3 g8f6 d2d4 e7e6 f1d3 b8
c6 e1g1 f8e7 f1e1 e8g8 b1c3
info multipv 1 depth 14 seldepth 17 score cp 8 time 742 nodes 610015 nps 822122 pv g1f3 d7d5 e2e3 g8f6 d2d4 e7e6 f1d3 b8
c6 e1g1 f8d6 b1c3 e8g8 c1d2 c8d7
info multipv 1 depth 15 seldepth 22 score cp 32 time 1441 nodes 1238250 nps 859299 pv e2e4 e7e5 d2d4 e5d4 g1f3 f8b4 b1d2
 b8c6 a2a3 b4d2 d1d2 g8f6 e4e5 f6g4 f3d4 c6e5 f1b5
info multipv 1 depth 16 seldepth 22 score cp 51 time 2798 nodes 2461809 nps 879845 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8c6 f1b5 f8b4 b5c6 b7c6 c2c3 e4d2 c3b4
info multipv 1 depth 17 seldepth 22 score cp 44 time 3541 nodes 3076303 nps 868766 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 c6d4 d1d4 g8e7 b1c3 e7c6 d4c4 f8d6 c3b5 d6e5 f1e2
info multipv 1 depth 18 seldepth 23 score cp 44 time 4081 nodes 3557291 nps 871671 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 c6d4 d1d4 g8e7 b1c3
info multipv 1 depth 19 seldepth 24 score cp 42 time 5391 nodes 4580882 nps 849727 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8e7 b1c3 c6d4 d1d4 e7c6 d4e3 f8d6 c3b5 d6e5 f1d3 a7a6 b5c3
info multipv 1 depth 20 seldepth 25 score cp 42 time 6986 nodes 6015479 nps 861076 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4

info multipv 1 depth 21 seldepth 25 score cp 39 time 9955 nodes 8723897 nps 876333 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8d7 f1e2 f8e7 c2c4 e8g8 c4d5 e4d2 c1d2 d7b6 e1g1
info multipv 1 depth 22 seldepth 28 score cp 36 time 15750 nodes 13022794 nps 826844 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4
e5 d7d5 b1d2 b8d7 f1e2 c7c6 e1g1 f8e7 c2c4 e8g8 c4d5 c6d5 d2e4 d5e4
info multipv 1 depth 23 seldepth 28 score cp 35 time 22616 nodes 18496481 nps 817849 pv e2e4 e7e5 g1f3 g8f6 d2d4 e5d4 e4
e5 d8e7 f1e2 f6g4 d1d4 h7h5 e1g1 b8c6 d4c3 g4e5 f1e1 d7d6 f3e5 c6e5 f2f4 e5g6
info multipv 1 depth 24 seldepth 30 score cp 22 time 34506 nodes 28274560 nps 819409 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 b4c3 b2c3 e8g8 e1g1 d7d5 e4d5 c6d5 f1e1 c8g4
info multipv 1 depth 24 seldepth 30 score cp 22 time 45003 nodes 37117952 nps 824788 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 b4c3 b2c3 e8g8 e1g1 d7d5 e4d5 c6d5 f1e1 c8g4
bestmove e2e4

Score of Altair1.3.4 vs Altair1.3.3: 352 - 312 - 336 [0.520]
...      Altair1.3.4 playing White: 221 - 101 - 178  [0.620] 500
...      Altair1.3.4 playing Black: 131 - 211 - 158  [0.420] 500
...      White vs Black: 432 - 232 - 336  [0.600] 1000
Elo difference: 13.9 +/- 17.5, LOS: 94.0 %, DrawRatio: 33.6 %
1000 of 1000 games finished.

Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.3.4                    26      19    1153     545     460     148    619.0   53.7%   12.8%   53.0%   54.3% 
   1 tantabus-windows-2019-x86-64-v3      61      26     576     283     183     110    338.0   58.7%   19.1%   58.3%   59.0% 
   2 admete_1.5.0_windows_x86-64    -115      29     577     177     362      38    196.0   34.0%    6.6%   33.0%   34.9% 

1157 of 2000 games finished.

5 + 0.05
Score of Altair1.3.4 vs Altair1.0.0: 210 - 74 - 116 [0.670]
...      Altair1.3.4 playing White: 103 - 36 - 61  [0.667] 200
...      Altair1.3.4 playing Black: 107 - 38 - 55  [0.672] 200
...      White vs Black: 141 - 143 - 116  [0.497] 400
Elo difference: 123.0 +/- 29.7, LOS: 100.0 %, DrawRatio: 29.0 %

3 + 2
Score of Altair1.3.4 vs Altair1.0.0: 23 - 7 - 10 [0.700]
...      Altair1.3.4 playing White: 13 - 1 - 6  [0.800] 20
...      Altair1.3.4 playing Black: 10 - 6 - 4  [0.600] 20
...      White vs Black: 19 - 11 - 10  [0.600] 40
Elo difference: 147.2 +/- 102.6, LOS: 99.8 %, DrawRatio: 25.0 %
44 of 500 games finished.

   1 Altair1.2.3                   111      81      55      28      11      16     36.0   65.5%   29.1%   74.1%   57.1% 
   2 Altair1.3.1                    57      81      55      25      16      14     32.0   58.2%   25.5%   57.1%   59.3% 
   3 Altair1.3.4                    32      80      54      22      17      15     29.5   54.6%   27.8%   51.9%   57.4% 
   4 Altair1.1.2                    25      75      55      20      16      19     29.5   53.6%   34.5%   61.1%   46.4% 
   5 Altair1.0.0                   -64      76      55      13      23      19     22.5   40.9%   34.5%   39.3%   42.6% 
   6 Altair1.0.1                  -174      93      54       9      34      11     14.5   26.9%   20.4%   29.6%   24.1% 

168 of 30000 games finished.

Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   1 Altair1.2.3                    19      73      54      18      15      21     28.5   52.8%   38.9%   59.3%   46.3% 
   2 Altair1.3.1                    -6      78      54      18      19      17     26.5   49.1%   31.5%   55.6%   42.6% 
   3 Altair1.3.4                   -13      75      54      16      18      20     26.0   48.1%   37.0%   50.0%   46.3% 

85 of 6000 games finished.
```


### 1.3.5
Removing changes from 1.2.7

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 28 nps 28000 pv b1c3
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 110 nps 110000 pv b1c3 b8c6
info multipv 1 depth 3 seldepth 3 score cp 64 time 3 nodes 256 nps 85333 pv b1c3 b8c6 g1f3
info multipv 1 depth 4 seldepth 4 score cp 7 time 4 nodes 666 nps 166500 pv b1c3 b8c6 g1f3 g8f6
info multipv 1 depth 5 seldepth 6 score cp 49 time 6 nodes 1162 nps 193666 pv b1c3 b8c6 g1f3 g8f6 e2e4
info multipv 1 depth 6 seldepth 7 score cp 7 time 8 nodes 2465 nps 308125 pv b1c3 b8c6 g1f3 g8f6 e2e4 e7e5
info multipv 1 depth 7 seldepth 8 score cp 29 time 13 nodes 5965 nps 458846 pv b1c3 b8c6 d2d4 d7d5 e2e3 g8f6 g1f3
info multipv 1 depth 8 seldepth 9 score cp 25 time 26 nodes 16096 nps 619076 pv b1c3 b8c6 d2d4 d7d5 g1f3 e7e6 e2e4 g8f6

info multipv 1 depth 9 seldepth 11 score cp 28 time 40 nodes 27787 nps 694675 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 c1f4 c8f5
 e2e3
info multipv 1 depth 10 seldepth 14 score cp 12 time 108 nodes 89462 nps 828351 pv g1f3 d7d5 d2d4 b8c6 d1d3 g8f6 c1f4 f6
h5 f4e5 c6e5
info multipv 1 depth 11 seldepth 16 score cp 13 time 165 nodes 140664 nps 852509 pv g1f3 d7d5 d2d4 b8c6 b1c3 c8f5 f3e5 c
6e5 d4e5 e7e6 c1f4
info multipv 1 depth 12 seldepth 16 score cp 22 time 352 nodes 292820 nps 831875 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 f1d3 b
8c6
info multipv 1 depth 13 seldepth 16 score cp 21 time 445 nodes 358520 nps 805662 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 f1d3 b
8c6 e1g1 f8e7 b1c3 e8g8 c1d2
info multipv 1 depth 14 seldepth 18 score cp 35 time 1244 nodes 1082525 nps 870196 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4
 g8f6 d4c6 d7c6 d1d8 e8d8 c1g5 f8b4 b1d2 h8e8
info multipv 1 depth 15 seldepth 22 score cp 13 time 1692 nodes 1484897 nps 877598 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 b4c3 b2c3
info multipv 1 depth 16 seldepth 22 score cp 31 time 2268 nodes 1864575 nps 822123 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 f1c4
 f8c5 e1g1 e8g8 d2d3 h7h6 c1e3 c5e3 f2e3 d7d6
info multipv 1 depth 17 seldepth 24 score cp 20 time 3425 nodes 2866222 nps 836853 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 e5d6 d8d6 d1e2 d6e6 b1d2 f8b4 c2c3 e4d2 c1d2
info multipv 1 depth 18 seldepth 24 score cp 28 time 4230 nodes 3605704 nps 852412 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 d4e5
 d7d5 b1d2 b8d7 f1e2 f8e7 e1g1 e8g8 c2c4 d7c5 c4d5 d8d5
info multipv 1 depth 19 seldepth 24 score cp 20 time 8084 nodes 5549827 nps 686519 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 f1d3
 d7d5 f3e5 b8d7 e5d7 c8d7 b1d2 e4d2 c1d2 d8e7 d1e2 e7e2 d3e2 d7f5 e1c1
info multipv 1 depth 20 seldepth 27 score cp 19 time 11499 nodes 8108637 nps 705160 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d
4 e5d4 f3d4 f8b4 d4c6 b7c6 d1d4 d8e7 f1d3 c6c5 d4e3 b4c3 b2c3 c5c4 d3c4
info multipv 1 depth 21 seldepth 27 score cp 19 time 15452 nodes 11673648 nps 755478 pv e2e4 e7e5 g1f3
info multipv 1 depth 22 seldepth 29 score cp 26 time 19663 nodes 15494153 nps 787985 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2
d4 e5d4 f3d4 f8b4 d4c6 b7c6 f1d3 b4c3 b2c3 d7d5 e4e5 d8e7 d1e2 f6g4 c1f4 e8g8
info multipv 1 depth 23 seldepth 30 score cp 27 time 42567 nodes 36246744 nps 851522 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 d2
d4 f8b4 f1b5 c8d7 b5d3 g8f6 d1e2 d8e7 c1g5 e8g8 e2e7 b4e7 g1f3 b8c6 e1g1 d7g4 a1e1
info multipv 1 depth 23 seldepth 31 score cp 27 time 44999 nodes 38434840 nps 854126 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 d2
d4 f8b4 f1b5 c8d7 b5d3 g8f6 d1e2 d8e7 c1g5 e8g8 e2e7 b4e7 g1f3 b8c6 e1g1 d7g4 a1e1
bestmove e2e4

Score of Altair1.3.5 vs Altair1.3.4: 3276 - 3070 - 3223  [0.511] 9569
...      Altair1.3.5 playing White: 2073 - 1100 - 1612  [0.602] 4785
...      Altair1.3.5 playing Black: 1203 - 1970 - 1611  [0.420] 4784
...      White vs Black: 4043 - 2303 - 3223  [0.591] 9569
Elo difference: 7.5 +/- 5.7, LOS: 99.5 %, DrawRatio: 33.7 %
SPRT: llr 2.97 (100.7%), lbound -2.94, ubound 2.94 - H1 was accepted
```


```
Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw
   1 Altair1.2.6                    28      14    1710     673     536     501    923.5   54.0%   29.3%
   2 Altair1.2.3                     9      14    1710     647     602     461    877.5   51.3%   27.0%
   3 Altair1.3.5                     5      14    1711     619     594     498    868.0   50.7%   29.1%
   4 Altair1.3.0                     5      14    1710     620     596     494    867.0   50.7%   28.9%
   5 Altair1.2.7                     0      14    1709     619     619     471    854.5   50.0%   27.6%
   6 Altair1.2.4                    -1      14    1710     608     612     490    853.0   49.9%   28.7%
   7 Altair1.3.3                    -4      14    1709     600     618     491    845.5   49.5%   28.7%
   8 Altair1.3.4                    -6      14    1710     591     621     498    840.0   49.1%   29.1%
   9 Altair1.3.2                    -6      14    1710     591     621     498    840.0   49.1%   29.1%
  10 Altair1.3.1                    -8      14    1710     595     632     483    836.5   48.9%   28.2%
  11 Altair1.2.9                    -8      14    1711     573     612     526    836.0   48.9%   30.7%
  12 Altair1.2.8                   -15      14    1710     558     631     521    818.5   47.9%   30.5%

```


### 1.3.6
FINALLY TUNING

```
Score of Altair1.3.6 vs Altair1.3.5: 168 - 111 - 67 [0.582]
...      Altair1.3.6 playing White: 106 - 31 - 37  [0.716] 174
...      Altair1.3.6 playing Black: 62 - 80 - 30  [0.448] 172
...      White vs Black: 186 - 93 - 67  [0.634] 346
Elo difference: 57.8 +/- 33.3, LOS: 100.0 %, DrawRatio: 19.4 %
350 of 6000 games finished.

info multipv 1 depth 1 seldepth 1 score cp 12 time 1 nodes 27 nps 27000 pv e2e4
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 112 nps 112000 pv e2e4 e7e5
info multipv 1 depth 3 seldepth 3 score cp 7 time 2 nodes 253 nps 126500 pv e2e4 e7e5 b1c3
info multipv 1 depth 4 seldepth 5 score cp 8 time 3 nodes 964 nps 321333 pv d2d4 d7d5 g1f3 g8f6
info multipv 1 depth 5 seldepth 7 score cp 7 time 5 nodes 2028 nps 405600 pv b1c3 e7e5 d2d4 b8c6 d4e5
info multipv 1 depth 6 seldepth 8 score cp 8 time 9 nodes 4538 nps 504222 pv b1c3 e7e5 e2e4 b8c6 g1f3 g8f6
info multipv 1 depth 7 seldepth 9 score cp 6 time 20 nodes 13530 nps 676500 pv e2e4 e7e5 b1c3 b8c6
info multipv 1 depth 8 seldepth 10 score cp 12 time 36 nodes 26613 nps 739250 pv e2e4 e7e5 b1c3 b8c6 g1f3 f8c5 f1b5 d7d6
info multipv 1 depth 9 seldepth 12 score cp 8 time 80 nodes 64563 nps 807037 pv e2e4 e7e6 d2d4 d7d5 b1c3 b8c6 g1f3
info multipv 1 depth 10 seldepth 13 score cp 8 time 129 nodes 106698 nps 827116 pv e2e4 c7c5 d2d4 c5d4 g1f3 e7e5 c2c3 d7d5 e4d5 d8d5
info multipv 1 depth 11 seldepth 14 score cp 8 time 178 nodes 149063 nps 837432 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 d2d4 c5d4 f3d4 c6d4 d1d4
info multipv 1 depth 12 seldepth 16 score cp 10 time 230 nodes 196415 nps 853978 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1e2 d7d5 e4d5 f6d5 e1g1 d5f4
info multipv 1 depth 13 seldepth 17 score cp 3 time 608 nodes 531771 nps 874623 pv g1f3 d7d5 d2d4 g8f6 e2e3 e7e6 f1d3 b8c6
info multipv 1 depth 14 seldepth 18 score cp 8 time 784 nodes 691132 nps 881545 pv g1f3 d7d5 d2d4 g8f6 e2e3 e7e6 f1d3 b8c6 e1g1 f8d6 b1c3 e8g8 h2h3 h7h6
info multipv 1 depth 15 seldepth 18 score cp 5 time 1091 nodes 965224 nps 884714 pv g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 f1d3 b8c6 e1g1 f8d6 b1c3 e8g8 c3b5 h7h6 c2c3
info multipv 1 depth 16 seldepth 20 score cp 5 time 1770 nodes 1579872 nps 892583 pv g1f3 g8f6 d2d4 d7d5 e2e3 e7e6 b1c3 f8b4 f1d3 b4c3 b2c3 f6e4 c1b2 e8g8 e1g1
info multipv 1 depth 17 seldepth 22 score cp 10 time 4062 nodes 3640454 nps 896222 pv e2e4 c7c5 g1f3 b8c6 f1c4 g8f6 b1c3
info multipv 1 depth 18 seldepth 23 score cp 7 time 6890 nodes 6134741 nps 890383 pv e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 e1g1 f8e7 b1c3 e8g8 d2d3 d7d6 a2a3 a7a6 c4a2 b7b6 c1g5 f6g4
info multipv 1 depth 19 seldepth 25 score cp 8 time 8555 nodes 7634678 nps 892422 pv e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 e1g1 f8e7 b1c3 e8g8 d2d4 e5d4 f3d4 c6d4 d1d4 c7c6 e4e5 d7d5 e5f6
info multipv 1 depth 20 seldepth 25 score cp 8 time 10528 nodes 9417052 nps 894476 pv e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 e1g1
info multipv 1 depth 21 seldepth 25 score cp 8 time 13108 nodes 11726784 nps 894628 pv e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 e1g1 f8e7 b1c3 e8g8 d2d4 f6e4 d4e5 e4c3 b2c3 d7d6 e5d6 c7d6 f1e1 e7f6 c1b2
info multipv 1 depth 22 seldepth 25 score cp 8 time 17215 nodes 15362335 nps 892380 pv e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 e1g1 f8e7
info multipv 1 depth 23 seldepth 28 score cp 9 time 30663 nodes 27412824 nps 894003 pv e2e4 e7e5 d2d4 e5d4 g1f3 b8c6 f3d4 g8f6 d4c6 b7c6 e4e5 f6e4 b1d2 e4d2 d1d2 a8b8 f1e2 f8e7 e1g1 e8g8 d2d3
info multipv 1 depth 23 seldepth 28 score cp 9 time 45000 nodes 40263686 nps 894748 pv e2e4 e7e5 d2d4 e5d4 g1f3 b8c6 f3d4 g8f6 d4c6 b7c6 e4e5 f6e4 b1d2 e4d2 d1d2 a8b8 f1e2 f8e7 e1g1 e8g8 d2d3
bestmove e2e4
```


### 1.3.7
Bug fix in tuner and K values

```

info multipv 1 depth 1 seldepth 1 score cp 46 time 1 nodes 25 nps 25000 pv e2e4
info multipv 1 depth 2 seldepth 2 score cp 7 time 2 nodes 91 nps 45500 pv e2e4 e7e5
info multipv 1 depth 3 seldepth 3 score cp 38 time 3 nodes 223 nps 74333 pv e2e4 e7e5 g1f3
info multipv 1 depth 4 seldepth 6 score cp 11 time 5 nodes 1136 nps 227200 pv g1f3 d7d5 d2d4 g8f6
info multipv 1 depth 5 seldepth 6 score cp 42 time 7 nodes 1815 nps 259285 pv g1f3 d7d5 d2d4 g8f6 b1c3
info multipv 1 depth 6 seldepth 8 score cp 14 time 10 nodes 4474 nps 447400 pv e2e4 e7e5 d2d4 g8f6 d4e5 f6e4
info multipv 1 depth 7 seldepth 9 score cp 29 time 16 nodes 7919 nps 494937 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 d2d4
info multipv 1 depth 8 seldepth 10 score cp 24 time 25 nodes 14915 nps 596600 pv e2e4 d7d5 e4e5 b8c6 d2d4 c8f5 b1c3
info multipv 1 depth 9 seldepth 11 score cp 36 time 48 nodes 33487 nps 697645 pv e2e4 e7e5 g1f3 b8c6 f1d3 g8f6 e1g1 d7d5 b1c3
info multipv 1 depth 10 seldepth 12 score cp 43 time 75 nodes 55795 nps 743933 pv e2e4 e7e5 g1f3 b8c6 c2c3 g8f6 d2d4 d7d5 e4d5 d8d5
info multipv 1 depth 11 seldepth 14 score cp 29 time 146 nodes 119313 nps 817212 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4
info multipv 1 depth 12 seldepth 15 score cp 23 time 228 nodes 193043 nps 846679 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6
info multipv 1 depth 13 seldepth 16 score cp 15 time 468 nodes 399785 nps 854241 pv g1f3 d7d5 e2e3 e7e6 c2c4 g8f6 d2d4 f8b4 c1d2 b8c6 c4d5 e6d5 f1b5 a7a5
info multipv 1 depth 14 seldepth 18 score cp 17 time 616 nodes 534832 nps 868233 pv g1f3 d7d5 e2e3 e7e6 c2c4 g8f6 d2d4 f8e7 f1d3 e8g8 e1g1 d5c4 d3c4 b8c6
info multipv 1 depth 15 seldepth 18 score cp 21 time 878 nodes 777526 nps 885564 pv g1f3 d7d5 e2e3 e7e6 c2c4 g8f6 d2d4 b8c6 c4d5 e6d5 f1d3 f8b4 b1c3 e8g8 e1g1 c8e6
info multipv 1 depth 16 seldepth 20 score cp 30 time 2560 nodes 2296409 nps 897034 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 f8e7 f1d3 b8c6 e1g1 g8f6 f1e1 e8g8 b1c3
info multipv 1 depth 17 seldepth 21 score cp 21 time 4881 nodes 4437676 nps 909173 pv g1f3 g8f6 d2d4 d7d5 e2e3 c7c5 f1e2 e7e6 e1g1 c5d4 e3d4 f8d6 b1c3 b8c6 c3b5 e8g8 b5d6
info multipv 1 depth 18 seldepth 24 score cp 23 time 6008 nodes 5486732 nps 913237 pv g1f3 g8f6 d2d4 d7d5 c2c4 e7e6 e2e3 b8c6 b1c3 f8e7 f1e2 e8g8 e1g1 f6e4 c4d5 e6d5 c3e4 d5e4
info multipv 1 depth 19 seldepth 25 score cp 27 time 14542 nodes 13286785 nps 913683 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 g8f6 b1c3 b8c6 f1d3 f8d6 e1g1 e8g8 f1e1 c8e6
info multipv 1 depth 20 seldepth 25 score cp 27 time 16095 nodes 14713029 nps 914136 pv e2e4 e7e6 g1f3 d7d5 e4d5
info multipv 1 depth 21 seldepth 25 score cp 27 time 17954 nodes 16432844 nps 915274 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 f8d6 f1d3 g8f6 e1g1 e8g8 f1e1 b8c6 b1c3
info multipv 1 depth 22 seldepth 27 score cp 26 time 23139 nodes 21113200 nps 912450 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 g8f6 f1d3 b8c6 e1g1 f8e7 c2c3 e8g8 f1e1 f8e8 c1f4 h7h6 b1d2 c8e6
info multipv 1 depth 23 seldepth 27 score cp 26 time 27908 nodes 25350005 nps 908341 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 f8e7 f1d3 g8f6 e1g1 e8g8 f1e1 b8c6 c2c3
info multipv 1 depth 23 seldepth 29 score cp 26 time 45002 nodes 40865811 nps 908088 pv e2e4 e7e6 g1f3 d7d5 e4d5 e6d5 d2d4 f8e7 f1d3 g8f6 e1g1 e8g8 f1e1 b8c6 c2c3
bestmove e2e4

Score of Altair1.3.7 vs Altair1.3.6: 305 - 198 - 236 [0.572]
...      Altair1.3.7 playing White: 198 - 69 - 103  [0.674] 370
...      Altair1.3.7 playing Black: 107 - 129 - 133  [0.470] 369
...      White vs Black: 327 - 176 - 236  [0.602] 739
Elo difference: 50.7 +/- 20.8, LOS: 100.0 %, DrawRatio: 31.9 %
743 of 4000 games finished.
```

### 1.3.8
MVV-LVA values changed to match piece values

```
info multipv 1 depth 1 seldepth 1 score cp 46 time 1 nodes 25 nps 25000 pv e2e4
info multipv 1 depth 2 seldepth 2 score cp 7 time 1 nodes 91 nps 91000 pv e2e4 e7e5
info multipv 1 depth 3 seldepth 3 score cp 38 time 2 nodes 223 nps 111500 pv e2e4 e7e5 g1f3
info multipv 1 depth 4 seldepth 6 score cp 8 time 4 nodes 835 nps 208750 pv e2e4 e7e5 d2d4 b8c6
info multipv 1 depth 5 seldepth 7 score cp 41 time 6 nodes 2135 nps 355833 pv e2e4 e7e5 b1c3 g8f6 g1f3
info multipv 1 depth 6 seldepth 8 score cp 10 time 10 nodes 4807 nps 480700 pv e2e4 e7e5 g1f3 g8f6 d2d4 d7d5
info multipv 1 depth 7 seldepth 9 score cp 30 time 14 nodes 8379 nps 598500 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
info multipv 1 depth 8 seldepth 10 score cp 27 time 27 nodes 19078 nps 706592 pv e2e4 e7e6 b1c3 d7d5 d2d4 b8c6 g1f3 g8f6
info multipv 1 depth 9 seldepth 11 score cp 30 time 45 nodes 34690 nps 770888 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4 e5d4 f3d4
info multipv 1 depth 10 seldepth 12 score cp 19 time 63 nodes 49815 nps 790714 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4 e5d4 f3d4 f8d6
info multipv 1 depth 11 seldepth 15 score cp 30 time 99 nodes 81152 nps 819717 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4 e5d4 f3d4 c6d4 d1d4
info multipv 1 depth 12 seldepth 17 score cp 14 time 163 nodes 139876 nps 858134 pv e2e4 e7e5 g1f3 b8c6 b1c3 f8d6 f1e2 g8f6 e1g1 e8g8 d2d4 e5d4
info multipv 1 depth 13 seldepth 17 score cp 26 time 274 nodes 242130 nps 883686 pv e2e4 e7e5 g1f3 b8c6 c2c3 g8f6 d2d4 e5d4 e4e5 f6e4 f1d3 d7d5 c3d4
info multipv 1 depth 14 seldepth 17 score cp 22 time 656 nodes 601006 nps 916167 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 c2c4 f8e7 f1e2 e8g8 e1g1 c7c5 c4d5 e6d5
info multipv 1 depth 15 seldepth 19 score cp 24 time 1153 nodes 1076841 nps 933947 pv d2d4 g8f6 c2c4 e7e6 g1f3 f8e7 d4d5 e8g8 b1c3 e7b4 c1g5 c7c6 d5d6 h7h6 g5e3
info multipv 1 depth 16 seldepth 20 score cp 26 time 1914 nodes 1809433 nps 945367 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8f6 e4e5 c7c5 d4d1 d8e7 d1e2 f6d5
info multipv 1 depth 17 seldepth 21 score cp 33 time 2535 nodes 2373538 nps 936306 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8f6 e4e5 c7c5 d4d1 d8e7 d1e2 f6d5 b1d2
info multipv 1 depth 18 seldepth 24 score cp 33 time 2998 nodes 2825337 nps 942407 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4
info multipv 1 depth 19 seldepth 24 score cp 40 time 4368 nodes 4123832 nps 944100 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8e7 c1e3 e7c6 d4d1 f8d6 f1e2 d6e5 c2c3 e8g8 e1g1
info multipv 1 depth 20 seldepth 25 score cp 19 time 8450 nodes 7965137 nps 942619 pv e2e4 c7c5 b1c3 b8c6 g1f3 e7e5 f1c4 f8e7 e1g1 d7d6 c3d5 g8f6 d2d3 e8g8 c2c3
info multipv 1 depth 21 seldepth 25 score cp 24 time 11559 nodes 10860300 nps 939553 pv e2e4 c7c5 g1f3 b8c6 c2c3 d7d5 e4d5 d8d5 d2d4 g8f6 f1e2 c8f5 e1g1 c5d4 c3d4 f5b1 a1b1 e8c8 c1e3 d5a2
info multipv 1 depth 22 seldepth 28 score cp 29 time 18046 nodes 16929834 nps 938148 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 f1b5 a7a6 b5c6 d7c6 e4e5 f6d5 c3e4 e7e6 d2d4 c5d4 d1d4 f8e7 e1g1
info multipv 1 depth 23 seldepth 28 score cp 29 time 23275 nodes 21831648 nps 937987 pv e2e4 c7c5 g1f3
info multipv 1 depth 24 seldepth 28 score cp 22 time 36502 nodes 34294467 nps 939522 pv e2e4 c7c5 g1f3 b8c6 b1c3 e7e5 f1c4 f8e7 e1g1 g8f6 d2d3 e8g8 c3d5 d7d6 c2c3 a7a6 a2a3 c8e6 f3g5 f6d5 g5e6 f7e6 e4d5
info multipv 1 depth 24 seldepth 30 score cp 22 time 45000 nodes 42254352 nps 938985 pv e2e4 c7c5 g1f3 b8c6 b1c3 e7e5 f1c4 f8e7 e1g1 g8f6 d2d3 e8g8 c3d5 d7d6 c2c3 a7a6 a2a3 c8e6 f3g5 f6d5 g5e6 f7e6 e4d5
bestmove e2e4

Score of Altair1.3.8 vs Altair1.3.7: 2031 - 1877 - 2136  [0.513] 6044
...      Altair1.3.8 playing White: 1300 - 677 - 1046  [0.603] 3023
...      Altair1.3.8 playing Black: 731 - 1200 - 1090  [0.422] 3021
...      White vs Black: 2500 - 1408 - 2136  [0.590] 6044
Elo difference: 8.9 +/- 7.0, LOS: 99.3 %, DrawRatio: 35.3 %
SPRT: llr 2.99 (101.4%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

### 1.3.9
Tuning Mobility

```
info multipv 1 depth 1 seldepth 1 score cp 73 time 1 nodes 27 nps 27000 pv e2e4
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 136 nps 136000 pv e2e4 e7e5
info multipv 1 depth 3 seldepth 3 score cp 49 time 2 nodes 265 nps 132500 pv e2e4 e7e5 b1c3
info multipv 1 depth 4 seldepth 5 score cp 19 time 4 nodes 877 nps 219250 pv e2e4 g8f6 e4e5 f6e4
info multipv 1 depth 5 seldepth 7 score cp 37 time 6 nodes 1975 nps 329166 pv e2e4 b8c6 d2d4 d7d5 e4d5
info multipv 1 depth 6 seldepth 8 score cp 22 time 12 nodes 6686 nps 557166 pv b1c3 g8f6 e2e4 d7d5 e4d5 f6d5
info multipv 1 depth 7 seldepth 9 score cp 44 time 21 nodes 13477 nps 641761 pv e2e4 d7d5 e4d5 g8f6 d2d4 c7c6 d5c6
info multipv 1 depth 8 seldepth 10 score cp 8 time 53 nodes 41887 nps 790320 pv e2e3 b8c6 b1c3 d7d5 g1f3 g8f6 d2d4 e7e6 
info multipv 1 depth 9 seldepth 11 score cp 32 time 90 nodes 74344 nps 826044 pv d2d4 d7d5 e2e3 c7c5 g1f3 e7e6 b1c3 b8c6 f1d3
info multipv 1 depth 10 seldepth 13 score cp 21 time 145 nodes 124617 nps 859427 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4 e5d4 f3d4 f8d6
info multipv 1 depth 11 seldepth 16 score cp 48 time 179 nodes 155031 nps 866094 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4 e5d4 f3d4 d7d5 e4d5
info multipv 1 depth 12 seldepth 16 score cp 29 time 254 nodes 221207 nps 870893 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8f6 e4e5 d8e7
info multipv 1 depth 13 seldepth 17 score cp 36 time 550 nodes 493646 nps 897538 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1e2 e7e5 e1g1 f8d6 d2d3 e8g8 c1e3
info multipv 1 depth 14 seldepth 17 score cp 24 time 739 nodes 670808 nps 907723 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1b5 e7e6 e1g1 a7a6 b5c6 d7c6 d2d4 f8d6
info multipv 1 depth 15 seldepth 18 score cp 35 time 931 nodes 854044 nps 917340 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1b5 e7e6 e1g1 a7a6 b5c6 d7c6 e4e5 f6g4 d2d3
info multipv 1 depth 16 seldepth 20 score cp 26 time 1757 nodes 1595901 nps 908310 pv e2e4 c7c5 d2d4 c5d4 c2c3 d4c3 b1c3 e7e6 g1f3 b8c6
info multipv 1 depth 17 seldepth 22 score cp 20 time 3927 nodes 3612466 nps 919904 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 e2e3 f8e7 c4d5 e6d5 b1c3 b8c6 f1d3 e8g8 e1g1 c6b4 d3b1
info multipv 1 depth 18 seldepth 22 score cp 20 time 4592 nodes 4234946 nps 922244 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 e2e3 f8e7 c4d5
info multipv 1 depth 19 seldepth 23 score cp 19 time 6539 nodes 6058538 nps 926523 pv g1f3 d7d5 d2d4 g8f6 c2c4 e7e6 e2e3 f8e7 c4d5 e6d5 b1c3 e8g8 a2a3 c7c5 f1d3 c5c4 d3c2 b8c6 e1g1
info multipv 1 depth 20 seldepth 23 score cp 28 time 9597 nodes 8908776 nps 928287 pv d2d4 d7d5 e2e3 g8f6 c2c4 e7e6 g1f3 f8e7 c4d5 e6d5 f1d3 e8g8 e1g1 a7a6 b1c3 b8c6 a2a3 h7h6
info multipv 1 depth 21 seldepth 25 score cp 36 time 17637 nodes 16347930 nps 926911 pv d2d4 d7d5 g1f3 g8f6 c2c4 e7e6 b1c3 f8b4 e2e3 f6e4 c1d2 e4d2 d1d2 e8g8 c4d5 e6d5 f1d3 b4c3 d2c3
info multipv 1 depth 22 seldepth 29 score cp 25 time 38644 nodes 35603120 nps 921310 pv d2d4 d7d5 e2e3 g8f6 g1f3 c7c5 c2c4 c5d4 e3d4 c8e6 c4d5 e6d5 f1e2 b8c6 e1g1 a8c8 b1c3 e7e6 c3d5 f6d5 f3e5 f8d6
info multipv 1 depth 22 seldepth 29 score cp 25 time 44999 nodes 41484323 nps 921894 pv d2d4 d7d5 e2e3 g8f6 g1f3 c7c5 c2c4 c5d4 e3d4 c8e6 c4d5 e6d5 f1e2 b8c6 e1g1 a8c8 b1c3 e7e6 c3d5 f6d5 f3e5 f8d6
bestmove d2d4


Score of Altair1.3.9 vs Altair1.3.8: 1171 - 1054 - 1062  [0.518] 3287
...      Altair1.3.9 playing White: 726 - 418 - 500  [0.594] 1644
...      Altair1.3.9 playing Black: 445 - 636 - 562  [0.442] 1643
...      White vs Black: 1362 - 863 - 1062  [0.576] 3287
Elo difference: 12.4 +/- 9.8, LOS: 99.3 %, DrawRatio: 32.3 %
SPRT: llr 2.97 (100.7%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

### 1.4.0
Tuning Tropism

```
info multipv 1 depth 1 seldepth 1 score cp 63 time 1 nodes 28 nps 28000 pv e2e4
info multipv 1 depth 2 seldepth 2 score cp 8 time 1 nodes 137 nps 137000 pv e2e4 e7e5
info multipv 1 depth 3 seldepth 3 score cp 47 time 2 nodes 276 nps 138000 pv e2e4 e7e5 d2d4
info multipv 1 depth 4 seldepth 6 score cp 11 time 4 nodes 1134 nps 283500 pv e2e4 d7d5 e4d5 d8d5
info multipv 1 depth 5 seldepth 7 score cp 42 time 7 nodes 2653 nps 379000 pv d2d4 d7d5 g1f3 g8f6 b1c3
info multipv 1 depth 6 seldepth 8 score cp 20 time 12 nodes 6390 nps 532500 pv e2e4 d7d5 e4d5 g8f6 c2c4 c8g4
info multipv 1 depth 7 seldepth 9 score cp 41 time 17 nodes 9557 nps 562176 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3
info multipv 1 depth 8 seldepth 11 score cp 25 time 27 nodes 17060 nps 631851 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5b4
info multipv 1 depth 9 seldepth 11 score cp 50 time 38 nodes 25741 nps 677394 pv e2e4 d7d5 e4d5 g8f6 d2d4 d8d5 g1f3 d5e4 f1e2 b8c6
info multipv 1 depth 10 seldepth 13 score cp 30 time 61 nodes 45853 nps 751688 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 b8c6 c2c4 d5f6
info multipv 1 depth 11 seldepth 15 score cp 42 time 128 nodes 103530 nps 808828 pv e2e4 e7e6 d2d4 d7d5 b1c3 d5e4 c3e4 g8f6 c1g5 f8e7 f1b5 b8c6
info multipv 1 depth 12 seldepth 15 score cp 33 time 233 nodes 200206 nps 859253 pv e2e4 e7e6 d2d4 d7d5 b1c3 g8f6 e4e5 f6e4 g1f3 e4c3 b2c3 b8c6
info multipv 1 depth 13 seldepth 17 score cp 20 time 530 nodes 472550 nps 891603 pv e2e4 e7e5 b1c3 g8f6 g1f3 b8c6 f1b5 f8d6 d2d4 e5d4 f3d4 e8g8 e1g1
info multipv 1 depth 14 seldepth 18 score cp 41 time 827 nodes 746828 nps 903056 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 f1d3 d7d5 d4e5 b8c6 b1d2 e4c5 e1g1 c5d3
info multipv 1 depth 15 seldepth 18 score cp 42 time 1012 nodes 925280 nps 914308 pv e2e4 e7e5 g1f3 g8f6 f3e5 d7d6 e5f3 f6e4 f1e2 f8e7 d2d3 e4f6 b1c3 e8g8 e1g1
info multipv 1 depth 16 seldepth 20 score cp 41 time 1538 nodes 1418906 nps 922565 pv e2e4 e7e5 g1f3 g8f6 b1c3 f8b4 f1d3 b8c6 c3d5 e8g8 e1g1 d7d6 c2c3 b4c5 b2b4 f6d5
info multipv 1 depth 17 seldepth 22 score cp 28 time 4127 nodes 3792113 nps 918854 pv d2d4 g8f6 g1f3 e7e6 c2c4 f8b4 c1d2 b8c6 e2e3 e8g8 f1d3 b4d2 b1d2 c6b4 d1b3 b4d3 b3d3 d7d5 e1g1 f6g4
info multipv 1 depth 18 seldepth 23 score cp 29 time 5190 nodes 4798397 nps 924546 pv d2d4 g8f6 g1f3 e7e6 c2c4 d7d5 e2e3 b8c6 b1c3 f8e7 f1e2 e8g8 e1g1 a7a5 c1d2 h7h6 d1b3 e7d6
info multipv 1 depth 19 seldepth 23 score cp 29 time 6233 nodes 5794979 nps 929725 pv d2d4 g8f6 g1f3 e7e6 c2c4 d7d5
info multipv 1 depth 20 seldepth 23 score cp 29 time 7496 nodes 6986126 nps 931980 pv d2d4 g8f6 g1f3
info multipv 1 depth 21 seldepth 26 score cp 29 time 9760 nodes 9076970 nps 930017 pv d2d4 g8f6 g1f3 e7e6 c2c4 d7d5 e2e3 b8c6 b1c3 f8e7 f1e2 e8g8 e1g1 a7a5 c1d2 f6e4 c4c5 e4d2 d1d2
info multipv 1 depth 22 seldepth 29 score cp 24 time 34408 nodes 31342329 nps 910902 pv d2d4 g8f6 g1f3 e7e6 c2c4 f8e7 b1c3 d7d5 c4d5 e6d5 e2e3 e8g8 f1d3 c7c5 d4c5 e7c5 e1g1 b8c6
info multipv 1 depth 22 seldepth 29 score cp 24 time 44999 nodes 41148416 nps 914429 pv d2d4 g8f6 g1f3 e7e6 c2c4 f8e7 b1c3 d7d5 c4d5 e6d5 e2e3 e8g8 f1d3 c7c5 d4c5 e7c5 e1g1 b8c6
bestmove d2d4

Score of Altair1.4.0 vs Altair1.3.9: 697 - 600 - 606  [0.525] 1903
...      Altair1.4.0 playing White: 438 - 213 - 301  [0.618] 952
...      Altair1.4.0 playing Black: 259 - 387 - 305  [0.433] 951
...      White vs Black: 825 - 472 - 606  [0.593] 1903
Elo difference: 17.7 +/- 12.9, LOS: 99.6 %, DrawRatio: 31.8 %
SPRT: llr 2.94 (100.0%), lbound -2.94, ubound 2.94 - H1 was accepted
Finished match
```

### 1.4.1
Tuning King Pawn Shields

```
info multipv 1 depth 1 seldepth 1 score cp 58 time 1 nodes 29 nps 29000 pv e2e4
info multipv 1 depth 2 seldepth 2 score cp 19 time 1 nodes 107 nps 107000 pv e2e4 e7e5
info multipv 1 depth 3 seldepth 3 score cp 46 time 2 nodes 248 nps 124000 pv e2e4 e7e5 d2d4
info multipv 1 depth 4 seldepth 5 score cp 24 time 4 nodes 749 nps 187250 pv e2e4 e7e5 d2d4 b8c6
info multipv 1 depth 5 seldepth 7 score cp 43 time 7 nodes 2520 nps 360000 pv e2e4 d7d5 e4d5 c7c6 d5c6
info multipv 1 depth 6 seldepth 8 score cp 23 time 14 nodes 8065 nps 576071 pv e2e4 e7e5 g1f3 g8f6 d2d4 d7d5
info multipv 1 depth 7 seldepth 9 score cp 47 time 19 nodes 10926 nps 575052 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4
info multipv 1 depth 8 seldepth 10 score cp 40 time 29 nodes 19090 nps 658275 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 d7d5
info multipv 1 depth 9 seldepth 12 score cp 47 time 39 nodes 27020 nps 692820 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 d7d5 b1c3
info multipv 1 depth 10 seldepth 12 score cp 42 time 55 nodes 40649 nps 739072 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8f6
info multipv 1 depth 11 seldepth 14 score cp 34 time 107 nodes 86964 nps 812747 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 d7d5 c1g5
info multipv 1 depth 12 seldepth 16 score cp 41 time 228 nodes 196859 nps 863416 pv e2e4 e7e6 d2d4 c7c5 g1f3 c5d4 f3d4 b8c6 b1c3 g8f6 d4c6 b7c6
info multipv 1 depth 13 seldepth 17 score cp 47 time 505 nodes 444632 nps 880459 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1c4 e7e6 e1g1 f8d6 d2d4 c5d4 f3d4
info multipv 1 depth 14 seldepth 17 score cp 30 time 671 nodes 602355 nps 897697 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1e2 e7e5 e1g1 f8e7 d2d3 e8g8 c1g5 f6g4
info multipv 1 depth 15 seldepth 18 score cp 43 time 856 nodes 781354 nps 912796 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1b5 e7e5 b5c6 d7c6 f3e5 f8d6 d2d4 e8g8 e1g1
info multipv 1 depth 16 seldepth 19 score cp 34 time 1293 nodes 1160302 nps 897372 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1c4 e7e6 e1g1 f8d6 d2d3 e8g8 c3b5 d6e5 f3e5 c6e5
info multipv 1 depth 17 seldepth 23 score cp 29 time 1940 nodes 1787000 nps 921134 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1c4 e7e6 e1g1 f8d6 d2d4 c5d4 f3d4 e8g8 c1g5 c6d4 d1d4
info multipv 1 depth 18 seldepth 23 score cp 29 time 2530 nodes 2351051 nps 929269 pv e2e4 c7c5 b1c3 b8c6 g1f3
info multipv 1 depth 19 seldepth 24 score cp 27 time 4945 nodes 4509518 nps 911934 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e5 e1g1 d7d6 b1c3 g8f6 d2d3 f8e7 c3d5 e8g8 d5e7 d8e7 c1g5 a7a6 b5c6 b7c6
info multipv 1 depth 20 seldepth 24 score cp 27 time 6216 nodes 5657978 nps 910228 pv e2e4 c7c5 g1f3 b8c6 f1b5
info multipv 1 depth 21 seldepth 28 score cp 19 time 17884 nodes 16455229 nps 920108 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1e2 d7d5 e4d5 f6d5 e1g1 d5c3 d2c3 d8d1 f1d1 c8f5 d1d5 f5e6 d5b5 e5e4 f3g5
info multipv 1 depth 22 seldepth 28 score cp 23 time 20650 nodes 19023248 nps 921222 pv e2e4 e7e5 d2d4 e5d4 g1f3 b8c6 f3d4 g8f6 d4c6 b7c6 e4e5 d8e7 d1e2 f6d5 b1d2 c8b7 c2c4 d5b4 d2f3 e8c8
info multipv 1 depth 23 seldepth 29 score cp 28 time 41240 nodes 38258812 nps 927711 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e5 e1g1 f8d6 b1c3 g8f6 d2d3 e8g8 a2a4 h7h6 b5c4 d6c7 h2h3 d7d6
info multipv 1 depth 23 seldepth 29 score cp 28 time 45001 nodes 41795611 nps 928770 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e5 e1g1 f8d6 b1c3 g8f6 d2d3 e8g8 a2a4 h7h6 b5c4 d6c7 h2h3 d7d6
bestmove e2e4

Score of Altair1.4.1 vs Altair1.4.0: 1225 - 1106 - 1195  [0.517] 3526
...      Altair1.4.1 playing White: 771 - 418 - 574  [0.600] 1763
...      Altair1.4.1 playing Black: 454 - 688 - 621  [0.434] 1763
...      White vs Black: 1459 - 872 - 1195  [0.583] 3526
Elo difference: 11.7 +/- 9.3, LOS: 99.3 %, DrawRatio: 33.9 %
SPRT: llr 2.97 (101.0%), lbound -2.94, ubound 2.94 - H1 was accepted

Score of Altair1.4.1 vs tantabus-windows-2019-x86-64-v3: 187 - 56 - 86 [0.699]
...      Altair1.4.1 playing White: 92 - 31 - 42  [0.685] 165
...      Altair1.4.1 playing Black: 95 - 25 - 44  [0.713] 164
...      White vs Black: 117 - 126 - 86  [0.486] 329
Elo difference: 146.4 +/- 34.1, LOS: 100.0 %, DrawRatio: 26.1 %

Score of Altair1.4.1 vs wyldchess1.51_popcnt: 258 - 270 - 115 [0.491]
...      Altair1.4.1 playing White: 116 - 142 - 64  [0.460] 322
...      Altair1.4.1 playing Black: 142 - 128 - 51  [0.522] 321
...      White vs Black: 244 - 284 - 115  [0.469] 643
Elo difference: -6.5 +/- 24.3, LOS: 30.1 %, DrawRatio: 17.9 %
647 of 1000 games finished.
```


### 1.4.2
Bug fix to drawishness calculator

```
Score of Altair142 vs Altair141: 1432 - 1373 - 1695  [0.507] 4500
...      Altair142 playing White: 957 - 459 - 834  [0.611] 2250
...      Altair142 playing Black: 475 - 914 - 861  [0.402] 2250
...      White vs Black: 1871 - 934 - 1695  [0.604] 4500
Elo difference: 4.6 +/- 8.0, LOS: 86.7 %, DrawRatio: 37.7 %
```


### 1.4.3
More reductions to IIR

```
Score of Altair143 vs Altair142: 1796 - 1717 - 2147  [0.507] 5660
...      Altair143 playing White: 1152 - 605 - 1072  [0.597] 2829
...      Altair143 playing Black: 644 - 1112 - 1075  [0.417] 2831
...      White vs Black: 2264 - 1249 - 2147  [0.590] 5660
Elo difference: 4.8 +/- 7.1, LOS: 90.9 %, DrawRatio: 37.9 %

info multipv 1 depth 1 seldepth 1 score cp 58 time 1 nodes 29 nps 29000 pv e2e4 
info multipv 1 depth 2 seldepth 2 score cp 19 time 1 nodes 107 nps 107000 pv e2e4 e7e5 
info multipv 1 depth 3 seldepth 3 score cp 46 time 1 nodes 248 nps 248000 pv e2e4 e7e5 d2d4 
info multipv 1 depth 4 seldepth 5 score cp 24 time 4 nodes 749 nps 187250 pv e2e4 e7e5 d2d4 b8c6 
info multipv 1 depth 5 seldepth 7 score cp 43 time 10 nodes 2520 nps 252000 pv e2e4 d7d5 e4d5 c7c6 d5c6 
info multipv 1 depth 6 seldepth 8 score cp 23 time 36 nodes 8065 nps 224027 pv e2e4 e7e5 g1f3 g8f6 d2d4 d7d5 
info multipv 1 depth 7 seldepth 9 score cp 47 time 39 nodes 10929 nps 280230 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 
info multipv 1 depth 8 seldepth 10 score cp 40 time 46 nodes 19093 nps 415065 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 d7d5 
info multipv 1 depth 9 seldepth 12 score cp 47 time 52 nodes 27028 nps 519769 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 d7d5 b1c3 
info multipv 1 depth 10 seldepth 12 score cp 42 time 60 nodes 40622 nps 677033 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8f6 
info multipv 1 depth 11 seldepth 14 score cp 34 time 90 nodes 85684 nps 952044 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 d7d5 c1g5 
info multipv 1 depth 12 seldepth 15 score cp 50 time 134 nodes 151675 nps 1131902 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 g1f3 e7e5 f1d3 c8e6 e1g1 g8f6 
info multipv 1 depth 13 seldepth 17 score cp 49 time 199 nodes 248056 nps 1246512 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 c6d4 d1d4 f8d6 f1e2 
info multipv 1 depth 14 seldepth 17 score cp 31 time 422 nodes 580433 nps 1375433 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 f1c4 f6e4 c4f7 e8f7 c3e4 d7d5 e4c5 e7e5 c5d3 
info multipv 1 depth 15 seldepth 22 score cp 34 time 652 nodes 923475 nps 1416372 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 d2d4 c5d4 f3d4 e7e5 d4c6 b7c6 f1c4 f8b4 c1g5 
info multipv 1 depth 16 seldepth 22 score cp 34 time 843 nodes 1206157 nps 1430791 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 d2d4 c5d4 f3d4 e7e5 d4c6 
info multipv 1 depth 17 seldepth 22 score cp 27 time 2415 nodes 3477051 nps 1439772 pv g1f3 d7d5 e2e3 g8f6 c2c4 e7e6 d2d4 c7c6 f1d3 d5c4 d3c4 f8d6 e1g1 e8g8 b1c3 b8d7 h2h3 
info multipv 1 depth 18 seldepth 24 score cp 36 time 4664 nodes 6791074 nps 1456062 pv d2d4 g8f6 c2c4 c7c5 d4d5 d7d6 b1c3 c8f5 g1f3 e7e5 c1g5 b8d7 e2e4 f5g6 g5f6 d7f6 f1d3 h7h6 
info multipv 1 depth 19 seldepth 24 score cp 32 time 5388 nodes 7852928 nps 1457484 pv d2d4 g8f6 c2c4 e7e6 g1f3 b8c6 e2e3 d7d5 b1c3 f8e7 a2a3 a7a5 f1d3 d5c4 d3c4 e8g8 e1g1 f6g4 c4d3 
info multipv 1 depth 20 seldepth 24 score cp 32 time 6236 nodes 9102940 nps 1459740 pv d2d4 g8f6 c2c4 e7e6 g1f3 b8c6 e2e3 d7d5 b1c3 f8e7 a2a3 a7a5 f1d3 d5c4 d3c4 e8g8 
info multipv 1 depth 21 seldepth 27 score cp 21 time 10225 nodes 14878500 nps 1455110 pv d2d4 g8f6 c2c4 e7e6 g1f3 d7d5 e2e3 f8e7 f1d3 d5c4 d3c4 e8g8 e1g1 c7c5 b1c3 c5d4 e3d4 b8c6 c1e3 f6g4 a1c1 
info multipv 1 depth 22 seldepth 27 score cp 21 time 11830 nodes 17201314 nps 1454041 pv d2d4 g8f6 c2c4 e7e6 g1f3 d7d5 e2e3 
info multipv 1 depth 23 seldepth 28 score cp 24 time 14930 nodes 21451244 nps 1436787 pv d2d4 g8f6 c2c4 e7e6 g1f3 d7d5 e2e3 f8e7 f1d3 d5c4 d3c4 e8g8 e1g1 c7c5 d4c5 b8c6 b1c3 e7c5 c1d2 c6a5 c4b5 
info multipv 1 depth 24 seldepth 29 score cp 24 time 19603 nodes 28273320 nps 1442295 pv d2d4 g8f6 g1f3 d7d5 c2c4 e7e6 e2e3 f8e7 f1d3 
info multipv 1 depth 24 seldepth 36 score cp 24 time 45000 nodes 64774144 nps 1439425 pv d2d4 g8f6 g1f3 d7d5 c2c4 e7e6 e2e3 f8e7 f1d3 
bestmove d2d4
```


### 1.4.4
Fixing illegal moves where castling rights weren't updated correctly.

```
info multipv 1 depth 1 seldepth 1 score cp 58 time 1 nodes 29 nps 29000 pv e2e4 
info multipv 1 depth 2 seldepth 2 score cp 19 time 1 nodes 107 nps 107000 pv e2e4 e7e5 
info multipv 1 depth 3 seldepth 3 score cp 46 time 1 nodes 248 nps 248000 pv e2e4 e7e5 d2d4 
info multipv 1 depth 4 seldepth 5 score cp 24 time 1 nodes 749 nps 749000 pv e2e4 e7e5 d2d4 b8c6 
info multipv 1 depth 5 seldepth 7 score cp 43 time 4 nodes 2520 nps 630000 pv e2e4 d7d5 e4d5 c7c6 d5c6 
info multipv 1 depth 6 seldepth 8 score cp 23 time 10 nodes 8065 nps 806500 pv e2e4 e7e5 g1f3 g8f6 d2d4 d7d5 
info multipv 1 depth 7 seldepth 9 score cp 47 time 12 nodes 10929 nps 910750 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 
info multipv 1 depth 8 seldepth 10 score cp 40 time 18 nodes 19093 nps 1060722 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 d7d5 
info multipv 1 depth 9 seldepth 12 score cp 47 time 23 nodes 27028 nps 1175130 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 d7d5 b1c3 
info multipv 1 depth 10 seldepth 12 score cp 42 time 32 nodes 40622 nps 1269437 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8f6 
info multipv 1 depth 11 seldepth 14 score cp 34 time 62 nodes 85684 nps 1382000 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 d7d5 c1g5 
info multipv 1 depth 12 seldepth 15 score cp 50 time 106 nodes 151686 nps 1431000 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 g1f3 e7e5 f1d3 c8e6 e1g1 g8f6 
info multipv 1 depth 13 seldepth 17 score cp 49 time 172 nodes 250093 nps 1454029 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 c6d4 d1d4 f8d6 f1e2 
info multipv 1 depth 14 seldepth 18 score cp 44 time 468 nodes 685288 nps 1464290 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 f1b5 c6d4 e4e5 d4b5 c3b5 a7a6 b5c3 f6g4 
info multipv 1 depth 15 seldepth 18 score cp 41 time 581 nodes 855326 nps 1472161 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 f1b5 e7e6 e1g1 f8e7 d2d4 e8g8 c1e3 f6g4 e3f4 
info multipv 1 depth 16 seldepth 23 score cp 25 time 1425 nodes 2082658 nps 1461514 pv g1f3 d7d5 d2d4 g8f6 e2e3 e7e6 c2c4 b8c6 c4d5 f8b4 c1d2 e6d5 f1b5 b4d6 b5c6 b7c6 f3e5 d6e5 
info multipv 1 depth 17 seldepth 23 score cp 27 time 2310 nodes 3386314 nps 1465936 pv g1f3 g8f6 d2d4 e7e6 c2c4 f8e7 b1c3 d7d5 c4d5 e6d5 e2e3 e8g8 f1d3 b8c6 e1g1 
info multipv 1 depth 18 seldepth 23 score cp 27 time 2609 nodes 3832104 nps 1468801 pv g1f3 g8f6 d2d4 e7e6 c2c4 f8e7 b1c3 d7d5 c4d5 e6d5 e2e3 e8g8 f1d3 b8c6 e1g1 c6b4 d3b1 c7c6 
info multipv 1 depth 19 seldepth 23 score cp 24 time 3609 nodes 5306783 nps 1470430 pv g1f3 g8f6 d2d4 e7e6 c2c4 b8c6 e2e3 d7d5 b1c3 f8e7 f1e2 e8g8 e1g1 h7h6 c1d2 c8d7 a2a3 a7a6 c4d5 
info multipv 1 depth 20 seldepth 23 score cp 24 time 4068 nodes 5985199 nps 1471287 pv g1f3 g8f6 d2d4 
info multipv 1 depth 21 seldepth 24 score cp 24 time 5131 nodes 7497268 nps 1461170 pv g1f3 g8f6 d2d4 e7e6 c2c4 b8c6 b1c3 d7d5 e2e3 
info multipv 1 depth 22 seldepth 28 score cp 27 time 9123 nodes 13274200 nps 1455025 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 e2e3 f8d6 c4d5 e6d5 f1d3 e8g8 e1g1 c7c6 b1c3 h7h6 a2a3 f8e8 c1d2 a7a5 h2h3 g8h8 
info multipv 1 depth 23 seldepth 28 score cp 27 time 11528 nodes 16634327 nps 1442949 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 e2e3 
info multipv 1 depth 24 seldepth 28 score cp 27 time 13351 nodes 19295431 nps 1445242 pv g1f3 g8f6 
info multipv 1 depth 25 seldepth 32 score cp 29 time 40350 nodes 58209302 nps 1442609 pv g1f3 d7d5 e2e3 g8f6 c2c4 e7e6 d2d4 f8e7 
info multipv 1 depth 25 seldepth 32 score cp 29 time 45000 nodes 64796701 nps 1439926 pv g1f3 d7d5 e2e3 g8f6 c2c4 e7e6 d2d4 f8e7 
bestmove g1f3

Score of Altair144 vs Altair143: 3689 - 3742 - 4529  [0.498] 11960
...      Altair144 playing White: 2430 - 1285 - 2266  [0.596] 5981
...      Altair144 playing Black: 1259 - 2457 - 2263  [0.400] 5979
...      White vs Black: 4887 - 2544 - 4529  [0.598] 11960
Elo difference: -1.5 +/- 4.9, LOS: 26.9 %, DrawRatio: 37.9 %
SPRT: llr 0.766 (26.0%), lbound -2.94, ubound 2.94
```

### 1.4.5
NMP adjusted by static_eval

```
info multipv 1 depth 1 seldepth 1 score cp 58 time 1 nodes 29 nps 29000 pv e2e4 
info multipv 1 depth 2 seldepth 2 score cp 19 time 1 nodes 107 nps 107000 pv e2e4 e7e5 
info multipv 1 depth 3 seldepth 3 score cp 46 time 1 nodes 221 nps 221000 pv e2e4 e7e5 d2d4 
info multipv 1 depth 4 seldepth 5 score cp 24 time 1 nodes 708 nps 708000 pv e2e4 e7e5 d2d4 b8c6 
info multipv 1 depth 5 seldepth 7 score cp 43 time 5 nodes 2186 nps 437200 pv e2e4 d7d5 e4d5 c7c6 d5c6 
info multipv 1 depth 6 seldepth 8 score cp 43 time 9 nodes 4162 nps 462444 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 
info multipv 1 depth 7 seldepth 9 score cp 40 time 21 nodes 10610 nps 505238 pv e2e4 e7e5 b1c3 b8c6 g1f3 
info multipv 1 depth 8 seldepth 9 score cp 33 time 29 nodes 15024 nps 518068 pv e2e4 e7e5 b1c3 b8c6 g1f3 f8c5 f1b5 d7d6 
info multipv 1 depth 9 seldepth 12 score cp 50 time 38 nodes 23889 nps 628657 pv e2e4 e7e5 b1c3 b8c6 g1f3 d7d6 d2d4 c8g4 d4d5 
info multipv 1 depth 10 seldepth 12 score cp 41 time 46 nodes 36354 nps 790304 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 d7d5 
info multipv 1 depth 11 seldepth 14 score cp 34 time 61 nodes 58471 nps 958540 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 d7d5 c1g5 
info multipv 1 depth 12 seldepth 15 score cp 23 time 123 nodes 135168 nps 1098926 pv e2e4 d7d5 e4d5 c7c6 d2d4 c6d5 g1f3 b8c6 f1e2 g8f6 
info multipv 1 depth 13 seldepth 16 score cp 40 time 162 nodes 189552 nps 1170074 pv e2e4 d7d5 e4d5 c7c6 d2d4 c6d5 g1f3 b8c6 f1e2 g8f6 e1g1 c8f5 b1c3 
info multipv 1 depth 14 seldepth 18 score cp 44 time 325 nodes 422170 nps 1298984 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1b5 c6d4 e4e5 d4b5 c3b5 a7a6 b5c3 f6g4 
info multipv 1 depth 15 seldepth 18 score cp 48 time 442 nodes 562151 nps 1271834 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1b5 a7a6 b5c6 d7c6 e4e5 f6d5 e1g1 c8g4 
info multipv 1 depth 16 seldepth 19 score cp 43 time 713 nodes 898478 nps 1260137 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1b5 e7e5 b5c6 d7c6 f3e5 f8d6 d2d4 e8g8 e1g1 
info multipv 1 depth 17 seldepth 23 score cp 43 time 1089 nodes 1254911 nps 1152351 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 f1b5 e7e5 b5c6 d7c6 f3e5 f8d6 d2d4 e8g8 e1g1 c5d4 d1d4 
info multipv 1 depth 18 seldepth 23 score cp 39 time 1748 nodes 2049364 nps 1172405 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e5 e1g1 g8f6 b5c6 d7c6 f3e5 f8d6 e5f3 d6b8 d2d3 e8g8 c1e3 b7b6 
info multipv 1 depth 19 seldepth 23 score cp 39 time 2185 nodes 2671160 nps 1222498 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e5 e1g1 g8f6 b5c6 
info multipv 1 depth 20 seldepth 24 score cp 39 time 2853 nodes 3491334 nps 1223741 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e5 e1g1 
info multipv 1 depth 21 seldepth 24 score cp 39 time 3401 nodes 4258887 nps 1252245 pv e2e4 c7c5 g1f3 
info multipv 1 depth 22 seldepth 26 score cp 39 time 5125 nodes 6598965 nps 1287602 pv e2e4 c7c5 g1f3 b8c6 f1b5 
info multipv 1 depth 23 seldepth 31 score cp 25 time 11629 nodes 16145068 nps 1388345 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e5 e1g1 g8f6 b5c6 d7c6 f3e5 f8d6 e5f3 c8g4 b1c3 e8g8 h2h3 g4f3 d1f3 d6e5 
info multipv 1 depth 24 seldepth 31 score cp 30 time 15735 nodes 22159300 nps 1408280 pv e2e4 e7e6 d2d4 d7d5 e4d5 e6d5 g1f3 g8f6 b1c3 c7c6 f1d3 f8d6 e1g1 e8g8 f1e1 h7h6 h2h3 f8e8 f3e5 
info multipv 1 depth 25 seldepth 34 score cp 28 time 33321 nodes 48080757 nps 1442956 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 d2d4 f8b4 g1f3 b8c6 f1d3 g8f6 e1g1 e8g8 a2a3 b4c3 b2c3 f8e8 f1e1 f6e4 d3e4 e8e4 c1g5 
info multipv 1 depth 25 seldepth 34 score cp 28 time 45000 nodes 65173506 nps 1448300 pv e2e4 e7e6 b1c3 d7d5 e4d5 e6d5 d2d4 f8b4 g1f3 b8c6 f1d3 g8f6 e1g1 e8g8 a2a3 b4c3 b2c3 f8e8 f1e1 f6e4 d3e4 e8e4 c1g5 
bestmove e2e4

Score of Altair145 vs Altair144: 1923 - 1773 - 2242  [0.513] 5938
...      Altair145 playing White: 1279 - 625 - 1065  [0.610] 2969
...      Altair145 playing Black: 644 - 1148 - 1177  [0.415] 2969
...      White vs Black: 2427 - 1269 - 2242  [0.598] 5938
Elo difference: 8.8 +/- 7.0, LOS: 99.3 %, DrawRatio: 37.8 %
SPRT: llr 2.99 (101.4%), lbound -2.94, ubound 2.94 - H1 was accepted
```


### 1.4.6
History Pruning

```

info multipv 1 depth 1 seldepth 1 score cp 58 time 1 nodes 29 nps 29000 pv e2e4 
info multipv 1 depth 2 seldepth 2 score cp 19 time 1 nodes 107 nps 107000 pv e2e4 e7e5 
info multipv 1 depth 3 seldepth 3 score cp 46 time 1 nodes 221 nps 221000 pv e2e4 e7e5 d2d4 
info multipv 1 depth 4 seldepth 5 score cp 24 time 4 nodes 708 nps 177000 pv e2e4 e7e5 d2d4 b8c6 
info multipv 1 depth 5 seldepth 7 score cp 43 time 13 nodes 2200 nps 169230 pv e2e4 d7d5 e4d5 c7c6 d5c6 
info multipv 1 depth 6 seldepth 8 score cp 43 time 21 nodes 4148 nps 197523 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 
info multipv 1 depth 7 seldepth 9 score cp 32 time 46 nodes 8504 nps 184869 pv e2e4 d7d5 e4d5 d8d5 d2d3 d5e5 c1e3 g8f6 
info multipv 1 depth 8 seldepth 11 score cp 22 time 71 nodes 18147 nps 255591 pv e2e4 d7d5 e4d5 g8f6 b1c3 f6d5 d2d4 b8c6 
info multipv 1 depth 9 seldepth 11 score cp 37 time 78 nodes 25416 nps 325846 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 b8c6 b1c3 
info multipv 1 depth 10 seldepth 13 score cp 26 time 106 nodes 58700 nps 553773 pv e2e4 d7d5 e4e5 c7c5 g1f3 c8g4 f1b5 b8c6 e1g1 e7e6 b1c3 
info multipv 1 depth 11 seldepth 14 score cp 38 time 128 nodes 92505 nps 722695 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 b1c3 e7e5 g1f3 g8f6 f1d3 
info multipv 1 depth 12 seldepth 16 score cp 41 time 159 nodes 139688 nps 878540 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 d2d4 b8c6 f1b5 c8g4 e1g1 g8f6 
info multipv 1 depth 13 seldepth 17 score cp 24 time 240 nodes 264914 nps 1103808 pv e2e4 e7e5 g1f3 b8c6 f1b5 c6d4 f3d4 e5d4 e1g1 c7c6 b5e2 f8d6 c2c3 
info multipv 1 depth 14 seldepth 19 score cp 36 time 380 nodes 470474 nps 1238089 pv e2e4 e7e5 g1f3 g8f6 d2d4 f6e4 f1d3 d7d5 f3e5 b8c6 e5c6 b7c6 e1g1 a8b8 
info multipv 1 depth 15 seldepth 20 score cp 25 time 632 nodes 847916 nps 1341639 pv e2e4 c7c5 b1c3 b8c6 g1f3 g8f6 d2d3 e7e5 f1e2 f8d6 e1g1 e8g8 c1g5 c6d4 f3d4 
info multipv 1 depth 16 seldepth 20 score cp 21 time 921 nodes 1291363 nps 1402131 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 b7c6 c1g5 f8d6 b1d2 a8b8 d2c4 e8g8 
info multipv 1 depth 17 seldepth 23 score cp 34 time 1614 nodes 2321330 nps 1438246 pv d2d4 d7d5 g1f3 g8f6 e2e3 e7e6 c2c4 f8e7 c4d5 e6d5 b1c3 e8g8 f1d3 h7h6 e1g1 b8c6 c1d2 
info multipv 1 depth 18 seldepth 23 score cp 34 time 2040 nodes 2958515 nps 1450252 pv d2d4 d7d5 g1f3 g8f6 e2e3 c8g4 c2c4 e7e6 c4d5 e6d5 f1d3 b8c6 b1c3 
info multipv 1 depth 19 seldepth 24 score cp 34 time 2850 nodes 4172338 nps 1463978 pv d2d4 d7d5 g1f3 g8f6 e2e3 c8g4 
info multipv 1 depth 20 seldepth 26 score cp 34 time 4183 nodes 6152947 nps 1470941 pv d2d4 d7d5 g1f3 g8f6 
info multipv 1 depth 21 seldepth 27 score cp 19 time 8580 nodes 12677758 nps 1477594 pv d2d4 d7d5 g1f3 g8f6 c2c4 e7e6 b1c3 f8e7 c4d5 e6d5 e2e3 e8g8 f1d3 c7c5 d4c5 e7c5 e1g1 b8c6 a2a3 c8g4 c1d2 
info multipv 1 depth 22 seldepth 28 score cp 19 time 10102 nodes 14923170 nps 1477249 pv d2d4 d7d5 
info multipv 1 depth 23 seldepth 28 score cp 19 time 13187 nodes 19475844 nps 1476897 pv d2d4 d7d5 g1f3 g8f6 c2c4 e7e6 b1c3 f8e7 e2e3 e8g8 c4d5 e6d5 f1d3 
info multipv 1 depth 24 seldepth 32 score cp 26 time 40097 nodes 59202088 nps 1476471 pv d2d4 d7d5 g1f3 g8f6 c2c4 e7e6 e2e3 f8d6 b1c3 e8g8 f1d3 d5c4 d3c4 c7c5 e1g1 c5d4 c3b5 b8c6 b5d6 d8d6 e3d4 h7h6 c1d2 c6d4 
info multipv 1 depth 24 seldepth 32 score cp 26 time 45000 nodes 66502683 nps 1477837 pv d2d4 d7d5 g1f3 g8f6 c2c4 e7e6 e2e3 f8d6 b1c3 e8g8 f1d3 d5c4 d3c4 c7c5 e1g1 c5d4 c3b5 b8c6 b5d6 d8d6 e3d4 h7h6 c1d2 c6d4 
bestmove d2d4

Score of Altair146 vs Altair145: 1345 - 1222 - 1567  [0.515] 4134
...      Altair146 playing White: 884 - 433 - 750  [0.609] 2067
...      Altair146 playing Black: 461 - 789 - 817  [0.421] 2067
...      White vs Black: 1673 - 894 - 1567  [0.594] 4134
Elo difference: 10.3 +/- 8.3, LOS: 99.2 %, DrawRatio: 37.9 %
SPRT: llr 2.95 (100.1%), lbound -2.94, ubound 2.94 - H1 was accepted

Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.4.6                    51      30     405     188     129      88    232.0   57.3%   21.7%   55.2%   59.4% 
   1 zevra_popcnt                  -35      42     202      66      86      50     91.0   45.0%   24.8%   43.6%   46.5% 
   2 wyldchess1.51_popcnt          -68      44     203      63     102      38     82.0   40.4%   18.7%   37.7%   43.1% 

409 of 4000 games finished.
```


### 1.4.7
Idea of a min-max time split advised to me by Gedas and Archi

```
4 + 0.04
Score of Altair147 vs Altair146: 115 - 51 - 105  [0.618] 271
...      Altair147 playing White: 80 - 14 - 42  [0.743] 136
...      Altair147 playing Black: 35 - 37 - 63  [0.493] 135
...      White vs Black: 117 - 49 - 105  [0.625] 271
Elo difference: 83.6 +/- 32.8, LOS: 100.0 %, DrawRatio: 38.7 %
SPRT: llr 2.96 (100.5%), lbound -2.94, ubound 2.94 - H1 was accepted

10 + 0.01
Score of Altair147 vs Altair146: 174 - 110 - 221  [0.563] 505
...      Altair147 playing White: 122 - 31 - 100  [0.680] 253
...      Altair147 playing Black: 52 - 79 - 121  [0.446] 252
...      White vs Black: 201 - 83 - 221  [0.617] 505
Elo difference: 44.3 +/- 22.8, LOS: 100.0 %, DrawRatio: 43.8 %
SPRT: llr 2.95 (100.3%), lbound -2.94, ubound 2.94 - H1 was accepted
```


### 1.4.8
Protected Passed Pawn Eval

```
info multipv 1 depth 1 seldepth 1 score cp 55 time 1 nodes 28 nps 28000 pv e2e4 
info multipv 1 depth 2 seldepth 2 score cp 16 time 1 nodes 116 nps 116000 pv e2e4 e7e5 
info multipv 1 depth 3 seldepth 3 score cp 43 time 1 nodes 230 nps 230000 pv e2e4 e7e5 d2d4 
info multipv 1 depth 4 seldepth 5 score cp 22 time 5 nodes 1029 nps 205800 pv g1f3 b8c6 d2d4 d7d5 
info multipv 1 depth 5 seldepth 7 score cp 34 time 9 nodes 2104 nps 233777 pv g1f3 d7d5 d2d4 g8f6 b1c3 
info multipv 1 depth 6 seldepth 8 score cp 15 time 30 nodes 4496 nps 149866 pv g1f3 d7d5 d2d4 g8f6 b1c3 b8c6 
info multipv 1 depth 7 seldepth 9 score cp 31 time 40 nodes 9112 nps 227800 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 
info multipv 1 depth 8 seldepth 10 score cp 35 time 46 nodes 13193 nps 286804 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 c2c4 d5b4 
info multipv 1 depth 9 seldepth 12 score cp 41 time 65 nodes 32553 nps 500815 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 b1c3 e7e5 g1f3 
info multipv 1 depth 10 seldepth 12 score cp 20 time 82 nodes 54744 nps 667609 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 b1c3 e7e5 g1f3 g8f6 
info multipv 1 depth 11 seldepth 15 score cp 36 time 95 nodes 75478 nps 794505 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 b1c3 e7e5 g1f3 g8f6 f1d3 
info multipv 1 depth 12 seldepth 16 score cp 40 time 180 nodes 202239 nps 1123550 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 c6d4 d1d4 f8d6 
info multipv 1 depth 13 seldepth 17 score cp 43 time 215 nodes 257971 nps 1199865 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 d2d4 e5d4 f3d4 c6d4 d1d4 f8d6 c1g5 
info multipv 1 depth 14 seldepth 19 score cp 38 time 371 nodes 490950 nps 1323315 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 d7c6 d1d8 e8d8 c1g5 h7h6 g5f6 g7f6 
info multipv 1 depth 15 seldepth 19 score cp 23 time 510 nodes 701648 nps 1375780 pv e2e4 e7e5 g1f3 b8c6 f1b5 g8f6 d2d3 f8c5 b5c6 d7c6 f3e5 e8g8 c1e3 c5e3 f2e3 
info multipv 1 depth 16 seldepth 21 score cp 18 time 967 nodes 1398384 nps 1446105 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 b7c6 e4e5 d8e7 d1e2 f6d5 b1c3 d5c3 
info multipv 1 depth 17 seldepth 22 score cp 18 time 1172 nodes 1705370 nps 1455093 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 b7c6 e4e5 d8e7 d1e2 f6d5 b1c3 d5c3 b2c3 
info multipv 1 depth 18 seldepth 24 score cp 20 time 2041 nodes 3016529 nps 1477966 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 c2c4 b8c6 f1d3 f8e7 c1d2 e8g8 e1g1 c6b4 d2b4 e7b4 b1c3 d5c4 
info multipv 1 depth 19 seldepth 25 score cp 17 time 2713 nodes 4024513 nps 1483417 pv d2d4 d7d5 e2e3 g8f6 g1f3 e7e6 c2c4 b8c6 b1c3 f8e7 f1e2 e8g8 e1g1 a7a5 c1d2 f6g4 a1c1 f8e8 c4d5 
info multipv 1 depth 20 seldepth 27 score cp 26 time 4878 nodes 7297174 nps 1495935 pv g1f3 d7d5 d2d4 c7c5 d4c5 e7e6 e2e4 f8c5 e4d5 e6d5 f1b5 b8c6 e1g1 g8e7 f1e1 d8b6 b5c6 b7c6 c1e3 e8g8 e3c5 
info multipv 1 depth 21 seldepth 27 score cp 26 time 5894 nodes 8837938 nps 1499480 pv g1f3 d7d5 d2d4 c7c5 d4c5 e7e6 e2e4 f8c5 e4d5 e6d5 
info multipv 1 depth 22 seldepth 27 score cp 26 time 7011 nodes 10523969 nps 1501065 pv g1f3 d7d5 d2d4 
info multipv 1 depth 23 seldepth 27 score cp 26 time 8478 nodes 12721022 nps 1500474 pv g1f3 d7d5 d2d4 
info multipv 1 depth 24 seldepth 33 score cp 28 time 18342 nodes 27380451 nps 1492773 pv g1f3 d7d5 d2d4 c7c5 e2e3 e7e6 c2c4 g8f6 c4d5 e6d5 f1b5 c8d7 b1c3 c5d4 b5d7 b8d7 d1d4 f8c5 d4d3 e8g8 e1g1 a8c8 c3d5 f6d5 
info multipv 1 depth 25 seldepth 33 score cp 27 time 20513 nodes 30598416 nps 1491659 pv g1f3 d7d5 e2e3 g8f6 d2d4 e7e6 c2c4 b8c6 f1d3 f8e7 c1d2 e8g8 e1g1 h7h6 b1c3 c8d7 c4d5 e6d5 a2a3 
info multipv 1 depth 25 seldepth 33 score cp 27 time 45000 nodes 67280932 nps 1495131 pv g1f3 d7d5 e2e3 g8f6 d2d4 e7e6 c2c4 b8c6 f1d3 f8e7 c1d2 e8g8 e1g1 h7h6 b1c3 c8d7 c4d5 e6d5 a2a3 
bestmove g1f3

Score of Altair148 vs Altair147: 1386 - 1261 - 1838  [0.514] 4485
...      Altair148 playing White: 924 - 412 - 908  [0.614] 2244
...      Altair148 playing Black: 462 - 849 - 930  [0.414] 2241
...      White vs Black: 1773 - 874 - 1838  [0.600] 4485
Elo difference: 9.7 +/- 7.8, LOS: 99.2 %, DrawRatio: 41.0 %
SPRT: llr 2.95 (100.2%), lbound -2.94, ubound 2.94 - H1 was accepted
```


### 1.4.9
Phalanx Pawn Eval

```
info multipv 1 depth 1 seldepth 1 score cp 65 time 1 nodes 30 nps 30000 pv e2e4 
info multipv 1 depth 2 seldepth 2 score cp 19 time 1 nodes 131 nps 131000 pv d2d4 d7d5 
info multipv 1 depth 3 seldepth 3 score cp 49 time 1 nodes 242 nps 242000 pv d2d4 d7d5 g1f3 
info multipv 1 depth 4 seldepth 6 score cp 19 time 1 nodes 694 nps 694000 pv d2d4 d7d5 g1f3 g8f6 
info multipv 1 depth 5 seldepth 7 score cp 35 time 3 nodes 1500 nps 500000 pv d2d4 d7d5 g1f3 g8f6 b1c3 
info multipv 1 depth 6 seldepth 8 score cp 19 time 6 nodes 3542 nps 590333 pv d2d4 d7d5 g1f3 g8f6 b1c3 b8c6 
info multipv 1 depth 7 seldepth 9 score cp 35 time 14 nodes 9111 nps 650785 pv e2e4 d7d5 e4d5 g8f6 d2d4 f6d5 g1f3 
info multipv 1 depth 8 seldepth 10 score cp 37 time 19 nodes 12765 nps 671842 pv e2e4 d7d5 e4d5 g8f6 d2d4 c7c6 d5c6 b8c6 
info multipv 1 depth 9 seldepth 12 score cp 46 time 36 nodes 28514 nps 792055 pv e2e4 e7e6 d2d4 d7d5 b1c3 b8c6 e4e5 g8e7 c1g5 
info multipv 1 depth 10 seldepth 13 score cp 35 time 66 nodes 65575 nps 993560 pv e2e4 e7e5 b1c3 b8c6 g1f3 g8f6 f1b5 f8d6 d2d4 e5d4 
info multipv 1 depth 11 seldepth 13 score cp 33 time 91 nodes 100539 nps 1104824 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 d7c6 d1d8 e8d8 
info multipv 1 depth 12 seldepth 15 score cp 38 time 118 nodes 142199 nps 1205076 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 b1c3 c6d4 d1d4 f8d6 
info multipv 1 depth 13 seldepth 18 score cp 20 time 285 nodes 383844 nps 1346821 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 f1b5 f8b4 e1g1 e8g8 d2d3 d7d6 c1e3 
info multipv 1 depth 14 seldepth 18 score cp 26 time 336 nodes 459083 nps 1366318 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 f1b5 f8b4 e1g1 e8g8 d2d3 d7d6 a2a3 b4c5 
info multipv 1 depth 15 seldepth 19 score cp 40 time 486 nodes 684215 nps 1407849 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 d2d4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 
info multipv 1 depth 16 seldepth 20 score cp 42 time 822 nodes 1177040 nps 1431922 pv e2e4 e7e5 g1f3 b8c6 f1c4 g8f6 d2d3 d7d5 e4d5 f6d5 e1g1 f8e7 f1e1 c8g4 b1c3 d5c3 
info multipv 1 depth 17 seldepth 21 score cp 20 time 1227 nodes 1764430 nps 1438003 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 b7c6 e4e5 d8e7 d1e2 f6d5 b1c3 d5c3 b2c3 
info multipv 1 depth 18 seldepth 24 score cp 34 time 1545 nodes 2234675 nps 1446391 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 b7c6 e4e5 d8e7 d1e2 f6d5 c1d2 c8b7 b1c3 e8c8 
info multipv 1 depth 19 seldepth 24 score cp 34 time 2338 nodes 3364840 nps 1439195 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 
info multipv 1 depth 20 seldepth 26 score cp 34 time 2782 nodes 3980076 nps 1430652 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 
info multipv 1 depth 21 seldepth 26 score cp 33 time 3601 nodes 5179514 nps 1438354 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 b7c6 e4e5 d8e7 d1e2 f6d5 c1d2 d5b4 e2e4 d7d5 
info multipv 1 depth 22 seldepth 26 score cp 33 time 4347 nodes 6273084 nps 1443083 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 
info multipv 1 depth 23 seldepth 27 score cp 33 time 5524 nodes 7978870 nps 1444400 pv e2e4 e7e5 g1f3 
info multipv 1 depth 24 seldepth 27 score cp 33 time 6600 nodes 9534290 nps 1444589 pv e2e4 e7e5 g1f3 b8c6 
info multipv 1 depth 25 seldepth 31 score cp 36 time 16188 nodes 23588224 nps 1457142 pv e2e4 e7e5 g1f3 b8c6 b1c3 g8f6 f1c4 f6e4 c3e4 d7d5 c4d3 d5e4 d3e4 f8d6 e1g1 e8g8 c2c3 c8g4 f1e1 
info multipv 1 depth 26 seldepth 34 score cp 31 time 34509 nodes 50370384 nps 1459630 pv d2d4 g8f6 c2c4 e7e6 b1c3 f8b4 g1f3 e8g8 e2e3 d7d5 c4d5 e6d5 f1d3 c7c5 d4c5 b8d7 e1g1 d7c5 d3c2 b4c3 b2c3 c5e4 c1b2 c8g4 
bestmove d2d4

Score of Altair149 vs Altair148: 290 - 216 - 331  [0.544] 837
...      Altair149 playing White: 194 - 72 - 153  [0.646] 419
...      Altair149 playing Black: 96 - 144 - 178  [0.443] 418
...      White vs Black: 338 - 168 - 331  [0.602] 837
Elo difference: 30.8 +/- 18.3, LOS: 99.9 %, DrawRatio: 39.5 %
SPRT: llr 2.97 (100.8%), lbound -2.94, ubound 2.94 - H1 was accepted

Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.4.9                     0      21     856     337     337     182    428.0   50.0%   21.3%   51.2%   48.8% 
   1 glaurung-w64                  133      44     214     125      47      42    146.0   68.2%   19.6%   69.6%   66.8% 
   2 4ku-2.0                        29      40     214      88      70      56    116.0   54.2%   26.2%   55.6%   52.8% 
   3 zevra_popcnt                  -54      42     214      69     102      43     90.5   42.3%   20.1%   42.5%   42.1% 
   4 wyldchess1.51_popcnt         -105      44     214      55     118      41     75.5   35.3%   19.2%   36.9%   33.6% 

859 of 8000 games finished.
```


### 1.5.0
Pawn Support and Threat Bonuses

```
info multipv 1 depth 1 seldepth 1 score cp 51 time 1 nodes 25 nps 25000 pv e2e3 
info multipv 1 depth 2 seldepth 2 score cp 18 time 1 nodes 88 nps 88000 pv e2e3 e7e6 
info multipv 1 depth 3 seldepth 3 score cp 30 time 1 nodes 201 nps 201000 pv e2e3 e7e6 b1c3 
info multipv 1 depth 4 seldepth 4 score cp 23 time 3 nodes 721 nps 240333 pv e2e3 e7e6 b1c3 b8c6 
info multipv 1 depth 5 seldepth 7 score cp 30 time 5 nodes 1638 nps 327600 pv e2e3 e7e6 b1c3 b8c6 g1f3 
info multipv 1 depth 6 seldepth 7 score cp 24 time 8 nodes 3118 nps 389750 pv e2e3 e7e6 b1c3 b8c6 g1f3 g8f6 
info multipv 1 depth 7 seldepth 8 score cp 33 time 14 nodes 9149 nps 653500 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 e2e3 
info multipv 1 depth 8 seldepth 10 score cp 24 time 28 nodes 27754 nps 991214 pv b1c3 d7d5 g1f3 b8c6 d2d4 g8f6 
info multipv 1 depth 9 seldepth 12 score cp 41 time 40 nodes 45328 nps 1133200 pv b1c3 g8f6 g1f3 b8c6 e2e3 e7e5 f1d3 d7d5 e1g1 
info multipv 1 depth 10 seldepth 13 score cp 28 time 59 nodes 72420 nps 1227457 pv b1c3 g8f6 g1f3 b8c6 d2d4 d7d5 c1f4 c8f5 c3b5 a8c8 
info multipv 1 depth 11 seldepth 14 score cp 46 time 126 nodes 167237 nps 1327277 pv e2e4 d7d5 e4d5 g8f6 g1f3 c7c6 d2d4 c6d5 f1d3 b8c6 e1g1 
info multipv 1 depth 12 seldepth 17 score cp 35 time 167 nodes 225348 nps 1349389 pv e2e4 d7d5 e4d5 g8f6 g1f3 e7e6 d5e6 c8e6 b1c3 f8d6 f3d4 e6g4 
info multipv 1 depth 13 seldepth 17 score cp 43 time 251 nodes 345492 nps 1376462 pv e2e4 d7d5 e4d5 g8f6 g1f3 e7e6 d5e6 c8e6 b1c3 f8d6 f3d4 e8g8 d4e6 
info multipv 1 depth 14 seldepth 18 score cp 41 time 446 nodes 623301 nps 1397535 pv e2e4 e7e6 b1c3 d7d5 d2d4 d5e4 c3e4 f8e7 c2c3 g8f6 f1d3 f6e4 d3e4 e8g8 
info multipv 1 depth 15 seldepth 20 score cp 23 time 1401 nodes 1952528 nps 1393667 pv d2d4 d7d5 e2e3 c7c5 g1f3 e7e6 f1e2 
info multipv 1 depth 16 seldepth 20 score cp 28 time 1729 nodes 2415954 nps 1397312 pv d2d4 d7d5 g1f3 g8f6 e2e3 e7e6 c2c4 c7c6 b1c3 f8b4 c4d5 e6d5 f1d3 e8g8 e1g1 c8g4 
info multipv 1 depth 17 seldepth 22 score cp 37 time 2623 nodes 3676366 nps 1401588 pv g1f3 g8f6 d2d4 e7e6 c2c4 f8b4 c1d2 c7c5 d2b4 c5b4 e2e3 e8g8 f1d3 d7d5 c4d5 f6d5 b1d2 b8c6 
info multipv 1 depth 18 seldepth 22 score cp 37 time 3031 nodes 4266094 nps 1407487 pv g1f3 g8f6 d2d4 e7e6 c2c4 f8b4 
info multipv 1 depth 19 seldepth 23 score cp 35 time 4234 nodes 5958512 nps 1407300 pv g1f3 d7d5 d2d4 g8f6 c2c4 d5c4 e2e3 c8e6 b1a3 b8c6 f1c4 e6d5 e1g1 e7e6 c4d5 d8d5 c1d2 
info multipv 1 depth 20 seldepth 24 score cp 35 time 5399 nodes 7585788 nps 1405035 pv g1f3 d7d5 d2d4 
info multipv 1 depth 21 seldepth 25 score cp 35 time 6747 nodes 9463208 nps 1402580 pv g1f3 d7d5 d2d4 g8f6 c2c4 
info multipv 1 depth 22 seldepth 31 score cp 33 time 17597 nodes 24420675 nps 1387774 pv g1f3 e7e6 e2e4 d7d5 e4d5 e6d5 d2d4 g8f6 f1d3 f8d6 
info multipv 1 depth 23 seldepth 31 score cp 26 time 22501 nodes 31171979 nps 1385359 pv g1f3 g8f6 c2c4 e7e6 d2d4 d7d5 b1c3 f8b4 c4d5 e6d5 e2e3 e8g8 f1d3 c7c5 e1g1 c5c4 d3c2 b8c6 a2a3 
info multipv 1 depth 24 seldepth 31 score cp 30 time 26559 nodes 36807759 nps 1385886 pv g1f3 g8f6 e2e3 e7e6 d2d4 c7c5 f1d3 d7d5 e1g1 c5d4 e3d4 f8d6 b1c3 a7a6 c3e2 b8c6 c2c3 e8g8 c1f4 h7h6 h2h3 
info multipv 1 depth 25 seldepth 32 score cp 29 time 38871 nodes 54076166 nps 1391169 pv g1f3 g8f6 e2e3 e7e6 d2d4 d7d5 c2c4 f8e7 c4d5 e6d5 b1c3 e8g8 f1d3 c7c5 d4c5 b8c6 e1g1 e7c5 a2a3 h7h6 b2b4 c5d6 b4b5 
bestmove g1f3

Score of Altair150 vs Altair149: 258 - 189 - 350  [0.543] 797
...      Altair150 playing White: 172 - 52 - 175  [0.650] 399
...      Altair150 playing Black: 86 - 137 - 175  [0.436] 398
...      White vs Black: 309 - 138 - 350  [0.607] 797
Elo difference: 30.2 +/- 18.1, LOS: 99.9 %, DrawRatio: 43.9 %
SPRT: llr 2.98 (101.1%), lbound -2.94, ubound 2.94 - H1 was accepted

Rank Name                          Elo     +/-   Games    Wins  Losses   Draws   Points   Score    Draw   White   Black 
   0 Altair1.5.0                   -17      11    3266    1276    1435     555   1553.5   47.6%   17.0%   47.8%   47.3% 
   1 glaurung-w64                  188      25     816     551     148     117    609.5   74.7%   14.3%   74.4%   75.0% 
   2 4ku-2.0                        69      21     816     396     236     184    488.0   59.8%   22.5%   57.4%   62.3% 
   3 wyldchess1.51_popcnt          -40      22     818     302     395     121    362.5   44.3%   14.8%   46.5%   42.2% 
   4 zevra_popcnt                 -139      23     816     186     497     133    252.5   30.9%   16.3%   32.6%   29.3% 

3266 of 20000 games finished.
```


### 1.5.1
LMR Bug Fix

```
info multipv 1 depth 1 seldepth 1 score cp 51 time 1 nodes 25 nps 25000 pv e2e3 
info multipv 1 depth 2 seldepth 2 score cp 18 time 1 nodes 88 nps 88000 pv e2e3 e7e6 
info multipv 1 depth 3 seldepth 3 score cp 30 time 1 nodes 201 nps 201000 pv e2e3 e7e6 b1c3 
info multipv 1 depth 4 seldepth 4 score cp 23 time 1 nodes 721 nps 721000 pv e2e3 e7e6 b1c3 b8c6 
info multipv 1 depth 5 seldepth 7 score cp 30 time 3 nodes 1638 nps 546000 pv e2e3 e7e6 b1c3 b8c6 g1f3 
info multipv 1 depth 6 seldepth 7 score cp 24 time 6 nodes 3116 nps 519333 pv e2e3 e7e6 b1c3 b8c6 g1f3 g8f6 
info multipv 1 depth 7 seldepth 8 score cp 33 time 16 nodes 9145 nps 571562 pv b1c3 b8c6 d2d4 d7d5 g1f3 g8f6 e2e3 
info multipv 1 depth 8 seldepth 10 score cp 24 time 43 nodes 27738 nps 645069 pv b1c3 d7d5 g1f3 b8c6 d2d4 g8f6 
info multipv 1 depth 9 seldepth 12 score cp 41 time 61 nodes 45303 nps 742672 pv b1c3 g8f6 g1f3 b8c6 e2e3 e7e5 f1d3 d7d5 e1g1 
info multipv 1 depth 10 seldepth 13 score cp 28 time 83 nodes 72380 nps 872048 pv b1c3 g8f6 g1f3 b8c6 d2d4 d7d5 c1f4 c8f5 c3b5 a8c8 
info multipv 1 depth 11 seldepth 14 score cp 45 time 147 nodes 162026 nps 1102217 pv e2e4 d7d5 e4d5 g8f6 g1f3 c7c6 d2d4 c6d5 f1d3 b8c6 e1g1 
info multipv 1 depth 12 seldepth 17 score cp 39 time 185 nodes 217406 nps 1175167 pv e2e4 d7d5 e4d5 g8f6 g1f3 e7e6 d2d4 e6d5 f1d3 f8d6 d1e2 d8e7 e2e7 e8e7 
info multipv 1 depth 13 seldepth 17 score cp 41 time 333 nodes 421833 nps 1266765 pv e2e4 e7e6 g1f3 c7c5 b1c3 b8c6 f1e2 f8d6 e1g1 g8f6 d2d4 c5d4 f3d4 
info multipv 1 depth 14 seldepth 18 score cp 38 time 476 nodes 629762 nps 1323029 pv e2e4 c7c5 b1c3 e7e6 g1f3 
info multipv 1 depth 15 seldepth 19 score cp 44 time 659 nodes 892548 nps 1354397 pv e2e4 c7c5 g1f3 b8c6 f1b5 g8f6 b1c3 c6d4 e4e5 d4b5 c3b5 f6e4 e1g1 a7a6 b5c3 
info multipv 1 depth 16 seldepth 20 score cp 31 time 1090 nodes 1505525 nps 1381215 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 f1c4 d7d6 e1g1 c6d4 f3d4 c5d4 c3d5 f6e4 d2d3 e4c5 
info multipv 1 depth 17 seldepth 22 score cp 42 time 1540 nodes 2143868 nps 1392122 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 f1b5 c6d4 b5a4 d8c7 d2d3 a7a6 a4b3 d7d6 c3d5 f6d5 f3d4 
info multipv 1 depth 18 seldepth 22 score cp 42 time 1892 nodes 2646472 nps 1398769 pv e2e4 c7c5 g1f3 b8c6 b1c3 g8f6 f1b5 c6d4 b5a4 d8c7 d2d3 a7a6 
info multipv 1 depth 19 seldepth 26 score cp 28 time 3955 nodes 5538910 nps 1400482 pv d2d4 g8f6 g1f3 d7d5 
info multipv 1 depth 20 seldepth 26 score cp 36 time 5099 nodes 7078303 nps 1388174 pv d2d4 g8f6 g1f3 d7d5 c2c4 d5c4 e2e3 c8e6 b1c3 c7c5 e3e4 c5d4 f3d4 b7b5 d4e6 d8d1 e1d1 
info multipv 1 depth 21 seldepth 26 score cp 31 time 6889 nodes 9569692 nps 1389126 pv d2d4 g8f6 g1f3 d7d5 c2c4 e7e6 e2e3 c7c5 c4d5 e6d5 b1c3 f8e7 f1d3 e8g8 e1g1 b8c6 d4c5 e7c5 a2a3 d5d4 c3e4 
info multipv 1 depth 22 seldepth 26 score cp 31 time 8177 nodes 11382734 nps 1392042 pv d2d4 g8f6 g1f3 e7e6 c2c4 d7d5 c4d5 e6d5 e2e3 c7c5 b1c3 
info multipv 1 depth 23 seldepth 26 score cp 31 time 9569 nodes 13339936 nps 1394078 pv d2d4 g8f6 
info multipv 1 depth 24 seldepth 30 score cp 31 time 12339 nodes 17253169 nps 1398263 pv d2d4 g8f6 
info multipv 1 depth 25 seldepth 32 score cp 33 time 24148 nodes 33723078 nps 1396516 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 c2c3 c5d4 c3d4 c8d7 g1f3 b8c6 b1c3 a8c8 f1d3 d8b6 d3c2 c6b4 e1g1 g8e7 
info multipv 1 depth 26 seldepth 32 score cp 33 time 28183 nodes 39293968 nps 1394243 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 c2c3 c5d4 c3d4 
info multipv 1 depth 27 seldepth 32 score cp 33 time 34278 nodes 47736243 nps 1392620 pv e2e4 e7e6 d2d4 
bestmove e2e4

Score of Altair151 vs Altair150: 1971 - 1894 - 2415  [0.506] 6280
...      Altair151 playing White: 1265 - 647 - 1228  [0.598] 3140
...      Altair151 playing Black: 706 - 1247 - 1187  [0.414] 3140
...      White vs Black: 2512 - 1353 - 2415  [0.592] 6280
Elo difference: 4.3 +/- 6.7, LOS: 89.2 %, DrawRatio: 38.5 %
```

### 1.5.2
Different History table scheme based on piece | to instead of color | from | to

```
Score of Altair152 vs Altair151: 208 - 163 - 209  [0.539] 580
...      Altair152 playing White: 131 - 48 - 112  [0.643] 291
...      Altair152 playing Black: 77 - 115 - 97  [0.434] 289
...      White vs Black: 246 - 125 - 209  [0.604] 580
Elo difference: 27.0 +/- 22.6, LOS: 99.0 %, DrawRatio: 36.0 %
```


### 1.5.3
No checks in Razoring, and lower margins.

```
Score of Altair153 vs Altair152: 321 - 286 - 393  [0.517] 1000
...      Altair153 playing White: 208 - 100 - 193  [0.608] 501
...      Altair153 playing Black: 113 - 186 - 200  [0.427] 499
...      White vs Black: 394 - 213 - 393  [0.591] 1000
Elo difference: 12.2 +/- 16.8, LOS: 92.2 %, DrawRatio: 39.3 %
SPRT: llr 0.66 (22.4%), lbound -2.94, ubound 2.94
```


### 1.5.4
Slightly more history bonus at the root of null move searches.

```
Score of Altair154 vs Altair153: 405 - 366 - 569  [0.515] 1340
...      Altair154 playing White: 272 - 128 - 270  [0.607] 670
...      Altair154 playing Black: 133 - 238 - 299  [0.422] 670
...      White vs Black: 510 - 261 - 569  [0.593] 1340
Elo difference: 10.1 +/- 14.1, LOS: 92.0 %, DrawRatio: 42.5 %
SPRT: llr 0.735 (25.0%), lbound -2.94, ubound 2.94
```


### 1.5.5
Different quiet LMP scheme. No more depth constraint, however there is a new formula and it is also
affected by the improving metric.

```
Score of Altair155 vs Altair154: 1771 - 1695 - 2394  [0.506] 5860
...      Altair155 playing White: 1156 - 569 - 1205  [0.600] 2930
...      Altair155 playing Black: 615 - 1126 - 1189  [0.413] 2930
...      White vs Black: 2282 - 1184 - 2394  [0.594] 5860
Elo difference: 4.5 +/- 6.8, LOS: 90.2 %, DrawRatio: 40.9 %
SPRT: llr 0.823 (28.0%), lbound -2.94, ubound 2.94
```


### 1.5.6 (2.0.0)
My idea for threats and supporting eval to be extended to all pieces


```
20+0.2
Score of Altair156 vs Altair155: 357 - 253 - 482  [0.548] 1092
...      Altair156 playing White: 263 - 65 - 218  [0.681] 546
...      Altair156 playing Black: 94 - 188 - 264  [0.414] 546
...      White vs Black: 451 - 159 - 482  [0.634] 1092
Elo difference: 33.2 +/- 15.4, LOS: 100.0 %, DrawRatio: 44.1 %
SPRT: llr 2.95 (100.2%), lbound -2.94, ubound 2.94 - H1 was accepted

5+0.05
Score of Altair156 vs Altair155: 165 - 145 - 220  [0.519] 530
...      Altair156 playing White: 128 - 40 - 98  [0.665] 266
...      Altair156 playing Black: 37 - 105 - 122  [0.371] 264
...      White vs Black: 233 - 77 - 220  [0.647] 530
Elo difference: 13.1 +/- 22.6, LOS: 87.2 %, DrawRatio: 41.5 %
```


### 2.0.1
Singular Extensions + Multi-cut pruning


```
Score of Altair201 vs Altair156: 664 - 606 - 900  [0.513] 2170
...      Altair201 playing White: 465 - 182 - 439  [0.630] 1086
...      Altair201 playing Black: 199 - 424 - 461  [0.396] 1084
...      White vs Black: 889 - 381 - 900  [0.617] 2170
Elo difference: 9.3 +/- 11.2, LOS: 94.8 %, DrawRatio: 41.5 %
SPRT: llr 1.32 (44.8%), lbound -2.94, ubound 2.94
```


### 2.0.2
Increasing reductions less if a move's history score is very bad. Decreasing reductions slightly more
if a move's history score is good.

```
Score of Altair202 vs Altair201: 512 - 486 - 842  [0.507] 1840
...      Altair202 playing White: 378 - 103 - 439  [0.649] 920
...      Altair202 playing Black: 134 - 383 - 403  [0.365] 920
...      White vs Black: 761 - 237 - 842  [0.642] 1840
Elo difference: 4.9 +/- 11.7, LOS: 79.5 %, DrawRatio: 45.8 %
```

### 2.0.3
RFP changes

```
info multipv 1 depth 1 seldepth 1 score cp 72 time 1 nodes 26 nps 26000 pv e2e3 
info multipv 1 depth 2 seldepth 2 score cp 27 time 1 nodes 122 nps 122000 pv e2e3 e7e6 
info multipv 1 depth 3 seldepth 3 score cp 52 time 1 nodes 228 nps 228000 pv e2e3 e7e6 b1c3 
info multipv 1 depth 4 seldepth 4 score cp 26 time 7 nodes 460 nps 65714 pv e2e3 e7e6 b1c3 b8c6 
info multipv 1 depth 5 seldepth 5 score cp 34 time 9 nodes 821 nps 91222 pv e2e3 e7e6 b1c3 b8c6 g1f3 
info multipv 1 depth 6 seldepth 6 score cp 28 time 12 nodes 1548 nps 129000 pv e2e3 e7e6 b1c3 b8c6 g1f3 g8f6 
info multipv 1 depth 7 seldepth 9 score cp 27 time 40 nodes 8698 nps 217450 pv e2e4 d7d5 e4d5 g8f6 b1c3 f6d5 g1f3 
info multipv 1 depth 8 seldepth 10 score cp 22 time 68 nodes 16882 nps 248264 pv e2e4 d7d5 e4d5 g8f6 b1c3 f6d5 d2d4 d5c3 
info multipv 1 depth 9 seldepth 11 score cp 49 time 85 nodes 29130 nps 342705 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 
info multipv 1 depth 10 seldepth 12 score cp 46 time 105 nodes 50463 nps 480600 pv e2e4 d7d5 e4d5 e7e6 d5e6 c8e6 d2d4 b8c6 c2c3 g8f6 
info multipv 1 depth 11 seldepth 14 score cp 51 time 121 nodes 70415 nps 581942 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 d2d4 b8c6 f1e2 g8f6 e1g1 
info multipv 1 depth 12 seldepth 15 score cp 47 time 148 nodes 106979 nps 722831 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 d2d4 g8f6 f1e2 b8c6 
info multipv 1 depth 13 seldepth 17 score cp 29 time 241 nodes 230646 nps 957037 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 
info multipv 1 depth 14 seldepth 17 score cp 45 time 295 nodes 305238 nps 1034705 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 e4e5 
info multipv 1 depth 15 seldepth 19 score cp 37 time 412 nodes 466247 nps 1131667 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 d2d4 e5d4 f3d4 f8b4 d4c6 d7c6 d1d8 e8d8 c1g5 h8e8 
info multipv 1 depth 16 seldepth 20 score cp 37 time 523 nodes 618445 nps 1182495 pv e2e4 e7e5 g1f3 g8f6 b1c3 b8c6 
info multipv 1 depth 17 seldepth 21 score cp 22 time 878 nodes 1099028 nps 1251740 pv e2e4 e7e5 g1f3 b8c6 f1b5 a7a6 b5c6 d7c6 e1g1 c8g4 d2d3 d8f6 b1c3 g4f3 d1f3 f6f3 g2f3 
info multipv 1 depth 18 seldepth 23 score cp 33 time 1199 nodes 1536831 nps 1281760 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8e7 b1c3 e7c6 d4e3 
info multipv 1 depth 19 seldepth 23 score cp 32 time 1553 nodes 2020915 nps 1301297 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8e7 b1c3 e7c6 d4e3 f8d6 f1c4 c6e5 c4e2 e8g8 f2f4 
info multipv 1 depth 20 seldepth 25 score cp 31 time 2095 nodes 2773330 nps 1323785 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 c6d4 d1d4 g8e7 b1c3 e7c6 d4e3 f8d6 f1c4 c6e5 c4e2 e8g8 e1g1 c7c6 
info multipv 1 depth 21 seldepth 27 score cp 29 time 5565 nodes 7449321 nps 1338602 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 c2c3 d4c3 b1c3 a7a6 f1d3 d7d6 e1g1 g8f6 c1f4 f8e7 e4e5 d6e5 f3e5 e8g8 e5c6 
info multipv 1 depth 22 seldepth 27 score cp 29 time 6597 nodes 8830321 nps 1338535 pv e2e4 e7e5 
info multipv 1 depth 23 seldepth 30 score cp 29 time 7906 nodes 10580385 nps 1338272 pv e2e4 e7e5 g1f3 b8c6 
info multipv 1 depth 24 seldepth 30 score cp 46 time 9469 nodes 12663125 nps 1337324 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 b7c6 e4e5 d8e7 d1e2 f6d5 c2c4 d5b6 b1c3 d7d6 e5d6 e7e2 f1e2 f8d6 c3e4 c8f5 e4d6 c7d6 
info multipv 1 depth 25 seldepth 30 score cp 46 time 11234 nodes 15015763 nps 1336635 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 
info multipv 1 depth 25 seldepth 32 score cp 46 time 45000 nodes 60719117 nps 1349313 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 
bestmove e2e4

Score of Altair203 vs Altair202: 357 - 279 - 405  [0.537] 1041
...      Altair203 playing White: 243 - 81 - 196  [0.656] 520
...      Altair203 playing Black: 114 - 198 - 209  [0.419] 521
...      White vs Black: 441 - 195 - 405  [0.618] 1041
Elo difference: 26.1 +/- 16.5, LOS: 99.9 %, DrawRatio: 38.9 %
SPRT: llr 2.98 (101.3%), lbound -2.94, ubound 2.94 - H1 was accepted
```


### 2.0.4
Aspiration Window Improvements

```
ELO   | 18.29 +- 9.98 (95%)
SPRT  | 5.0+0.06s Threads=1 Hash=16MB
LLR   | 3.04 (-2.94, 2.94) [0.00, 6.15]
GAMES | N: 2624 W: 808 L: 670 D: 1146
```

### 2.0.5
Move ordering Improvements

```
ELO   | 6.04 +- 4.55 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 12200 W: 3435 L: 3223 D: 5542
```

### 2.0.6
Capture history for qsearch

```
ELO   | 8.87 +- 5.97 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 7248 W: 2113 L: 1928 D: 3207
```

### 2.0.7
Slightly randomized draw scores as an incentive for better search tree exploration
```
ELO   | 2.03 +- 4.69 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -0.01 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 11984 W: 3455 L: 3385 D: 5144

Score of Altair2.0.7 vs Altair2.0.0: 141 - 74 - 235 [0.574]
...      Altair2.0.7 playing White: 72 - 38 - 115  [0.576] 225
...      Altair2.0.7 playing Black: 69 - 36 - 120  [0.573] 225
...      White vs Black: 108 - 107 - 235  [0.501] 450
Elo difference: 52.1 +/- 22.2, LOS: 100.0 %, DrawRatio: 52.2 %
454 of 50000 games finished.
```

### 2.0.8
Number of times alpha has been raised in a node factors into the LMR reduction

```
ELO   | 1.97 +- 3.72 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -0.08 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 19080 W: 5508 L: 5400 D: 8172
```

### 2.0.9
TT-prefetch to improve speed and cache hits.

### 2.1.0
Fewer reductions for moves which give checks

```
ELO   | 2.81 +- 4.51 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 0.60 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 12960 W: 3750 L: 3645 D: 5565
```

### 2.1.1
Tuning Search Parameter Values using Weather Factory over 390K games

```
ELO   | 10.24 +- 6.58 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 6144 W: 1856 L: 1675 D: 2613
```

### 2.1.2
No returning TT values at root

### 2.1.3
Remove Singular Extensions

### 2.1.4
Add Futility Pruning

```
ELO   | 8.62 +- 5.90 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 7616 W: 2272 L: 2083 D: 3261
```

### 2.1.5
Using a new Aspiration Windows framework

```
ELO   | 18.63 +- 11.39 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 3.00 (-2.94, 2.94) [0.00, 8.00]
GAMES | N: 2072 W: 655 L: 544 D: 873
```

### 2.1.6
My idea to scale initial aspiration windows based on depth

```
ELO   | 7.01 +- 5.11 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 10160 W: 3013 L: 2808 D: 4339
```

### 2.1.7
Static Exchange Evaluation Move ordering

```
ELO   | 9.36 +- 6.22 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 6944 W: 2110 L: 1923 D: 2911
```

### 2.1.8
Static Exchange Evaluation pruning in qsearch

```
ELO   | 13.79 +- 7.92 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.99 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 4360 W: 1371 L: 1198 D: 1791
```

### 2.1.9
Static Exchange Evaluation pruning in negamax

```
ELO   | 19.55 +- 9.65 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 2864 W: 902 L: 741 D: 1221
```

### 2.2.0
King Danger Ring Evaluation

```
Score of Altair220 vs Altair219: 445 - 409 - 616  [0.512] 1470
...      Altair220 playing White: 312 - 117 - 307  [0.632] 736
...      Altair220 playing Black: 133 - 292 - 309  [0.392] 734
...      White vs Black: 604 - 250 - 616  [0.620] 1470
Elo difference: 8.5 +/- 13.5, LOS: 89.1 %, DrawRatio: 41.9 %
SPRT: llr 0.735 (25.0%), lbound -2.94, ubound 2.94
```

### 2.2.1
Very slightly lowering soft and hard time limit bounds \
Around equal or better in self play over 1000 games


### 2.2.2
Switching Blockers from a one dimensional array to 2 dimensions based on piece | rank

```
Score of Altair222 vs Altair221: 527 - 434 - 649  [0.529] 1610
...      Altair222 playing White: 361 - 114 - 331  [0.653] 806
...      Altair222 playing Black: 166 - 320 - 318  [0.404] 804
...      White vs Black: 681 - 280 - 649  [0.625] 1610
Elo difference: 20.1 +/- 13.1, LOS: 99.9 %, DrawRatio: 40.3 %
SPRT: llr 2.6 (88.3%), lbound -2.94, ubound 2.94
```

### 2.2.3
Mobility Changes

```
ELO   | 6.11 +- 4.65 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 12400 W: 3709 L: 3491 D: 5200
```


### 2.2.4
Scaling the initial Aspiration Window based on number of retries

```
ELO   | 1.30 +- 2.02 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 65800 W: 19252 L: 19006 D: 27542
```


### 2.2.5
Outpost Eval

```
ELO   | 1.58 +- 2.98 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -0.87 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 30336 W: 8923 L: 8785 D: 12628
```


### 2.2.6
Late Move Reductions on Bad Captures

```
ELO   | 6.47 +- 4.83 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 11496 W: 3438 L: 3224 D: 4834
```


### 2.2.7
Continuation History for Move Ordering

```
ELO   | 10.74 +- 6.80 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 5824 W: 1782 L: 1602 D: 2440
```

### 2.2.8
Drawishness calculator changes - only tested over affected endgame positions. \
Not tested over games, as they only influence niche positions.

### 2.2.9
Evaluating the rule of the pawn / passed pawn's square / square of the pawn

go movetime 50000:
```
info multipv 1 depth 1 seldepth 1 score cp 68 time 1 nodes 26 nps 26000 pv e2e3 
info multipv 1 depth 2 seldepth 2 score cp 28 time 1 nodes 89 nps 89000 pv e2e3 e7e6 
info multipv 1 depth 3 seldepth 3 score cp 51 time 1 nodes 174 nps 174000 pv e2e3 e7e6 b1c3 
info multipv 1 depth 4 seldepth 4 score cp 28 time 1 nodes 324 nps 324000 pv e2e3 e7e6 b1c3 b8c6 
info multipv 1 depth 5 seldepth 6 score cp 38 time 2 nodes 570 nps 285000 pv e2e3 e7e6 b1c3 b8c6 g1f3 
info multipv 1 depth 6 seldepth 6 score cp 28 time 4 nodes 959 nps 239750 pv e2e3 e7e6 b1c3 b8c6 g1f3 g8f6 
info multipv 1 depth 7 seldepth 9 score cp 24 time 16 nodes 2881 nps 180062 pv e2e3 e7e6 b1c3 b8c6 g1f3 g8f6 d2d4 
info multipv 1 depth 8 seldepth 10 score cp 46 time 64 nodes 12092 nps 188937 pv g1f3 d7d5 d2d3 g8f6 c1e3 b8c6 b1c3 
info multipv 1 depth 9 seldepth 11 score cp 35 time 77 nodes 22056 nps 286441 pv g1f3 g8f6 b1c3 d7d5 e2e3 e7e6 
info multipv 1 depth 10 seldepth 12 score cp 48 time 95 nodes 39417 nps 414915 pv e2e4 d7d5 e4d5 g8f6 d2d4 d8d5 b1c3 d5e6 c1e3 b8c6 
info multipv 1 depth 11 seldepth 14 score cp 46 time 106 nodes 52339 nps 493764 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 f1b5 c8d7 b1c3 d7b5 c3b5 b8c6 
info multipv 1 depth 12 seldepth 14 score cp 43 time 122 nodes 71893 nps 589286 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 f1b5 b8d7 e1g1 a7a6 b5e2 e7e5 d2d4 
info multipv 1 depth 13 seldepth 16 score cp 38 time 152 nodes 107290 nps 705855 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 f1b5 b8d7 b1c3 e7e6 d2d4 a7a6 b5d7 c8d7 c1g5 
info multipv 1 depth 14 seldepth 17 score cp 49 time 217 nodes 182957 nps 843119 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 c2c3 g8f6 d2d4 c8f5 f1b5 b8c6 f3e5 a8c8 e1g1 
info multipv 1 depth 15 seldepth 18 score cp 35 lowerbound time 271 nodes 245507 nps 905929 pv e2e4 d7d5 e4d5 c7c6 g1f3 c6d5 c2c3 g8f6 d2d4 e7e6 f1d3 f8d6 c1e3 
info multipv 1 depth 15 seldepth 20 score cp 52 upperbound time 327 nodes 308531 nps 943519 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 g1f3 e7e5 f1b5 g8f6 f3e5 f8b4 
info multipv 1 depth 15 seldepth 20 score cp 43 time 329 nodes 311264 nps 946091 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 g1f3 e7e5 f1b5 c8d7 d2d3 a7a6 b5c6 d7c6 
info multipv 1 depth 16 seldepth 20 score cp 42 time 412 nodes 407960 nps 990194 pv e2e4 d7d5 e4d5 c7c6 d5c6 b8c6 g1f3 e7e5 b1c3 g8f6 f1b5 c8g4 d2d3 f8c5 c1e3 c5e3 
info multipv 1 depth 17 seldepth 23 score cp 44 time 800 nodes 841893 nps 1052366 pv e2e4 c7c5 g1f3 b8c6 b1c3 e7e6 d2d4 c5d4 f3d4 f8b4 d4c6 b7c6 d1d4 b4c3 d4c3 g8f6 c1g5 e8g8 
info multipv 1 depth 18 seldepth 23 score cp 53 time 998 nodes 1067261 nps 1069399 pv e2e4 c7c5 g1f3 b8c6 b1c3 e7e6 d2d4 c5d4 f3d4 f8b4 d4c6 b7c6 d1d4 b4c3 d4c3 g8f6 c1g5 e8g8 e4e5 
info multipv 1 depth 19 seldepth 23 score cp 44 time 1407 nodes 1528893 nps 1086633 pv e2e4 c7c5 g1f3 b8c6 b1c3 e7e6 d2d4 c5d4 f3d4 f8b4 d4c6 b7c6 d1d4 b4c3 d4c3 g8f6 c1g5 e8g8 g5f6 d8f6 
info multipv 1 depth 20 seldepth 24 score cp 48 time 2031 nodes 2232036 nps 1098983 pv e2e4 c7c5 g1f3 b8c6 f1b5 e7e6 e1g1 g8e7 d2d4 c5d4 c2c3 d7d5 e4d5 e7d5 c3d4 f8e7 b1c3 e8g8 c3d5 e6d5 
info multipv 1 depth 21 seldepth 26 score cp 36 lowerbound time 3621 nodes 3976252 nps 1098108 pv e2e4 e7e5 d2d4 e5d4 g1f3 b8c6 f3d4 g8f6 b1c3 f8b4 d4c6 b7c6 f1d3 e8g8 e1g1 d7d5 e4d5 c6d5 a1b1 
info multipv 1 depth 21 seldepth 26 score cp 35 time 4627 nodes 5065837 nps 1094842 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 
info multipv 1 depth 22 seldepth 27 score cp 35 time 5655 nodes 6207546 nps 1097709 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 
info multipv 1 depth 23 seldepth 32 score cp 35 time 7369 nodes 8094754 nps 1098487 pv e2e4 e7e5 g1f3 b8c6 
info multipv 1 depth 24 seldepth 32 score cp 35 time 8139 nodes 8901332 nps 1093664 pv e2e4 e7e5 g1f3 b8c6 
info multipv 1 depth 25 seldepth 32 score cp 35 time 9595 nodes 10454877 nps 1089617 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 
info multipv 1 depth 26 seldepth 32 score cp 35 time 10885 nodes 11813047 nps 1085259 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 d4c6 d7c6 d1d8 e8d8 b1c3 f8b4 c1d2 c8e6 
info multipv 1 depth 27 seldepth 32 score cp 30 time 24123 nodes 25710485 nps 1065807 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 b1c3 c7c5 c1e3 b8a6 c4d5 f6d5 c3d5 e6d5 g2g3 c5c4 f1g2 f8b4 e3d2 e8g8 e1g1 c8f5 f3h4 f5e6 e2e4 f8e8 e4e5 b4d2 
info multipv 1 depth 28 seldepth 32 score cp 30 time 34666 nodes 37125081 nps 1070936 pv g1f3 g8f6 d2d4 e7e6 
bestmove g1f3
```

Testing:
```
ELO   | 6.34 +- 6.65 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [-5.00, 0.00]
GAMES | N: 6024 W: 1787 L: 1677 D: 2560
```

### 2.3.0
Zugzwang checks for Null Move Pruning

```
ELO   | 6.82 +- 5.04 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 10544 W: 3155 L: 2948 D: 4441
```

### 2.3.1
Mate Threat Extensions

```
ELO   | 0.99 +- 3.13 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -1.68 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 27000 W: 7781 L: 7704 D: 11515
```

### 2.3.2
TT move ordering fixed in qsearch \
(little to no elo gained)

### 2.3.3
Passed Pawn Extensions

```
ELO   | 6.54 +- 4.88 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 11368 W: 3435 L: 3221 D: 4712
```

### 2.3.4
Reductions in LMR reduced based on recaptures

```
ELO   | 1.18 +- 2.14 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 58184 W: 16843 L: 16645 D: 24696
```

### 2.3.5
Better zugzwang conditions in NMP

```
ELO   | 3.37 +- 2.61 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 3.04 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 38936 W: 11393 L: 11015 D: 16528
```

### 2.3.6
Skip evaluating while in check

```
ELO   | 1.98 +- 4.69 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -0.07 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 12312 W: 3635 L: 3565 D: 5112
```

### 2.3.7
Only use SEE for move ordering under certain conditions based on history scores as it is expensive

```
ELO   | 4.25 +- 5.13 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 1.31 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 10312 W: 3087 L: 2961 D: 4264
```

### 2.3.8
No returning TT scores in pv nodes \
(helped fix crashes and illegals in Lazy SMP)

```
ELO   | 7.46 +- 14.24 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 0.42 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 1304 W: 386 L: 358 D: 560
```

### 2.3.9
Lazy SMP multi-threading implemented

STC 2CPU vs 1CPU
```
ELO   | 95.49 +- 32.54 (95%)
SPRT  | 8.0+0.08s Threads=2 Hash=32MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 10.00]
GAMES | N: 276 W: 118 L: 44 D: 114
```

LTC 2CPU vs 1CPU
```
ELO   | 80.14 +- 35.44 (95%)
SPRT  | 40.0+0.40s Threads=2 Hash=256MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 15.00]
GAMES | N: 225 W: 90 L: 39 D: 96
```

STC 4CPU vs 1CPU
```
ELO   | 210.17 +- 88.19 (95%)
SPRT  | 8.0+0.08s Threads=4 Hash=64MB
LLR   | 2.99 (-2.94, 2.94) [0.00, 20.00]
GAMES | N: 74 W: 48 L: 8 D: 18
```

### 2.4.0
Singular Extensions

```
ELO   | 7.11 +- 5.16 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 9976 W: 2965 L: 2761 D: 4250
```

### 2.4.1
Make sure to clear the state stack upon every new search

```
ELO   | 1.93 +- 2.21 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -0.24 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 52792 W: 14867 L: 14573 D: 23352
```

### 2.4.2
Multi-cut

```
ELO   | 1.29 +- 2.00 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -2.79 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 64464 W: 18121 L: 17882 D: 28461
```

### 2.4.3
Remove razoring

go movetime 50000:

```
info multipv 1 depth 1 seldepth 1 score cp 68 time 1 nodes 26 nps 26000 pv e2e3 
info multipv 1 depth 2 seldepth 2 score cp 28 time 1 nodes 89 nps 89000 pv e2e3 
info multipv 1 depth 3 seldepth 3 score cp 51 time 1 nodes 174 nps 174000 pv e2e3 e7e6 
info multipv 1 depth 4 seldepth 4 score cp 28 time 1 nodes 324 nps 324000 pv e2e3 e7e6 
info multipv 1 depth 5 seldepth 6 score cp 38 time 2 nodes 570 nps 285000 pv e2e3 e7e6 
info multipv 1 depth 6 seldepth 6 score cp 28 time 2 nodes 959 nps 479500 pv e2e3 e7e6 b1c3 
info multipv 1 depth 7 seldepth 9 score cp 24 time 9 nodes 3571 nps 396777 pv e2e3 e7e6 b1c3 
info multipv 1 depth 8 seldepth 9 score cp 28 time 14 nodes 6457 nps 461214 pv e2e3 e7e6 d2d4 
info multipv 1 depth 9 seldepth 11 score cp 24 time 21 nodes 10141 nps 482904 pv e2e3 e7e6 d2d4 c7c6 
info multipv 1 depth 10 seldepth 12 score cp 38 time 44 nodes 24130 nps 548409 pv g1f3 g8f6 b1c3 d7d5 
info multipv 1 depth 11 seldepth 13 score cp 46 time 76 nodes 52321 nps 688434 pv e2e4 d7d5 e4d5 c7c6 g1f3 
info multipv 1 depth 12 seldepth 15 score cp 57 time 101 nodes 78459 nps 776821 pv e2e4 c7c5 b1c3 b8c6 g1f3 
info multipv 1 depth 13 seldepth 18 score cp 42 time 171 nodes 161645 nps 945292 pv e2e4 d7d5 e4d5 c7c6 d2d4 c6d5 g1f3 g8f6 f1d3 e7e6 e1g1 f8d6 c2c3 
info multipv 1 depth 14 seldepth 20 score cp 25 time 278 nodes 285763 nps 1027924 pv e2e4 d7d5 e4d5 c7c6 d2d4 c6d5 g1f3 g8f6 c1f4 e7e6 f1d3 f8d6 f4d6 d8d6 e1g1 
info multipv 1 depth 15 seldepth 22 score cp 34 time 357 nodes 377278 nps 1056801 pv e2e4 d7d5 e4d5 c7c6 b1c3 g8f6 d2d4 c6d5 g1f3 e7e6 c1f4 f8b4 f1b5 b8c6 e1g1 e8g8 
info multipv 1 depth 16 seldepth 24 score cp 34 time 787 nodes 859600 nps 1092249 pv g1f3 g8f6 d2d4 e7e6 b1c3 d7d5 c1g5 f8b4 e2e3 e8g8 f1d3 c7c5 d4c5 b8c6 g5f6 d8f6 e1g1 
info multipv 1 depth 17 seldepth 24 score cp 41 time 1250 nodes 1371006 nps 1096804 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 e2e3 b8c6 b1c3 c8d7 a2a3 f8e7 c4d5 f6d5 f1d3 d5c3 b2c3 
info multipv 1 depth 18 seldepth 25 score cp 43 time 1799 nodes 1977070 nps 1098982 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 e2e3 c7c5 c4d5 e6d5 f1b5 c8d7 b1c3 c5d4 f3d4 d7b5 c3b5 b8c6 e1g1 a7a6 b5c3 
info multipv 1 depth 19 seldepth 29 score cp 31 time 2513 nodes 2767236 nps 1101168 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 c1g5 b8c6 e2e3 f8e7 c4d5 e6d5 b1c3 e8g8 f1b5 c8g4 e1g1 h7h6 g5f6 
info multipv 1 depth 20 seldepth 29 score cp 31 time 3018 nodes 3339815 nps 1106631 pv g1f3 g8f6 d2d4 e7e6 c2c4 d7d5 c1g5 b8c6 e2e3 f8e7 c4d5 e6d5 b1c3 e8g8 f1b5 c8g4 e1g1 h7h6 
info multipv 1 depth 21 seldepth 34 score cp 40 time 4924 nodes 5393563 nps 1095362 pv g1f3 d7d5 d2d4 c8f5 c2c4 e7e6 b1c3 g8f6 f3h4 f5g6 c4d5 e6d5 g2g3 f8b4 f1g2 b8c6 h4g6 f7g6 e1g1 e8g8 a2a3 
info multipv 1 depth 22 seldepth 34 score cp 37 time 6227 nodes 6858388 nps 1101395 pv g1f3 d7d5 d2d4 c8f5 c2c4 e7e6 b1c3 g8f6 f3h4 f5g6 c4d5 e6d5 g2g3 f8b4 f1g2 e8g8 h4g6 h7g6 e1g1 c7c6 a2a3 b4c3 b2c3 
info multipv 1 depth 23 seldepth 35 score cp 32 time 9729 nodes 10743661 nps 1104292 pv g1f3 d7d5 d2d4 c8f5 c2c4 e7e6 b1c3 g8f6 f3h4 f5g6 c4d5 e6d5 g2g3 c7c6 f1g2 b8d7 e1g1 f8b4 a2a3 b4c3 b2c3 e8g8 h4g6 
info multipv 1 depth 24 seldepth 35 score cp 32 time 11466 nodes 12683356 nps 1106170 pv g1f3 d7d5 d2d4 c8f5 c2c4 e7e6 b1c3 g8f6 f3h4 f5g6 c4d5 e6d5 g2g3 c7c6 f1g2 b8d7 e1g1 f8b4 a2a3 b4c3 b2c3 e8g8 
info multipv 1 depth 25 seldepth 36 score cp 42 upperbound time 16717 nodes 18230935 nps 1090562 pv e2e4 e7e5 g1f3 d7d5 e4d5 
info multipv 1 depth 25 seldepth 36 score cp 52 upperbound time 18267 nodes 19914513 nps 1090190 pv e2e4 e7e5 g1f3 b8c6 d2d4 e5d4 f3d4 g8f6 
info multipv 1 depth 25 seldepth 36 score cp 46 time 21360 nodes 23298734 nps 1090764 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 c2c3 c8d7 f1d3 c5d4 c3d4 d8b6 g1f3 b8c6 d3c2 c6b4 e1g1 a8c8 b1c3 b4c2 d1c2 d7b5 f1d1 
info multipv 1 depth 26 seldepth 36 score cp 35 lowerbound time 24804 nodes 27074163 nps 1091524 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 c2c3 c8d7 
info multipv 1 depth 26 seldepth 36 score cp 46 time 26361 nodes 28799363 nps 1092498 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 c2c3 c8d7 g1f3 b8c6 f1d3 c5d4 c3d4 d8b6 d3c2 c6b4 e1g1 a8c8 b1c3 b4c2 d1c2 d7b5 f1d1 
info multipv 1 depth 27 seldepth 36 score cp 35 lowerbound time 30564 nodes 33417240 nps 1093352 pv e2e4 e7e6 d2d4 d7d5 e4e5 c7c5 c2c3 
info multipv 1 depth 27 seldepth 36 score cp 29 time 43490 nodes 47442888 nps 1090891 pv d2d4 g8f6 c2c4 c7c6 c1f4 d7d5 e2e3 c8f5 b1c3 e7e6 g1f3 f8d6 f4d6 d8d6 f1d3 f5d3 d1d3 e8g8 e1g1 d5c4 d3c4 b8d7 c4d3 h7h6 a1c1 a7a5 d3c2 b7b5 c3e4 f6e4 
bestmove d2d4
```

Testing:

```
ELO   | 3.65 +- 5.72 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [-5.00, 1.00]
GAMES | N: 7896 W: 2248 L: 2165 D: 3483
```


### 2.4.4
Do not do certain pruning and heuristics when searching for a mate

```
ELO   | 1.43 +- 3.70 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [-4.00, 1.00]
GAMES | N: 18768 W: 5242 L: 5165 D: 8361
```

### 2.4.5
Double Extensions

```
ELO   | 2.66 +- 3.78 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 0.70 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 18040 W: 5106 L: 4968 D: 7966
```

### 2.4.6
Negative Extensions

```
ELO   | 3.50 +- 2.78 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 33392 W: 9500 L: 9164 D: 14728
```

### 2.4.7
Remove Mate Threat Extensions

```
ELO   | 0.65 +- 5.40 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 1.26 (-2.94, 2.94) [-5.00, 0.00]
GAMES | N: 8016 W: 2036 L: 2021 D: 3959
```

### 2.4.8 (3.0.0)
More aggressive Noisy LMR values

```
ELO   | 3.24 +- 2.53 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 40352 W: 11470 L: 11094 D: 17788
```

### 3.0.1
Fischer Random Chess Implemented

### 3.0.2
Small Singular Extensions fix

```
ELO   | 1.93 +- 3.34 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -0.10 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 23032 W: 6465 L: 6337 D: 10230
```

### 3.0.3
bug-fix that possibly fixes some out of bounds errors
```
ELO   | -0.29 +- 2.19 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [-4.00, 1.00]
GAMES | N: 53632 W: 14862 L: 14906 D: 23864
```

### 3.0.4
More history bonus when improving or for pv-nodes

```
ELO   | 1.64 +- 1.86 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -1.61 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 73928 W: 20668 L: 20319 D: 32941
```

### 3.0.5
Scale soft time limit by best move node count percentage

STC:
```
ELO   | 20.14 +- 9.64 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 2712 W: 814 L: 657 D: 1241
```

LTC:
```
ELO   | 17.75 +- 8.68 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 3.02 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 3056 W: 837 L: 681 D: 1538
```

### 3.0.6
Allow checks in LMR
```
ELO   | 12.90 +- 7.49 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 4472 W: 1295 L: 1129 D: 2048
```

### 3.0.7 & 3.0.8
Pruning fixes (kept for simplification)

First part
```
ELO   | -9.70 +- 7.61 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -3.02 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 4264 W: 1077 L: 1196 D: 1991
```

Second part
```
ELO   | 8.53 +- 5.80 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 7456 W: 2114 L: 1931 D: 3411
```

### 3.0.9
Mobility arrays instead of multipliers

```
ELO   | 4.56 +- 3.60 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 3.03 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 19816 W: 5633 L: 5373 D: 8810
```

### 3.1.0
Change check extension location to extensions area for simplification

```
ELO   | 1.04 +- 2.18 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 52496 W: 14231 L: 14074 D: 24191
```

### 3.1.1
Interesting moves and fewer reductions for these moves

```
ELO   | 5.10 +- 3.97 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.99 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 15600 W: 4266 L: 4037 D: 7297
```

### 3.1.2
Clamp the LMR depth to prevent reducing into qsearch immediately

```
ELO   | 4.36 +- 3.48 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 20552 W: 5668 L: 5410 D: 9474
```

### 3.1.3
Do not reset continuation histories every move

```
ELO   | 17.87 +- 9.00 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 3056 W: 894 L: 737 D: 1425
```

### 3.1.4
Improving Heuristic for futility pruning

```
ELO   | 2.52 +- 1.68 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 87320 W: 23705 L: 23072 D: 40543
```

### 3.1.5
Failing term implemented. \
This term is true when the current evaluation is worse than the previous evaluation by a certain margin. \
Tested in quiet LMP.

```
ELO   | 0.40 +- 2.81 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -2.94 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 31184 W: 8332 L: 8296 D: 14556
```

(Kept the patch because it is interesting)

### 3.1.6
Failing term tested in LMR

```
ELO   | 0.63 +- 2.60 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 36816 W: 9930 L: 9863 D: 17023
```

(Kept the patch because it is interesting)

### 3.1.7
Fix 50 move related issues

```
ELO   | 4.83 +- 6.79 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | 2.97 (-2.94, 2.94) [-5.00, 3.00]
GAMES | N: 5464 W: 1524 L: 1448 D: 2492
```

### 3.1.8
LMR moves condition simplification patch

```
ELO   | 0.15 +- 2.99 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=16MB
LLR   | -2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 27256 W: 7193 L: 7181 D: 12882
https://chess.swehosting.se/test/1812/
```

### 3.1.9
Favor PV nodes for TT entry replacement

```
ELO   | 0.64 +- 2.56 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 37336 W: 9902 L: 9833 D: 17601
https://chess.swehosting.se/test/1885/
```

(Kept the patch because it is interesting)

### 3.2.0
Let quiet-LMP break out of the move loop

```
ELO   | 12.97 +- 7.52 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 4448 W: 1291 L: 1125 D: 2032
https://chess.swehosting.se/test/1943/
```

### 3.2.1
Save the best move on fail highs in aspiration window searches

```
ELO   | 4.43 +- 3.54 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 19944 W: 5525 L: 5271 D: 9148
https://chess.swehosting.se/test/2189/
```

### 3.2.2
Speedup of around a factor of 15% based a PR by @archishou to Altair bitboards-rewrite branch for move picking

### 3.2.3
Move ordering Changes

```
ELO   | 3.37 +- 2.66 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 35552 W: 9874 L: 9529 D: 16149
https://chess.swehosting.se/test/2244/
```

### 3.2.4
TM scaling by score changes throughout search

```
ELO   | 5.45 +- 4.21 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 14080 W: 3911 L: 3690 D: 6479
https://chess.swehosting.se/test/2279/
```

### 3.2.5
SEE pruning on PV nodes

```
ELO   | 3.35 +- 2.64 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.99 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 35368 W: 9610 L: 9269 D: 16489
https://chess.swehosting.se/test/2304/
```

### 3.2.6
Move ordering changes

```
ELO   | 4.80 +- 3.83 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 17792 W: 5130 L: 4884 D: 7778
https://chess.swehosting.se/test/2372/
```

### 3.2.7 (4.0.0)
Skip SEE in qsearch under certain conditions

```
ELO   | 4.32 +- 3.46 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 20672 W: 5672 L: 5415 D: 9585
https://chess.swehosting.se/test/2389/
```

## --- Bitboards Rewrite ---
Altair is now rewritten using bitboards as the internal board representation with magic bitboards
for generating sliding attacks. Altair now has the same search, but the evaluation has been completely removed for
the purpose of rewriting it. 

Starting off with a material only evaluation function, Altair is at around a 2050 Elo level.

### 4.0.1
PSTs (Piece Square Tables)

```
ELO   | 620.44 +- 870.23 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 8.00]
GAMES | N: 128 W: 124 L: 3 D: 1
https://chess.swehosting.se/test/2031/
```

### 4.0.2
Fixed SEE under a bitboards representation

```
ELO   | 36.13 +- 13.62 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 1496 W: 521 L: 366 D: 609
https://chess.swehosting.se/test/2049/
```

### 4.0.3
Passed Pawns Evaluation

```
ELO   | 19.20 +- 9.92 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 3152 W: 1138 L: 964 D: 1050
https://chess.swehosting.se/test/2052/
```

### 4.0.4
Blocker Evaluation

```
ELO   | 38.03 +- 14.23 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 1440 W: 526 L: 369 D: 545
https://chess.swehosting.se/test/2054/
```

### 4.0.5
Protected Passed Pawn Evaluation

```
ELO   | 3.74 +- 2.99 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 31480 W: 9719 L: 9380 D: 12381
https://chess.swehosting.se/test/2060/
```

### 4.0.6
Phalanx Pawn Evaluation

```
ELO   | 15.85 +- 8.67 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 3728 W: 1210 L: 1040 D: 1478
https://chess.swehosting.se/test/2069/
```

### 4.0.7
Isolated Pawn Evaluation

```
ELO   | 1.96 +- 3.32 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -0.30 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 26560 W: 8471 L: 8321 D: 9768
https://chess.swehosting.se/test/2096/
```

### 4.0.8
Fix Extensions due to a bitboards bug

```
ELO   | 35.28 +- 17.09 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.07 (-2.94, 2.94) [-7.00, 0.00]
GAMES | N: 1008 W: 367 L: 265 D: 376
https://chess.swehosting.se/test/2101/
```

### 4.0.9
Bishop Pair Evaluation

```
ELO   | 38.31 +- 14.41 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 1448 W: 543 L: 384 D: 521
https://chess.swehosting.se/test/2117/
```

### 4.1.0
Second Blockers Evaluation

```
ELO   | 3.38 +- 4.79 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 0.90 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 12016 W: 3632 L: 3515 D: 4869
https://chess.swehosting.se/test/2119/
```

### 4.1.1
Tempo Evaluation

```
ELO   | 14.27 +- 8.07 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.02 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 4288 W: 1380 L: 1204 D: 1704
https://chess.swehosting.se/test/2123/
```

### 4.1.2
Mobility Evaluation

```
ELO   | 77.00 +- 21.12 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.99 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 720 W: 316 L: 159 D: 245
https://chess.swehosting.se/test/2143/
```

### 4.1.3
Semi-open + Open file Evaluation

```
ELO   | 39.45 +- 14.59 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 1424 W: 540 L: 379 D: 505
https://chess.swehosting.se/test/2147/
```

### 4.1.4
Piece Threat Evaluation

```
ELO   | 43.11 +- 15.34 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 1280 W: 488 L: 330 D: 462
https://chess.swehosting.se/test/2149/
```

### 4.1.5
Speedup Refactors

```
ELO   | 22.86 +- 11.61 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [-5.00, 0.00]
GAMES | N: 2024 W: 660 L: 527 D: 837
https://chess.swehosting.se/test/2175/
```

### 4.1.6
King Ring Attack Evaluation

```
ELO   | 24.79 +- 11.27 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 2288 W: 795 L: 632 D: 861
https://chess.swehosting.se/test/2192/
```

### 4.1.7
Total King Ring Attack Evaluation

```
ELO   | 11.52 +- 7.03 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.01 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 5400 W: 1647 L: 1468 D: 2285
https://chess.swehosting.se/test/2193/
```

### 4.1.8
@archishou Speedup Pull Request

### 4.1.9
King Pawn Shield Evaluation

```
ELO   | 24.71 +- 11.22 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 2296 W: 794 L: 631 D: 871
https://chess.swehosting.se/test/2228/
```

### 4.2.0
King Pawn Storm Evaluation (merged as it leads to interesting play-styles)

```
ELO   | 0.12 +- 6.70 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -0.66 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 5840 W: 1655 L: 1653 D: 2532
https://chess.swehosting.se/test/2393/
```

### 4.2.1
King Tropism

```
ELO   | 4.44 +- 3.57 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 20640 W: 6001 L: 5737 D: 8902
https://chess.swehosting.se/test/2394/
```

### 4.2.2
Hand-tuned, original drawishness evaluation

```
ELO   | 11.71 +- 6.84 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 4748 W: 1220 L: 1060 D: 2468
https://chess.swehosting.se/test/2443/
```

### 4.2.3
Opposite Colored Bishops Evaluation

```
ELO   | 1.66 +- 5.75 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -0.12 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 7328 W: 1937 L: 1902 D: 3489
https://chess.swehosting.se/test/2462/
```

### 4.2.4
Add -flto Compiler Flag

```
ELO   | 56.21 +- 16.66 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.99 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 904 W: 313 L: 168 D: 423
https://chess.swehosting.se/test/2465/
```

### 4.2.5
Doubled Pawns Evaluation

```
ELO   | 6.17 +- 4.63 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 11544 W: 3188 L: 2983 D: 5373
https://chess.swehosting.se/test/2539/
```

### 4.2.6
Square of the Pawn Rule Evaluation

```
ELO   | 1.95 +- 2.01 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -0.05 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 61864 W: 16821 L: 16473 D: 28570
https://chess.swehosting.se/test/2545/
```

### 4.2.7
Drawishness calculations improved

```
ELO   | 2.62 +- 4.04 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 0.68 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 13656 W: 3345 L: 3242 D: 7069
https://chess.swehosting.se/test/2569/
```

### 4.2.8
Total King Ring layer 1 weight doubled

```
ELO   | 5.17 +- 4.04 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 15720 W: 4479 L: 4245 D: 6996
https://chess.swehosting.se/test/2627/
```

### 4.2.9
No saving killers under certain conditions in a null search

```
ELO   | 4.07 +- 3.28 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 22696 W: 6120 L: 5854 D: 10722
https://chess.swehosting.se/test/2639/
```

### 4.3.0
TT fail low best move saving

```
ELO   | 10.44 +- 6.45 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.00 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 5728 W: 1561 L: 1389 D: 2778
https://chess.swehosting.se/test/2722/
```

### 4.3.1
Backward Pawns fix

```
ELO   | 6.06 +- 4.55 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 11992 W: 3328 L: 3119 D: 5545
https://chess.swehosting.se/test/3049/
```

### 4.3.2
Piece relative occupancies for evaluating terms such as mobility and king safety

```
ELO   | 2.98 +- 3.76 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 1.08 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 17840 W: 4930 L: 4777 D: 8133
https://chess.swehosting.se/test/3225/
```

### 4.3.3
Our king tropism

```
ELO   | 6.73 +- 4.95 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
GAMES | N: 10488 W: 3011 L: 2808 D: 4669
https://chess.swehosting.se/test/3282/
```

### 4.3.4
Fischer Random Chess implemented for bitboards


### 4.3.5
Null Move Pruning improving heuristic

```
ELO   | 11.82 +- 7.07 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.94 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 4880 W: 1368 L: 1202 D: 2310
https://chess.swehosting.se/test/3452/
```

### 4.3.6
Passed pawn king distance evaluation

```
ELO   | 10.96 +- 6.72 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.97 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 5392 W: 1504 L: 1334 D: 2554
https://chess.swehosting.se/test/3481/
```

### 4.3.7
Mobility Arrays

```
ELO   | 21.18 +- 9.89 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.91 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 2464 W: 714 L: 564 D: 1186
https://chess.swehosting.se/test/3493/
```

### 4.3.8
Backward Pawns 2

```
ELO   | 5.94 +- 4.52 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.89 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 11696 W: 3123 L: 2923 D: 5650
https://chess.swehosting.se/test/3545/
```

### 4.3.9
Lower Base Capture Margin

```
ELO: 1.89 +- 1.29 [0.607, 3.18]
LLR: 4.01 [0.0, 3.0] (-2.25, 2.89)
H1 Accepted
GAMES | N: 138192 W: 34571 L: 33822 D: 69799
https://chess.swehosting.se/test/3661/
```

### 4.4.0
More Aggressive Bad Captures

```
ELO   | 4.06 +- 3.26 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 21568 W: 5471 L: 5219 D: 10878
https://chess.swehosting.se/test/3871/
```

### 4.4.1
Index capture history by SEE result

```
ELO   | 3.63 +- 2.92 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.97 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 27168 W: 6934 L: 6650 D: 13584
https://chess.swehosting.se/test/3942/
```


## --- Original Data ---
Altair's HCE weights have been set completely to zero, and all data will be iteratively generated off this version.

### 5.0.1
First round of original HCE data generation

```
Score of Altair439-original-data-1 vs Altair439-original-data-0: 105 - 10 - 1 [0.909]
...      Altair439-original-data-1 playing White: 54 - 3 - 1  [0.940] 58
...      Altair439-original-data-1 playing Black: 51 - 7 - 0  [0.879] 58
...      White vs Black: 61 - 54 - 1  [0.530] 116
Elo difference: 400.8 +/- 121.9, LOS: 100.0 %, DrawRatio: 0.9 %
116 of 5000 games finished.
```

### 5.0.2
Second round of original HCE data generation

```
Score of Altair439-original-data-2 vs Altair439-original-data-1: 125 - 0 - 0 [1.000]
...      Altair439-original-data-2 playing White: 63 - 0 - 0  [1.000] 63
...      Altair439-original-data-2 playing Black: 62 - 0 - 0  [1.000] 62
...      White vs Black: 63 - 62 - 0  [0.504] 125
Elo difference: inf +/- nan, LOS: 100.0 %, DrawRatio: 0.0 %
125 of 5000 games finished.
```

```
Score of Altair439-original-data-2 vs vice10_mac_m1: 27 - 91 - 10 [0.250]
...      Altair439-original-data-2 playing White: 10 - 48 - 6  [0.203] 64
...      Altair439-original-data-2 playing Black: 17 - 43 - 4  [0.297] 64
...      White vs Black: 53 - 65 - 10  [0.453] 128
Elo difference: -190.8 +/- 67.1, LOS: 0.0 %, DrawRatio: 7.8 %
128 of 5000 games finished.
```


### 5.0.3
Third round of original HCE data generation

```
Score of Altair439-original-data-3 vs Altair439-original-data-2: 205 - 1 - 0 [0.995]
...      Altair439-original-data-3 playing White: 102 - 1 - 0  [0.990] 103
...      Altair439-original-data-3 playing Black: 103 - 0 - 0  [1.000] 103
...      White vs Black: 102 - 104 - 0  [0.495] 206
Elo difference: 924.7 +/- nan, LOS: 100.0 %, DrawRatio: 0.0 %
212 of 5000 games finished.
```

### 5.0.4
Fourth round of original HCE data generation

```
Score of Altair439-original-data-4 vs Altair439-original-data-3: 131 - 14 - 20 [0.855]
...      Altair439-original-data-4 playing White: 66 - 6 - 11  [0.861] 83
...      Altair439-original-data-4 playing Black: 65 - 8 - 9  [0.848] 82
...      White vs Black: 74 - 71 - 20  [0.509] 165
Elo difference: 307.6 +/- 67.3, LOS: 100.0 %, DrawRatio: 12.1 %
171 of 5000 games finished.
```

```
Score of Altair439-original-data-4 vs Altair439: 16 - 125 - 64 [0.234]
...      Altair439-original-data-4 playing White: 7 - 64 - 32  [0.223] 103
...      Altair439-original-data-4 playing Black: 9 - 61 - 32  [0.245] 102
...      White vs Black: 68 - 73 - 64  [0.488] 205
Elo difference: -205.9 +/- 42.5, LOS: 0.0 %, DrawRatio: 31.2 %
205 of 5000 games finished.
```

### 5.0.5
Fifth round of original HCE data generation

```
Score of Altair439-original-data-5 vs Altair439-original-data-4: 90 - 55 - 171 [0.555]
...      Altair439-original-data-5 playing White: 47 - 23 - 89  [0.575] 159
...      Altair439-original-data-5 playing Black: 43 - 32 - 82  [0.535] 157
...      White vs Black: 79 - 66 - 171  [0.521] 316
Elo difference: 38.6 +/- 25.9, LOS: 99.8 %, DrawRatio: 54.1 %
316 of 5000 games finished.
```

```
Score of Altair439-original-data-5 vs Altair439: 278 - 1116 - 740 [0.304]
...      Altair439-original-data-5 playing White: 148 - 549 - 370  [0.312] 1067
...      Altair439-original-data-5 playing Black: 130 - 567 - 370  [0.295] 1067
...      White vs Black: 715 - 679 - 740  [0.508] 2134
Elo difference: -144.2 +/- 12.3, LOS: 0.0 %, DrawRatio: 34.7 %
2134 of 5000 games finished.
```

### 5.0.6
Sixth round of original HCE data generation

```
Score of Altair439-original-data-6 vs Altair439-original-data-5: 47 - 19 - 52 [0.619]
...      Altair439-original-data-6 playing White: 20 - 12 - 28  [0.567] 60
...      Altair439-original-data-6 playing Black: 27 - 7 - 24  [0.672] 58
...      White vs Black: 27 - 39 - 52  [0.449] 118
Elo difference: 84.0 +/- 47.4, LOS: 100.0 %, DrawRatio: 44.1 %
118 of 5000 games finished.
```

```
Score of Altair439-original-data-6 vs Altair439: 57 - 163 - 122 [0.345]
...      Altair439-original-data-6 playing White: 25 - 87 - 59  [0.319] 171
...      Altair439-original-data-6 playing Black: 32 - 76 - 63  [0.371] 171
...      White vs Black: 101 - 119 - 122  [0.474] 342
Elo difference: -111.3 +/- 30.2, LOS: 0.0 %, DrawRatio: 35.7 %
342 of 5000 games finished.
```

### 5.0.7
Seventh round of original HCE data generation

```
Score of Altair439-original-data-7 vs Altair439-original-data-6: 124 - 110 - 265 [0.514]
...      Altair439-original-data-7 playing White: 59 - 54 - 137  [0.510] 250
...      Altair439-original-data-7 playing Black: 65 - 56 - 128  [0.518] 249
...      White vs Black: 115 - 119 - 265  [0.496] 499
Elo difference: 9.8 +/- 20.9, LOS: 82.0 %, DrawRatio: 53.1 %
499 of 5000 games finished.
```

### 5.0.8
Eighth and final round of original HCE data generation

```
Score of Altair439-original-data-8 vs Altair439-original-data-7: 350 - 320 - 625 [0.512]
...      Altair439-original-data-8 playing White: 174 - 155 - 319  [0.515] 648
...      Altair439-original-data-8 playing Black: 176 - 165 - 306  [0.509] 647
...      White vs Black: 339 - 331 - 625  [0.503] 1295
Elo difference: 8.1 +/- 13.6, LOS: 87.7 %, DrawRatio: 48.3 %
1301 of 5000 games finished.
```

```
Score of Altair439-original-data-8 vs Altair439: 97 - 218 - 178 [0.377]
...      Altair439-original-data-8 playing White: 57 - 100 - 90  [0.413] 247
...      Altair439-original-data-8 playing Black: 40 - 118 - 88  [0.341] 246
...      White vs Black: 175 - 140 - 178  [0.535] 493
Elo difference: -87.1 +/- 24.8, LOS: 0.0 %, DrawRatio: 36.1 %
501 of 5000 games finished.

```

## --- Introduction of NNUE ---

### 5.0.9
First net with 64 HL size, trained on 30M fens of HCE data. \
-46 against master compared to -87 compared to against master with original data HCE

```
ELO   | -46.02 +- 19.68 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -2.27 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 896 W: 268 L: 386 D: 242
https://chess.swehosting.se/test/3973/
```

### 5.1.0
Second net with 128 HL size, trained on 128M fens off the previous net.

```
ELO   | 136.97 +- 30.90 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 432 W: 244 L: 82 D: 106
https://chess.swehosting.se/test/4001/
```

### 5.1.1
Third net with 384 HL size, trained on 360M fens off the previous net.

```
ELO   | 129.54 +- 28.39 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.03 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 432 W: 221 L: 67 D: 144
https://chess.swehosting.se/test/4155/
```

### 5.1.2
Fourth net with 768 HL size, trained on ~800M fens off the previous net at 30 epochs.

```
ELO   | 4.96 +- 3.96 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.89 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 16256 W: 4588 L: 4356 D: 7312
https://chess.swehosting.se/test/4282/
```

### 5.1.3
Same data as above but trained to 55 epochs

```
ELO   | 17.18 +- 8.66 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.92 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 3056 W: 830 L: 679 D: 1547
https://chess.swehosting.se/test/4294/
```

### 5.1.4
Fix Capture Move History \
Merged for fixing ongoing issues in the engine of illogical and bad code.

```
ELO   | -1.97 +- 2.24 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -0.40 (-2.25, 2.89) [-5.00, 0.00]
GAMES | N: 44240 W: 10537 L: 10788 D: 22915
https://chess.swehosting.se/test/4329/

ELO: -1.97 +- 2.24 [-4.22, 0.273]
LLR: 4.25 [-8.0, 0.0] (-2.94, 2.94)
H1 Accepted
```

### 5.1.5
Change of MVV-LVA values for Delta Pruning mainly

```
ELO   | 8.67 +- 5.68 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.93 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 6736 W: 1666 L: 1498 D: 3572
https://chess.swehosting.se/test/4363/
```

### 5.1.6
Remove Delta Pruning altogether

```
ELO   | 12.85 +- 7.33 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.90 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 4192 W: 1097 L: 942 D: 2153
https://chess.swehosting.se/test/4376/
```

### 5.1.7
Cleanup LMR \
Passed with Simplification bounds [-3, 0]

```
ELO   | 2.21 +- 2.64 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 0.80 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 31488 W: 7552 L: 7352 D: 16584
https://chess.swehosting.se/test/4390/

LLR: 3.93 [-3.0, 0.0] (-2.94, 2.94)
```

### 5.1.8
Cont-hist on ply 4 added

```
ELO   | 4.14 +- 3.35 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.91 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 20288 W: 5105 L: 4863 D: 10320
https://chess.swehosting.se/test/4474/
```

### 5.1.9
Cont-hist added to the search move history score

```
ELO   | 3.61 +- 2.92 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.92 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 27136 W: 6941 L: 6659 D: 13536
https://chess.swehosting.se/test/4511/
```

### 5.2.0
New Net with data from previous net + 200M data with some FRC data mixed in

```
ELO   | 8.68 +- 5.75 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.07 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 7568 W: 2140 L: 1951 D: 3477
https://chess.swehosting.se/test/4571/
```

### 5.2.1
Verification Search (basic version)

```
ELO   | 6.96 +- 5.01 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.89 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 9088 W: 2335 L: 2153 D: 4600
https://chess.swehosting.se/test/4612/
```

### 5.2.2
New Net with fixed data generation

Standard:
```
ELO   | 0.43 +- 4.28 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -1.30 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 13840 W: 3800 L: 3783 D: 6257
https://chess.swehosting.se/test/4840/
FRC:
```

FRC:
```
ELO   | 22.20 +- 10.12 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.89 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 2304 W: 659 L: 512 D: 1133
https://chess.swehosting.se/test/4844/
```

### 5.2.3
SCRELU net

```
ELO   | 10.02 +- 6.51 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.90 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 6000 W: 1734 L: 1561 D: 2705
https://chess.swehosting.se/test/4848/
```

### 5.2.4
Time Management Changes

LTC

```
ELO   | 8.70 +- 5.65 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.92 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 6552 W: 1561 L: 1397 D: 3594
https://chess.swehosting.se/test/4874/
```

STC
```
ELO   | 15.24 +- 8.10 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.94 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 3536 W: 963 L: 808 D: 1765
https://chess.swehosting.se/test/4871/
```

### 5.2.5 (6.0.0)
Set reductions to integers only in LMR + slight additional LMR changes

```
ELO   | 6.05 +- 4.54 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.91 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 11136 W: 2856 L: 2662 D: 5618
https://chess.swehosting.se/test/4887/
```

### 6.0.1
TT Staged move generation +~30Knps

```
ELO   | 7.69 +- 5.56 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.94 (-2.25, 2.89) [-1.00, 4.00]
GAMES | N: 7008 W: 1717 L: 1562 D: 3729
https://chess.swehosting.se/test/5065/
```

### 6.0.2
Staged noisy / quiet + bad noisy generation +~70Knps

```
ELO   | 7.78 +- 5.27 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.94 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 7680 W: 1859 L: 1687 D: 4134
https://chess.swehosting.se/test/5170/
```

### 6.0.3
NNUE updates optimizations in search +~150Knps

```
ELO   | 23.92 +- 10.30 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.91 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 2080 W: 566 L: 423 D: 1091
https://chess.swehosting.se/test/5187/
```

### 6.0.4
Remove IID

```
ELO   | 4.05 +- 3.27 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.90 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 20144 W: 4810 L: 4575 D: 10759
https://chess.swehosting.se/test/5214/
```

### 6.0.5
Change IIR mechanics in PV nodes

```
Elo   | 16.35 +- 9.14 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.89 (-2.25, 2.89) [0.00, 5.00]
Games | N: 2552 W: 647 L: 527 D: 1378
Penta | [15, 250, 638, 346, 27]
https://antares2262.pythonanywhere.com/test/5/
```

### 6.0.6
Staged scoring efficiency changes + fixes

```
Elo   | 0.25 +- 2.87 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -2.26 (-2.25, 2.89) [0.00, 5.00]
Games | N: 26548 W: 6271 L: 6252 D: 14025
Penta | [220, 3241, 6338, 3250, 225]
```

Merged for simplification + bug fixes. Although not passing at [0, 5], did not lose any or much ELO.

### 6.0.7
Taffreta Net
Arch: (768->768)x2->1x8
Data: Trappist Data + 350M fens

```
ELO   | 34.34 +- 12.88 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.92 (-2.25, 2.89) [0.00, 5.00]
GAMES | N: 1472 W: 458 L: 313 D: 701
https://chess.swehosting.se/test/5240/
```

### 6.0.8
SE params changed

STC:
```
Elo   | -4.83 +- 8.13 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -1.55 (-2.25, 2.89) [0.00, 5.00]
Games | N: 3452 W: 827 L: 875 D: 1750
Penta | [49, 429, 798, 421, 29]
```

LTC:
```
Elo   | 2.56 +- 3.40 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 1.80 (-2.25, 2.89) [0.00, 5.00]
Games | N: 17940 W: 4089 L: 3957 D: 9894
Penta | [86, 2015, 4626, 2167, 76]
```

Merged for scaling as time control increases

### 6.0.9
Deeper / Shallower search

```
Elo   | 8.62 +- 6.33 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.89 (-2.25, 2.89) [0.00, 5.00]
Games | N: 5642 W: 1449 L: 1309 D: 2884
Penta | [57, 628, 1332, 726, 78]
```

### 6.1.0
Check Extension Change

STC
```
Elo   | 1.43 +- 1.76 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | -0.05 (-2.25, 2.89) [0.00, 5.00]
Games | N: 73502 W: 18165 L: 17863 D: 37474
Penta | [825, 8731, 17312, 9083, 800]
```

LTC
```
Elo   | 5.65 +- 4.97 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.92 (-2.25, 2.89) [0.00, 5.00]
Games | N: 8424 W: 1960 L: 1823 D: 4641
Penta | [32, 925, 2182, 1020, 53]
```

LTC pass

### 6.1.1
Cutnodes

```
Elo   | 1.90 +- 3.68 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 0.58 (-2.25, 2.89) [0.00, 5.00]
Games | N: 16808 W: 4176 L: 4084 D: 8548
Penta | [184, 1960, 4021, 2058, 181]

ELO: 1.9 +- 3.68 [-1.78, 5.58]
LLR: 3.17 [-4.0, 1.0] (-2.94, 2.94)
```

Merged for cutnode functionality, and passed non-regression

### 6.1.2
SIMD (AVX2 enabled only currently)

STC SPRT
```
Elo   | 23.57 +- 11.20 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.94 (-2.25, 2.89) [0.00, 5.00]
Games | N: 1890 W: 546 L: 418 D: 926
Penta | [14, 188, 432, 278, 33]
```

LTC Fixed games
```
Elo   | 22.23 +- 16.42 (95%)
Conf  | 40.0+0.40s Threads=1 Hash=128MB
Games | N: 798 W: 210 L: 159 D: 429
Penta | [3, 74, 199, 115, 8]
```

### 6.1.3
Negative Extensions on alpha condition in SE

```
Elo   | 4.71 +- 4.22 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.99 (-2.25, 2.89) [0.00, 5.00]
Games | N: 13132 W: 3404 L: 3226 D: 6502
Penta | [172, 1489, 3081, 1637, 187]
```


### 6.1.4
Move IIR after forward pruning

```
Elo   | 3.41 +- 3.35 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.89 (-2.25, 2.89) [0.00, 5.00]
Games | N: 20288 W: 5088 L: 4889 D: 10311
Penta | [196, 2400, 4810, 2485, 253]
```

### 6.1.5
New net named Solaris with four king buckets, and +~1B FENs for a total of ~2B FENs.
Arch of (768x4->768)x2->1x8

STC
```
Elo   | 19.32 +- 9.17 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.91 (-2.25, 2.89) [0.00, 4.00]
Games | N: 2916 W: 851 L: 689 D: 1376
Penta | [33, 291, 669, 411, 54]
```

LTC
```
Elo   | 34.71 +- 12.84 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.90 (-2.25, 2.89) [0.00, 4.00]
Games | N: 1416 W: 425 L: 284 D: 707
Penta | [3, 113, 348, 228, 16]
```

### 6.1.6
Fixed FRC bugs.
Issues were previously in movegen and NNUE handling in FRC.

No ELO change can be calculated as a fixed version cannot be tested against a broken version.

### 6.1.6
SPSA Tune at 160K Games, ~10K Iterations

20+0.2
```
Elo   | 14.78 +- 8.04 (95%)
SPRT  | 20.0+0.20s Threads=1 Hash=32MB
LLR   | 2.93 (-2.25, 2.89) [0.00, 4.00]
Games | N: 3292 W: 826 L: 686 D: 1780
Penta | [5, 330, 852, 438, 21]
https://antares2262.pythonanywhere.com/test/123/
```

40+0.4
```
Elo   | 20.06 +- 12.98 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.90 (-2.25, 2.89) [0.00, 8.00]
Games | N: 1266 W: 327 L: 254 D: 685
Penta | [0, 129, 312, 182, 10]
https://antares2262.pythonanywhere.com/test/124/
```

### 6.1.7
Use power of 2 sizes for the transposition table.
Speed gain patch with a small sample size test to ensure no regression

```
Elo   | 6.42 +- 7.90 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 1.14 (-2.25, 2.89) [0.00, 4.00]
Games | N: 3520 W: 868 L: 803 D: 1849
Penta | [24, 391, 868, 450, 27]
```

### 6.1.8 (7.0.0)
Use the TT value in place of the static evaluation when it is more accurate (Negamax only)

```
Elo   | 7.13 +- 5.30 (95%)
SPRT  | 20.0+0.20s Threads=1 Hash=128MB
LLR   | 2.91 (-2.25, 2.89) [0.00, 4.00]
Games | N: 7608 W: 1835 L: 1679 D: 4094
Penta | [34, 834, 1917, 980, 39]
https://antares2262.pythonanywhere.com/test/178/
```

### 7.0.1
Use QA = 255 while keeping int16 by switching order of operations

```
Elo   | 6.39 +- 5.20 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.00 (-2.94, 2.94) [0.00, 5.00]
Games | N: 8324 W: 2104 L: 1951 D: 4269
Penta | [73, 972, 1931, 1101, 85]
https://chess.swehosting.se/test/5579/
```

### 7.0.2
LMR changes

```
Elo   | 3.43 +- 3.40 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
Games | N: 19564 W: 4877 L: 4684 D: 10003
Penta | [173, 2248, 4754, 2427, 180]
https://chess.swehosting.se/test/5618/
```

### 7.0.3
Europa Net
Over 3.1B FENs, 5 king buckets, 768 HL

```
Elo   | 22.94 +- 10.97 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
Games | N: 1896 W: 528 L: 403 D: 965
Penta | [15, 172, 461, 273, 27]
https://chess.swehosting.se/test/5708/
```

### 7.0.4
Revamped Altair's time management

STC:
```
Elo   | 5.53 +- 4.84 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.03 (-2.94, 2.94) [0.00, 5.00]
Games | N: 9430 W: 2325 L: 2175 D: 4930
Penta | [66, 1020, 2401, 1154, 74]
https://chess.swehosting.se/test/6143/
```

LTC:
```
Elo   | 9.22 +- 6.94 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
Games | N: 4446 W: 1088 L: 970 D: 2388
Penta | [10, 445, 1202, 549, 17]
https://chess.swehosting.se/test/6148/
```

Cyclic TM:
```
Elo   | -2.39 +- 4.60 (95%)
SPRT  | 40/15.0+0.00s Threads=1 Hash=32MB
LLR   | -2.96 (-2.94, 2.94) [0.00, 5.00]
Games | N: 10026 W: 2268 L: 2337 D: 5421
Penta | [49, 1195, 2580, 1154, 35]
https://chess.swehosting.se/test/6167/
```

Although Cyclic TM did not gain, it had relatively smaller losses compared to the gains of STC and LTC, 
and is relatively unimportant in general.

### 7.0.5
New 1024 HL Net: Ceres

LTC
```
Elo   | 4.44 +- 3.27 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
Games | N: 12040 W: 3028 L: 2874 D: 6138
Penta | [48, 1372, 3053, 1472, 75]
https://chess.swehosting.se/test/6858/
```

STC
```
Elo   | 8.52 +- 5.19 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.98 (-2.94, 2.94) [0.00, 5.00]
Games | N: 6078 W: 1667 L: 1518 D: 2893
Penta | [72, 682, 1410, 775, 100]
https://chess.swehosting.se/test/6856/
```

### 7.0.6
Qsearch TT eval

```
Elo | 3.91 +- 3.02 (95%)
SPRT | 8.0+0.08s Threads=1 Hash=32MB
LLR | 2.95 (-2.94, 2.94) [0.00, 5.00]
Games | N: 15654 W: 3901 L: 3725 D: 8028
Penta | [138, 1764, 3846, 1942, 137]
https://chess.swehosting.se/test/7002/
```

### 7.0.7
Pawn key indexed correction history

```
Elo   | 3.52 +- 2.77 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
Games | N: 18246 W: 4509 L: 4324 D: 9413
Penta | [130, 2129, 4441, 2272, 151]
https://chess.swehosting.se/test/7063/
```

### 7.0.8
Pawn key fixed
Merged for being relatively equal at high game count while being a bug that is imperative to fix.

```
Elo   | -0.61 +- 3.33 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 0.12 (-2.94, 2.94) [-4.00, 1.00]
Games | N: 10304 W: 2417 L: 2435 D: 5452
Penta | [34, 1157, 2773, 1169, 19]
https://chess.swehosting.se/test/7091/
```

### 7.0.9
Qsearch pawn correction history

```
Elo   | 3.51 +- 2.77 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
Games | N: 18980 W: 4776 L: 4584 D: 9620
Penta | [179, 2173, 4589, 2375, 174]
https://chess.swehosting.se/test/7139/
```

### 7.1.0
Squared depth correction history

```
Elo   | 2.70 +- 2.16 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.99 (-2.94, 2.94) [0.00, 5.00]
Games | N: 29710 W: 7330 L: 7099 D: 15281
Penta | [228, 3452, 7241, 3729, 205]
https://chess.swehosting.se/test/7145/
```

### 7.1.1
Multicut use return eval

```
Elo   | 3.95 +- 3.04 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
Games | N: 15674 W: 3943 L: 3765 D: 7966
Penta | [120, 1865, 3705, 2011, 136]
https://chess.swehosting.se/test/7169/
```

### 7.1.2
SPSA tune at 6K iterations.

STC
```
Elo   | 12.29 +- 6.29 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.96 (-2.94, 2.94) [0.00, 5.00]
Games | N: 3678 W: 946 L: 816 D: 1916
Penta | [22, 407, 871, 497, 42]
https://chess.swehosting.se/test/7407/
```

LTC
```
Elo   | 2.38 +- 2.81 (95%)
SPRT  | 60.0+0.60s Threads=1 Hash=128MB
LLR   | 1.38 (-2.94, 2.94) [0.00, 5.00]
Games | N: 14734 W: 3547 L: 3446 D: 7741
Penta | [34, 1658, 3883, 1757, 35]
https://chess.swehosting.se/test/7409/
```

### 7.1.3
Hand-tuned values

```
Elo   | 4.50 +- 3.26 (95%)
SPRT  | 40.0+0.40s Threads=1 Hash=128MB
LLR   | 2.95 (-2.94, 2.94) [0.00, 5.00]
Games | N: 11110 W: 2719 L: 2575 D: 5816
Penta | [26, 1232, 2905, 1356, 36]
https://chess.swehosting.se/test/7421/
```

### 7.1.4
history depth bonus

```
Elo   | 5.61 +- 3.85 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 3.01 (-2.94, 2.94) [0.00, 5.00]
Games | N: 9422 W: 2323 L: 2171 D: 4928
Penta | [73, 1044, 2330, 1186, 78]
https://chess.swehosting.se/test/7457/
```

### 7.1.5
tt-pv

```
Elo   | 6.22 +- 4.14 (95%)
SPRT  | 8.0+0.08s Threads=1 Hash=32MB
LLR   | 2.97 (-2.94, 2.94) [0.00, 5.00]
Games | N: 8048 W: 2067 L: 1923 D: 4058
Penta | [43, 927, 1968, 1015, 71]
https://chess.swehosting.se/test/7467/
```
