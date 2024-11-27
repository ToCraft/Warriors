# Compiler and linker
CXX = g++
CXX_WIN := x86_64-w64-mingw32-g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -static

# Directories
SRC_DIR = src
BUIDL_DIR = build
BIN_DIR = bin

# Files
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/warrior.cpp $(SRC_DIR)/boss.cpp $(SRC_DIR)/effect.cpp
LINUX_BIN = $(BIN_DIR)/warriors
WINDOWS_BIN = $(BIN_DIR)/warriors.exe

# Targets
all: $(LINUX_BIN) $(WINDOWS_BIN)

$(LINUX_BIN):
	@mkdir -p $(BIN_DIR)  # Ensure the bin directory exists
	$(CXX) $(CXXFLAGS) -o $(LINUX_BIN) $(SRC_FILES)

$(WINDOWS_BIN):
	@mkdir -p $(BIN_DIR)
	$(CXX_WIN) $(CXXFLAGS) $(SRC_FILES) -o $(WINDOWS_BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(MAIN)
	./$(MAIN) $(ARGS)

.PHONY: all clean run

