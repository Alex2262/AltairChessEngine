
# engine name
EXE      = Altair

SOURCES      := src/evaluation.cpp src/main.cpp src/move.cpp src/position.cpp src/search.cpp \
				src/useful.cpp src/uci.cpp src/see.cpp src/bitboard.cpp src/move_ordering.cpp \
				src/timeman.cpp

CXXFLAGS     := -O3 -mno-avx512f -std=c++20 -DNDEBUG -flto -ffunction-sections \
				-fdata-sections -fvisibility=hidden -fno-rtti -fno-exceptions -g0 -fmerge-all-constants -fshort-enums \
				-fomit-frame-pointer -fno-asynchronous-unwind-tables -falign-functions=1 -fno-ident

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
            ifeq (,$(shell which llvm-profdata))
              	override PGO := false
            endif
        else
            LLVM_PROF_CMD = xcrun llvm-profdata
        endif
    else
    	override PGO := false
    endif

endif

OUT := $(EXE)$(SUFFIX)


make:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)

clean:
	rm -rf *.o
