/*

Function declarations for Douglas Rachford splitting to solve sudoku puzzle

*/

#pragma once
#include "solver.hpp"
#include <armadillo>

constexpr double TOL = 1e-7;
constexpr double MAXITS = 1e4;

// Reflection operators that make up the iterations in the DR splitting procedure
arma::cube projectRows(const arma::cube& inputCube);
arma::cube projectColumns(const arma::cube& inputCube);
arma::cube projectBlocks(const arma::cube& inputCube);
arma::cube projectUniqueness(const arma::cube& inputCube);
arma::cube projectGivenConfig(const arma::cube& inputCube, Board& board);
Board cubeToBoard(const arma::cube& inputCube);

// Douglas-Rachford splitting operator (i.e., solves the puzzle)
Board solveSudokuDR(Board& board);
