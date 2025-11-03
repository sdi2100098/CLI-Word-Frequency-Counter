# Makefile - build WordCount, BigFileGen, tests, and helper targets

# Compiler / flags
CXX      := g++
CXXFLAGS := -mavx2 -Wall -std=c++17 -lstdc++ -O3 -fopenmp -IInclude
# You can add debug flags for local dev:
# DEBUGFLAGS := -g -O0 -fsanitize=address,undefined
# CXXFLAGS := $(CXXFLAGS) $(DEBUGFLAGS)

# Directories / targets
TARGET1    := WordCount
OBJ_DIR    := obj
BIN_DIR    := bin
SRC_DIR    := Src
UTILS_DIR  := Utils
TEST_DIR   := Test

# Sources
SRC := $(SRC_DIR)/WordCounter.cpp \
       $(SRC_DIR)/HelperFunc.cpp

TEST_SRC := $(TEST_DIR)/UnitTests.cpp

# Objects (map Src/*.cpp -> obj/*.o)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Big file generator
BIGFILE_SRC    := $(UTILS_DIR)/BigFileGen.cpp
BIGFILE_TARGET := $(BIN_DIR)/BigFileGen

# Default target: build product binary
.PHONY: all
all: $(BIN_DIR)/$(TARGET1)

# Build main product executable
$(BIN_DIR)/$(TARGET1): $(SRC_DIR)/main.cpp $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_DIR)/main.cpp $(OBJ)
	@echo "Built $@"

# Build object files from Src/*.cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

# Big file generator: built standalone (contains its own main)
.PHONY: biggen $(BIGFILE_TARGET) gen
$(BIGFILE_TARGET): $(BIGFILE_SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(BIGFILE_SRC)
	@echo "Built $@"

# Run the product executable with optional ARGS
# Usage: make run ARGS="input.txt out.txt 100"
.PHONY: run
run: $(BIN_DIR)/$(TARGET1)
	@echo "Executing: ./$(BIN_DIR)/$(TARGET1) $(ARGS)"
	@./$(BIN_DIR)/$(TARGET1) $(ARGS)

# Run the bigfile generator
# Usage: make gen ARGS="--output corpus.txt --size-mb 200 --mode random"
.PHONY: gen
gen: $(BIGFILE_TARGET)
	@echo "Running bigfile generator: ./$(BIGFILE_TARGET) $(ARGS)"
	@./$(BIGFILE_TARGET) $(ARGS)

# Build and run unit tests
.PHONY: test
test: $(TEST_SRC) $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/test_executable $(TEST_SRC) $(OBJ)
	@echo "Running tests..."
	@./$(BIN_DIR)/test_executable

# Valgrind targets
.PHONY: valgrind_test
valgrind_test: test
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN_DIR)/test_executable

.PHONY: valgrind
valgrind: $(BIN_DIR)/$(TARGET1)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN_DIR)/$(TARGET1) $(ARGS)

# Clean generated files
.PHONY: clean
clean:
	@echo "Cleaning $(OBJ_DIR) and $(BIN_DIR)"
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
