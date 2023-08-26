/*

Code to implement Douglas Rachford splitting to solve sudoku puzzle
The idea to use DR to solve sudoku comes from the paper:
"Recent Results on Douglas–Rachford Methods for Combinatorial Optimization 
Problems"

*/

#include "altproj.hpp"
#include <iostream>
using namespace std;
using namespace arma;

// Project onto cubes that obey row constraints
cube projectRows(const cube& inputCube){

  int n = inputCube.n_rows;
  cube projectedCube(n, n, n, fill::zeros);
  uvec seq = linspace<uvec>(0, n - 1, n), ix(n), order(n);
  for(int i = 0; i < n; i++)
    for(int k = 0; k < n; k++){
      ix = k * n * n + n * seq + i;
      order = sort_index(inputCube.elem(ix), "descend");
      projectedCube(i, order(0), k) = 1;
    }
  return 2 * projectedCube - inputCube;
}

// Project onto cubes that obey column constraints
cube projectColumns(const cube& inputCube){
  int n = inputCube.n_rows;
  cube projectedCube(n, n, n, fill::zeros);
  uvec seq = linspace<uvec>(0, n - 1, n), ix(n), order(n);
  for(int j = 0; j < n; j++)
    for(int k = 0; k < n; k++){
      ix = k * n * n + j * n + seq;
      order = sort_index(inputCube.elem(ix), "descend");
      projectedCube(order(0), j, k) = 1;
    }
  return 2 * projectedCube - inputCube;
}

// Project onto cubes that obey block constraints
cube projectBlocks(const cube& inputCube){
  int n = inputCube.n_rows;
  cube projectedCube(n, n, n, fill::zeros);
  int blockSize = sqrt(n);
  uvec mask(blockSize * blockSize);
  uvec ix(blockSize * blockSize), order;
  for(int i = 0; i < blockSize; i++)
    for(int j = 0; j < blockSize; j++)
      mask(i + blockSize * j) = i + n * j;

  for(int k = 0; k < n; k++)
    for(int i = 0; i < blockSize; i++)
      for(int j = 0; j < blockSize; j++){
        ix = mask + (i * blockSize + j * n * blockSize);
        order = sort_index(inputCube.elem(ix + k * n * n), "descend");
        projectedCube(ix(order(0)) + k * n * n) = 1;
      }
  return 2 * projectedCube - inputCube;
}

// Project onto cubes that obey uniqueness constraints
cube projectUniqueness(const cube& inputCube){
  int n = inputCube.n_rows;
  cube projectedCube(n, n, n, fill::zeros);
  uvec seq = linspace<uvec>(0, n - 1, n), ix(n), order(n);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
      ix = seq * n * n + j * n + i;
      order = sort_index(inputCube.elem(ix), "descend");
      projectedCube(i, j, order(0)) = 1;
    }
  return 2 * projectedCube - inputCube;
}

// Project onto cubes that agree with the given sudoku configuration
cube projectGivenConfig(const cube& inputCube, Board& board){
  int n = inputCube.n_rows;
  cube projectedCube = inputCube;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(board(i, j) != 0)
        projectedCube(i, j, board(i, j) - 1) = 1;
  return 2 * projectedCube - inputCube;
}

// Convert a cube to a board by filling board(i, j) with the index
// of the largest index of inputCube(i, j, :)
Board cubeToBoard(const cube& inputCube){
  int n = inputCube.n_rows;
  Board solvedBoard(n);
  uword ix;
  vec A;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++){
      A = inputCube.tube(i, j);
      A.max(ix);
      solvedBoard(i, j) = (int)ix + 1;
    }
  return solvedBoard;
}

// Perform Douglas-Rachford iterations to solve sudoku board
Board solveSudokuDR(Board& board){
  int n = board.getSize();
  double err;
  cube X1(n, n, n, fill::zeros),
       X2(n, n, n, fill::zeros),
       X3(n, n, n, fill::zeros),
       X4(n, n, n, fill::zeros),
       X5(n, n, n, fill::zeros),
       Z(n, n, n, fill::zeros);

  for(int i = 0; i < MAXITS; i++){

    Z = (X1 + X2 + X3 + X4 + X5) / 5;

    if(i % 50 == 0 ){
      err = accu(abs(Z - projectRows(Z))) + accu(abs(Z - projectColumns(Z))) +
            accu(abs(Z - projectBlocks(Z))) + accu(abs(Z - projectUniqueness(Z))) +
            accu(abs(Z - projectGivenConfig(Z, board)));
      if(err < TOL){
        //cout << i << endl;
        return cubeToBoard(Z);
      }
    }

    X1 = X1 / 2 + projectRows(2 * Z - X1) / 2;
    X2 = X2 / 2 + projectColumns(2 * Z - X2) / 2;
    X3 = X3 / 2 + projectBlocks(2 * Z - X3) / 2;
    X4 = X4 / 2 + projectUniqueness(2 * Z - X4) / 2;
    X5 = X5 / 2 + projectGivenConfig(2 * Z - X5, board) / 2;

  }

  return cubeToBoard(Z);
}
