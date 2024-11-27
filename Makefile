# Compiler and linker
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/warrior.cpp $(SRC_DIR)/boss.cpp $(SRC_DIR)/effect.cpp
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN = $(BIN_DIR)/warriors

# Targets
all: $(MAIN)

$(MAIN): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)  # Ensure the bin directory exists
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Ensure the obj directory exists
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(MAIN)
	./$(MAIN) $(ARGS)

.PHONY: all clean run

