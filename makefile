
# engine name
EXE      = Altair

SOURCES      := src/evaluation.cpp src/main.cpp src/move.cpp src/perft.cpp src/position.cpp src/search.cpp \
				src/useful.cpp src/uci.cpp src/bench.cpp src/see.cpp src/bitboard.cpp src/move_ordering.cpp \
				src/datagen.cpp src/nnue.cpp src/timeman.cpp

CXXFLAGS     := -O3 -std=c++20 -march=native -Wall -Wextra -pedantic -DNDEBUG -flto

CXX          := clang++
SUFFIX       :=

PGO := true

LLVM_PROF_CMD = llvm-profdata

ifeq ($(native),1)
    CXXFLAGS += -march=native

    ifeq (,$(shell where llvm-profdata))
    	override PGO := off
    endif
endif

# Detect Windows
ifeq ($(OS), Windows_NT)
    SUFFIX   := .exe
    CXXFLAGS += -static
    CXXFLAGS += -fuse-ld=lld
else

    DETECTED_OS := $(shell uname -s)
    ifneq (,$(findstring clang,$(shell $(CXX) --version)))
        ifneq ($(DETECTED_OS), Darwin)
            CXXFLAGS += -fuse-ld=lld

            ifeq (,$(shell which llvm-profdata))
              	override PGO := false
            endif
        else
            LLVM_PROF_CMD = xcrun llvm-profdata
        endif
    else
    	override PGO := false
    endif
	CXXFLAGS += -pthread

endif

OUT := $(EXE)$(SUFFIX)


make:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)

clean:
	rm -rf *.o
