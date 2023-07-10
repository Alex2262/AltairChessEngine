
# engine name
EXE      = Altair

SOURCES      := evaluation.cpp main.cpp move.cpp perft.cpp position.cpp search.cpp useful.cpp uci.cpp bench.cpp see.cpp bitboard.cpp \
				move_ordering.cpp

TEMPDIR      := tmp/
CXXFLAGS     := -O3 -std=c++20 -Wall -Wextra -pedantic -DNDEBUG -flto

CXX          := clang++
SUFFIX       :=

# Detect Windows
ifeq ($(OS), Windows_NT)
    SUFFIX   := .exe
    CXXFLAGS += -static
    CXXFLAGS += -fuse-ld=lld
else
	CXXFLAGS += -pthread

endif

OUT := $(EXE)$(SUFFIX)

all: $(EXE)

$(EXE) : $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)

clean:
	rm -rf *.o