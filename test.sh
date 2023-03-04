# cd cutechess dir
cd "C:\Users\Alex Tian\AppData\Local\Programs\Cute Chess"

# Engine Paths and Names
ENGINE_NEW_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.3.6.exe"
ENGINE_OLD_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.3.5.exe"

ENGINE_3_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.2.4.exe"
ENGINE_4_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.2.6.exe"
ENGINE_5_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.2.7.exe"
ENGINE_6_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.2.8.exe"
ENGINE_7_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.2.9.exe"
ENGINE_8_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.3.0.exe"
ENGINE_9_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.3.1.exe"
ENGINE_10_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.3.2.exe"
ENGINE_11_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.3.3.exe"
ENGINE_12_PATH="C:\Users\Alex Tian\Documents\ChessEngines\Altair1.3.4.exe"

ENGINE_NEW_NAME=Altair1.3.6
ENGINE_OLD_NAME=Altair1.3.5

ENGINE_3_NAME=Altair1.2.4
ENGINE_4_NAME=Altair1.2.6
ENGINE_5_NAME=Altair1.2.7
ENGINE_6_NAME=Altair1.2.8
ENGINE_7_NAME=Altair1.2.9
ENGINE_8_NAME=Altair1.3.0
ENGINE_9_NAME=Altair1.3.1
ENGINE_10_NAME=Altair1.3.2
ENGINE_11_NAME=Altair1.3.3
ENGINE_12_NAME=Altair1.3.4

# Opening Books
SUITE_1="C:\Users\Alex Tian\Documents\UHO_XXL_+0.90_+1.19.pgn"

# Testing Folder
TEST_ROOT="C:\Users\Alex Tian\Documents\EngineTests"

# Test Name
TEST_NAME=test1

# Test Variables
ENGINE_1=($ENGINE_NEW_NAME "$ENGINE_NEW_PATH")
ENGINE_2=($ENGINE_OLD_NAME "$ENGINE_OLD_PATH")

ENGINE_3=($ENGINE_3_NAME "$ENGINE_3_PATH")
ENGINE_4=($ENGINE_4_NAME "$ENGINE_4_PATH")
ENGINE_5=($ENGINE_5_NAME "$ENGINE_5_PATH")
ENGINE_6=($ENGINE_6_NAME "$ENGINE_6_PATH")
ENGINE_7=($ENGINE_7_NAME "$ENGINE_7_PATH")
ENGINE_8=($ENGINE_8_NAME "$ENGINE_8_PATH")
ENGINE_9=($ENGINE_9_NAME "$ENGINE_9_PATH")
ENGINE_10=($ENGINE_10_NAME "$ENGINE_10_PATH")
ENGINE_11=($ENGINE_11_NAME "$ENGINE_11_PATH")
ENGINE_12=($ENGINE_12_NAME "$ENGINE_12_PATH")



TEST_OPENING_BOOK=$SUITE_1
TIME_CONTROL=2+0.02
CONCURRENCY=4

echo $TEST_ROOT

mkdir -p "C:\Users\Alex Tian\Documents\EngineTests\test1"

echo Engine 1 Name ${ENGINE_1[0]}
echo Engine 1 Path ${ENGINE_1[1]}
echo Engine 2 Name ${ENGINE_2[0]}
echo Engine 2 Path ${ENGINE_2[1]}


./cutechess-cli \
    -engine name=${ENGINE_1[0]} proto=uci cmd="${ENGINE_1[1]}" \
    -engine name=${ENGINE_2[0]} proto=uci cmd="${ENGINE_2[1]}" \
    -repeat -each tc=$TIME_CONTROL \
    -openings file="$TEST_OPENING_BOOK" format=pgn order=random \
    -concurrency $CONCURRENCY -ratinginterval 20 -games 50000 \
    -draw movenumber=150 movecount=3 score=100 \
    -sprt elo0=0 elo1=10 alpha=0.05 beta=0.05 \
    -pgnout "$TEST_ROOT\\$TEST_NAME\\test.pgn" \
    -recover \


    # -debug \



: '
./cutechess-cli \
    -engine name=${ENGINE_1[0]} proto=uci cmd="${ENGINE_1[1]}" \
    -engine name=${ENGINE_2[0]} proto=uci cmd="${ENGINE_2[1]}" \
    -engine name=${ENGINE_3[0]} proto=uci cmd="${ENGINE_3[1]}" \
    -engine name=${ENGINE_4[0]} proto=uci cmd="${ENGINE_4[1]}" \
    -engine name=${ENGINE_5[0]} proto=uci cmd="${ENGINE_5[1]}" \
    -engine name=${ENGINE_6[0]} proto=uci cmd="${ENGINE_6[1]}" \
    -engine name=${ENGINE_7[0]} proto=uci cmd="${ENGINE_7[1]}" \
    -engine name=${ENGINE_8[0]} proto=uci cmd="${ENGINE_8[1]}" \
    -engine name=${ENGINE_9[0]} proto=uci cmd="${ENGINE_9[1]}" \
    -engine name=${ENGINE_10[0]} proto=uci cmd="${ENGINE_10[1]}" \
    -engine name=${ENGINE_11[0]} proto=uci cmd="${ENGINE_11[1]}" \
    -engine name=${ENGINE_12[0]} proto=uci cmd="${ENGINE_12[1]}" \
    -repeat -each tc=$TIME_CONTROL \
    -openings file="$TEST_OPENING_BOOK" format=pgn order=random \
    -concurrency $CONCURRENCY -ratinginterval 20 -rounds 10000 \
    -draw movenumber=150 movecount=3 score=100 \
    -resultformat wide                         \
    -pgnout "$TEST_ROOT\\$TEST_NAME\\test.pgn" \
    -recover \


    # -debug \
'