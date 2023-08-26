# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O3
LDFLAGS = -lm -larmadillo

# Object files
OBJ = solver.o altproj.o game.o tests.o

# Targets
all: sudoku debug

sudoku: main.cpp $(OBJ)
	$(CXX) main.cpp -o sudoku $(OBJ) $(CXXFLAGS) $(LDFLAGS)

debug: debug.cpp $(OBJ)
	$(CXX) debug.cpp -o debug $(OBJ) $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) sudoku debug
