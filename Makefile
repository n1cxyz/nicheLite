# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_mixer

# Directories and file names
SRC_DIR = src
BIN_DIR = bin
TARGET = game

# Source and object files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRC))

.PHONY: all clean fclean re

all: $(TARGET)

# Link the object files into the final binary
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile source files into bin/*.o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure bin directory exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Remove only object files
clean:
	rm -f $(OBJ)

# Remove object files and the final binary
fclean: clean
	rm -rf $(TARGET)

# Rebuild everything
re: fclean all


