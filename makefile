EXE      = Altair

SOURCES      := evaluation.cpp main.cpp move.cpp perft.cpp position.cpp search.cpp useful.cpp uci.cpp bench.cpp

TEMPDIR      := tmp/
CXXFLAGS     := -O3 -std=c++17

CXX          := g++
SUFFIX       :=

# engine name
NAME         := Altair

# Detect Windows
ifeq ($(OS), Windows_NT)
    SUFFIX   := .exe
    CXXFLAGS += -static
else
	CXXFLAGS += -pthread

endif

OUT := $(NAME)$(SUFFIX)

all: $(EXE)

$(EXE) : $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)

clean:
	rm -rf *.o