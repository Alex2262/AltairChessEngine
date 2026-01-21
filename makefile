
# engine name
EXE      = Altair

SOURCES      := src/evaluation_classic.cpp src/main.cpp src/move.cpp src/perft.cpp src/position.cpp src/search.cpp \
				src/useful.cpp src/uci.cpp src/bench.cpp src/see.cpp src/bitboard.cpp src/move_ordering.cpp \
				src/datagen.cpp src/nnue.cpp src/timeman.cpp

TEST_SOURCES 	   := tests/maxheap_test.cpp
ENGINE_LIB_SOURCES := $(filter-out src/main.cpp, $(SOURCES))

CXXFLAGS     := -O3 -std=c++20 -march=native -Wall -Wextra -pedantic -DNDEBUG -flto
TEST_CXXFLAGS := -O0 -g -std=c++20 -Wall -Wextra -pedantic

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
TEST_OUT := tests/heap_test$(SUFFIX)

make:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)

pgo:
ifeq ($(PGO), true)
	$(CXX) $(CXXFLAGS) -fprofile-instr-generate -o $(OUT) $(SOURCES)

ifeq ($(OS), Windows_NT)
	$(OUT) bench 20
else
	./$(OUT) bench 20
endif

	$(LLVM_PROF_CMD) merge -output="Altair.profdata" *.profraw
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES) -fprofile-instr-use="Altair.profdata"
	rm "Altair.profdata"
	rm *.profraw

else
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES)
endif

tests: $(TEST_OUT)
$(TEST_OUT):
	$(CXX) $(TEST_CXXFLAGS) -o $(TEST_OUT) $(TEST_SOURCES) $(ENGINE_LIB_SOURCES)

test: $(TEST_OUT)
	./$(TEST_OUT)

clean:
	rm -rf *.o

