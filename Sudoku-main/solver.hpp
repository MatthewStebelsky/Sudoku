/*

Implement Board class to hold the state of the sudoku game
*/
#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>

// Board class to hold the state of the sudoku game (parts of board implementation
// borrowed from lecture code)
class Board {
    int N;
    int **puzzle;
    bool **immutable;
    bool **infeasible;

public:

    // To be implemented as a matrix with a single array
    Board(int _N) : N(_N) {

        // Matrix to keep track of values
        puzzle = new int*[N];
        for(int i = 0; i < N; i++) {
            puzzle[i] = new int[N];
        }
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                puzzle[i][j] = 0;

        // Matrix to track immutables
        immutable = new bool*[N];
        for(int i = 0; i < N; i++) {
            immutable[i] = new bool[N];
        }

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                immutable[i][j] = true;

        // Matrix to track which values are causing infeasibility
        // these are problem cells that will be
        // highlighted in red during gameplay
        infeasible = new bool*[N];
        for(int i = 0; i < N; i++) {
            infeasible[i] = new bool[N];
        }

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                infeasible[i][j] = false;

    }

    // Destructor for the board
    ~Board() {
        for(int i = 0; i < N; i++) {
            delete [] puzzle[i];
        }
        delete [] puzzle;

        for(int i = 0; i < N; i++) {
            delete [] immutable[i];
        }
        delete [] immutable;

        for(int i = 0; i < N; i++) {
            delete [] infeasible[i];
        }
        delete [] infeasible;
    }

    void printPuzzle(); // Print the puzzle to the screen
    bool checkPuzzle(); // Check if the puzzle is complete
    void clearPuzzle(); // Clear mutables from the puzzle
    bool inBounds(int val); // Check if the value can exist in the puzzle
    bool feasibleUser(int row, int col, int val);

    // Operator overload to assign a value to a cell
    int& operator() (int x, int y) {
        assert(x < N && y < N);
        return puzzle[x][y];
    }

    // Operator overload to assign a value to a cell
    void assignValue(int x, int y, int val) {
        (*this)(x, y) = val;
    }

    // Toggle cell mutability
    void assignImmutable(int x, int y, bool val) {
        immutable[x][y] = val;
    }

    // Checks if a cell is immutable (not changeable by solve/user)
    bool checkImmutable(int x, int y) {
        return immutable[x][y];
    }

    // Keep track of "problem cells"
    // i.e. cells that cause infeasibility
    bool isProblem(int x, int y) {
        return infeasible[x][y];
    }

    // Get the size of the game
    // i.e. 9 for a 9x9 game
    int getSize() {
        return N;
    }

    // Function for debugging (kind of dumb, but need to change its
    // signature each time you change the puzzle size...but I suppose
    // in practice we will never need this)
    void setFromArray(int a[4][4]) {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                puzzle[i][j] = a[i][j];
    }

};

bool feasible(Board &b, int row, int col, int val);
bool solve(Board &b, int row, int col);
int* genPerm(int N);
Board generatePuzzle(int n, int nobs);
