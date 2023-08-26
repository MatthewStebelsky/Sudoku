#include <iostream>
#include <cstdlib>
#include <ctime>
#include "solver.hpp"
#include "altproj.hpp"

using namespace std;
using namespace arma;

int main(int argc, char **argv) {
  
  srand(time(NULL));
  int puzzleSize = 16;
  Board initialBoard = generatePuzzle(puzzleSize, 20);
  cout << "Starting puzzle:\n";
  // initialBoard.printPuzzle();
  // cout << "\n==================================\n";

  Board solvedBoard = solveSudokuDR(initialBoard);

  bool isSolved = solvedBoard.checkPuzzle();
  if (!isSolved)
    cout << "DR Failed to Solve" << endl;
  else
    solvedBoard.printPuzzle();
  
  // cout << "\n==================================\n";

  // solveSudoku(initialBoard, 0, 0);
  // initialBoard.printPuzzle();
  
}
