

EXE      = Altair
OBJECTS	:= evaluation.o main.o move.o perft.o position.o search.o useful.o uci.o bench.o
SOURCES	:= evaluation.cpp main.cpp move.cpp perft.cpp position.cpp search.cpp useful.cpp uci.cpp bench.cpp
HEADERS	:= constants.h evaluation.h move.h perft.h position.h search.h useful.h uci.h zobrist.h bench.h

TEMPDIR := tmp/
FLAGS    = -O3
CXXFLAGS   = -std=c++17

CXX	    := g++
SUFFIX  :=

# engine name
NAME    := Altair

# Detect Windows
ifeq ($(OS), Windows_NT)
	SUFFIX  := .exe
	CXXFLAGS += -static

endif

OUT	:= $(NAME)$(SUFFIX)

all: $(EXE)


$(EXE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(OBJECTS)

clean:
	rm -rf *.o
#$(EXE): $(OBJECTS)
#	$(CXX) $(CXXFLAGS) $^ -c -o $(OUT)

#-include $(HEADERS)

#%.o : $(SOURCES)
#		$(CXX) $(CXXFLAGS) $(FLAGS) $^ -o $(OUT)

