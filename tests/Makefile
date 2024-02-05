CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -I../include -I/usr/local/include 
GTEST_LIBS = -L/usr/local/lib -lgtest -lgtest_main -pthread -ldl
LDFLAGS = -lsqlite3 -lSQLiteCpp

# Project directories
BASE_DIR = ../
SRC_DIR = $(BASE_DIR)src
INCLUDE_DIR = $(BASE_DIR)include
TEST_DIR = .
BIN_DIR = $(BASE_DIR)bin
OBJ_DIR = $(BASE_DIR)obj

# Executable targets
MAIN_TARGET = $(BIN_DIR)/program
TEST_TARGET = $(BIN_DIR)/team_test

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_FILES))

MACRO := -DUNIT_TEST
CXXFLAGS += $(UNIT_TEST)
# Default target
all: $(TEST_TARGET)
	./$(TEST_TARGET)
# Rule for creating the test executable
$(TEST_TARGET): $(filter-out $(OBJ_DIR)/Main.o, $(OBJ_FILES)) $(TEST_OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(GTEST_LIBS) 

# Object file generation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*
