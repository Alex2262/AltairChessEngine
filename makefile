
# engine name
EXE      = Altair

SOURCES      := src/evaluation.cpp src/main.cpp src/move.cpp src/perft.cpp src/position.cpp src/search.cpp \
				src/useful.cpp src/uci.cpp src/bench.cpp src/see.cpp src/bitboard.cpp src/move_ordering.cpp \
				src/datagen.cpp

CXXFLAGS     := -O3 -std=c++20 -Wall -Wextra -pedantic -DNDEBUG -flto

CXX          := clang++
SUFFIX       :=

ifeq ($(native),1)
    CXXFLAGS += -march=native
endif

# Detect Windows
ifeq ($(OS), Windows_NT)
    SUFFIX   := .exe
    CXXFLAGS += -static

else
    DETECTED_OS := $(shell uname -s)
    ifneq (,$(findstring clang,$(shell $(CXX) --version)))
        ifneq ($(DETECTED_OS),Darwin)
            CXXFLAGS += -fuse-ld=lld
        endif
    endif
	CXXFLAGS += -pthread

endif

OUT := $(EXE)$(SUFFIX)

all: $(EXE)

$(EXE) : $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)

clean:
	rm -rf *.o