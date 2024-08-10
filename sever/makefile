# Compiler
CXX = g++

# C++ version 
VERSION = -std=c++17

# Compiler flags
CXXFLAGS = -I./include

# Linker flags
LDFLAGS = -lws2_32

# Source directories
SRC_DIR = source
# SRC_SORT_DIR = source

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
# $(wildcard $(SRC_SORT_DIR)/*.cpp)

# Output executable
TARGET = sever

# Main file
MAIN = main.cpp

# Build rule
$(TARGET): $(MAIN) $(SRC_FILES)
	$(CXX) $(CXXFLAGS) $(VERSION) -o $(TARGET) $(MAIN) $(SRC_FILES) $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET) main.exe
