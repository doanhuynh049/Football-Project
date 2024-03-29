# Makefile for a simple C++ project
#
# Compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -Iinclude 

# Linker flags
LDFLAGS = -lsqlite3 -lSQLiteCpp

# Directory
SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = obj

# Name of the output executable
TARGET = $(BINDIR)program

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)
	./$(TARGET)
	
# Linking the executable from the object files
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)
	
# Compiling the source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) $(OBJDIR)/*.o $(BINDIR)/*

.PHONY: all clean
