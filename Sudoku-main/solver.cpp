/*
Implementation of the backtracking algorithm and other game-play mechanics
*/

#include "solver.hpp"
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

void Board::printPuzzle() {
    int blockSize = static_cast<int>(sqrt(N));
    int extraSpace = N / 10;

    for(int i = 0; i < N; i++) {
        cout << "+---";
        for(int j = 0; j < extraSpace; j++)
            cout << "-";
    }

    cout << "+" << endl;

    for(int i = 0; i < N; i++) {
        cout << "| ";
        for(int j = 0; j < N; j++) {

            if (puzzle[i][j] == 0) {
                cout << ".";
                for(int k = 0; k < extraSpace; k++)
                    cout << " ";
            } else {
                if (!immutable[i][j]) {
                    cout << puzzle[i][j];
                } else {
                    cout << "\033[31m" << puzzle[i][j] << "\033[39m";
                }

                int numDigits = puzzle[i][j] / 10;
                while (numDigits < extraSpace) {
                    cout << " ";
                    numDigits++;
                }
            }

            if ((j + 1) % blockSize == 0) {
                cout << " | ";
            } else {
                cout << "   ";
            }
        }

        cout << endl;
        if ((i + 1) % blockSize == 0) {
            for(int j = 0; j < N; j++) {
                cout << "+---";

                for(int k = 0; k < extraSpace; k++)
                    cout << "-";
            }

            cout << "+" << endl;
        }
    }
}

bool Board::checkPuzzle() {
    int val = 0;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) {
            val = puzzle[i][j];
            puzzle[i][j] = 0;
            if (!feasible(*this, i, j, val)) {
                puzzle[i][j] = val;
                return false;
            }
            puzzle[i][j] = val;
        }
    return true;
}

void Board::clearPuzzle() {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if (!immutable[i][j])
                puzzle[i][j] = 0;
}

bool Board::inBounds(int val) {
    if ((val > 0) && (val <= N)) {
        return true;
    } else {
        return false;
    }
}

bool Board::feasibleUser(int row, int col, int val) {
    int blockSize = static_cast<int>(sqrt(N));

    if (row >= N) {
        std::cout << "You can't play off the game board!" << endl;
        return false;
    }

    if (col >= N) {
        std::cout << "You can't play off the game board!" << endl;
        return false;
    }

    bool isFeasible = true;

    for(int i = 0; i < N; i++) {
        if (puzzle[row][i] == val) {
            infeasible[row][i] = true;
            isFeasible = false;
        } else {
            infeasible[row][i] = false;
        }
    }

    for(int i = 0; i < N; i++) {
        if (puzzle[i][col] == val) {
            infeasible[i][col] = true;
            isFeasible = false;
        } else {
            infeasible[i][col] = false;
        }
    }

    int blockRow = blockSize * (row / blockSize);
    int blockCol = blockSize * (col / blockSize);

    for(int i = 0; i < blockSize; i++) {
        for(int j = 0; j < blockSize; j++) {
            if (puzzle[blockRow + i][blockCol + j] == val) {
                infeasible[blockRow + i][blockCol + j] = true;
                isFeasible = false;
            } else {
                infeasible[blockRow + i][blockCol + j] = false;
            }
        }
    }
    return isFeasible;
}

bool feasible(Board &board, int row, int col, int val) {
    int N = board.getSize();
    assert(row < N);
    assert(col < N);
    int blockSize = static_cast<int>(sqrt(N));

    for(int j = 0; j < N; j++)
        if (board(row, j) == val) return false;

    for(int i = 0; i < N; i++)
        if (board(i, col) == val) return false;

    int blockRow = blockSize * (row / blockSize);
    int blockCol = blockSize * (col / blockSize);

    for(int i = 0; i < blockSize; i++)
        for(int j = 0; j < blockSize; j++)
            if (board(blockRow + i, blockCol + j) == val)
                return false;

    return true;
}

bool solve(Board &board, int row, int col) {
    int N = board.getSize();
    assert(N == pow(sqrt(N), 2));

    if (row == N)
        return true;

    if (board(row, col) != 0) {
        if (col == (N - 1)) {
            if (solve(board, row + 1, 0)) return true;
        } else {
            if (solve(board, row, col + 1)) return true;
        }
        return false;
    }

    for(int val = 1; val <= N; val++) {
        if (feasible(board, row, col, val)) {
            board(row, col) = val;
            if (col == (N - 1)) {
                if (solve(board, row + 1, 0)) return true;
            } else {
                if (solve(board, row, col + 1)) return true;
            }
        }
    }

    board(row, col) = 0;
    return false;
}

Board generatePuzzle(int N, int nobs) {
    assert(nobs <= N * N);
    Board board(N);

    int* perm = genPerm(N);
    for(int i = 0; i < N; i++)
        board(i, i) = perm[i];
    delete[] perm;

    bool isSolved = solve(board, 0, 0);
    assert(isSolved);

    perm = genPerm(N * N);
    int x, y;
    for(int i = 0; i < (N * N - nobs); i++) {
        x = (perm[i] - 1) / N;
        y = (perm[i] - 1) % N;
        board(x, y) = 0;
        board.assignImmutable(x, y, false);
    }

    delete[] perm;
    return board;
}

int* genPerm(int N) {
    int *x = new int[N];
    for(int i = 0; i < N; i++)
        x[i] = i + 1;

    int rindex;
    int temp;
    for(int i = (N - 1); i > 0; i--) {
        rindex = rand() % (i + 1);
        temp = x[i];
        x[i] = x[rindex];
        x[rindex] = temp;
    }

    return x;
}
