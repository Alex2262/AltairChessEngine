# cd cutechess dir
cd "C:\Users\Alex Tian\AppData\Local\Programs\Cute Chess"

# Opening Books
SUITE_1="C:\Users\Alex Tian\Documents\UHO_XXL_+0.90_+1.19.pgn"

# Test Variables
TEST_OPENING_BOOK=$SUITE_1
TIME_CONTROL=1+0.02
CONCURRENCY=4

./cutechess-cli \
    -engine conf=Altair1.4.2 \
    -engine conf=Altair1.4.1 \
    -repeat 2 \
    -recover \
    -each tc=$TIME_CONTROL \
    -openings file="$TEST_OPENING_BOOK" format=pgn order=random \
    -concurrency $CONCURRENCY \
    -resultformat wide2 \
    -ratinginterval 20 \
    -games 50000 \
    -draw movenumber=150 movecount=3 score=100 \
    -sprt elo0=0 elo1=10 alpha=0.05 beta=0.05 \
    -pgnout "$TEST_ROOT\\$TEST_NAME\\test.pgn" \

