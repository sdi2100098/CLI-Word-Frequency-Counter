# C++ compiler we use
CXX = g++
CXXFLAGS = -mavx2 -Wall -std=c++17 -lstdc++ -O3 -fopenmp -IInclude

# Output filenames and directories
TARGET1 = WordCount
OBJ_DIR = obj
BIN_DIR = bin

# Source and test files
SRC = Src/WordCounter.cpp\
	  Src/HelperFunc.cpp
TEST_SRC = Test/UnitTests.cpp
OBJ = $(SRC:Src/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(BIN_DIR)/$(TARGET1)

# Build main executable
$(BIN_DIR)/$(TARGET1): Src/main.cpp $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ Src/main.cpp $(OBJ)

# Build object files
$(OBJ_DIR)/%.o: Src/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run executable with optional arguments
run: $(BIN_DIR)/$(TARGET1)
	@echo "Executing: ./$(BIN_DIR)/$(TARGET1) $(ARGS)"
	./$(BIN_DIR)/$(TARGET1) $(ARGS)

# Test
test: $(TEST_SRC) $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/test_executable $(TEST_SRC) $(OBJ)
	./$(BIN_DIR)/test_executable

# Valgrind
valgrind_test: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN_DIR)/test_executable

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
