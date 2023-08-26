# Sudoku Game in C++
## Program Usage
To start the Sudoku game, compile it using the provided makefile and run the executable "sudoku".

The game starts in interactive mode with a 9x9 grid.
To fill in a cell, input the column number, row number, and the desired value (1-based index). You can separate these values using spaces, commas, or any other delimiter (except an integer).
You can enter "Solve" at any time to have the backtracking solver solve the game based on your current progress.
If you find yourself in an impossible configuration, the game will prompt you to clear the board first.
After solving the puzzle, you'll be asked if you want to play again.
Command Line Flags
You can configure the game using command line flags:

-s or --seed: Set a specific random seed to replicate results.
-u or --Unittest: Run unit (speed) tests with both solvers. Specify the number of test repetitions.
-g or --gamesize: Specify the game size, e.g., 9 for a 9x9 game or 16 for a 16x16 game.
-n or --nobs: Specify the number of pre-filled values (immutable cells) in the puzzle.
-v or --verbose: Add this flag for verbose output after each unit test. No effect in interactive mode.

## Build Instructions
The build process requires the armadillo library, which can be downloaded from the website: http://arma.sourceforge.net/.

## Notes
Puzzles are generated using a reverse backtracking approach, filling in the diagonal using a random permutation, solving the puzzle, and then removing cells. Generating the puzzle might take longer than solving it, especially for larger puzzles. The unit test measures only the solver function.
In the speed test during the class demo, the first puzzle took significantly longer to solve for the backtracking solver than the other puzzles. This could be attributed to the constant random seed, as solving times for the backtracking solver exhibit variability. The Alternating Projections approach seems to be less variable for a given puzzle configuration.


## References
Pseudo-code for the backtracking algorithm:

http://moritz.faui2k3.org/en/yasss
Idea to use Douglas-Rachford splitting to solve Sudoku:

"Recent Results on Douglas–Rachford Methods for Combinatorial Optimization Problems"
Function timing code:

http://stackoverflow.com/questions/29719999/testing-function-for-speed-performance-in-cpp
