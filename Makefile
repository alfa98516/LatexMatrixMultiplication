# cpp files
MAIN = main.cpp

# hpp files
MATRIX = Matrix.hpp 

# out files 
TARGET = matrix 

# CXX flags
STD = -std=c++17
WARNINGS = -Wpedantic
SANITIZE = -fsanitize=undefined
SYMBOLS = -g 
CC = g++
CXXFLAGS = $(SYMBOLS) $(WARNINGS) $(STD) $(SANITIZE)

all: $(TARGET)

$(TARGET) : $(MAIN) $(MATRIX) 
	$(CC) $(CXXFLAGS) -o $@ $(MAIN)

clean:
	rm -f $(TARGET)


.PHONY: all clean

