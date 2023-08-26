/*
File to implement gameplay
*/

#include <iostream>
#include <regex>
#include <sstream>
#include "game.hpp"
#include "solver.hpp"
#include "altproj.hpp"

using namespace std;

void playGame(int puzzleSize, int numberOfBlanks);

// Prompt to play the game again
void playAgainPrompt(int puzzleSize, int numberOfBlanks) {
    string userResponse;

    do {
        cout << "Would you like to play again? y/n" << endl;
        getline(cin, userResponse);
    } while ((userResponse != "y") && (userResponse != "n"));

    if (userResponse == "y") {
        playGame(puzzleSize, numberOfBlanks);
    } else {
        return;
    }
}

void playGame(int puzzleSize, int numberOfBlanks) {

    string userEntry;
    bool solverSuccess = false;
    Board board = generatePuzzle(puzzleSize, numberOfBlanks);
    regex rgx("[0-9]{1,}"); // For parsing user input
    smatch match;

    int inputInt[3]; // Array for user input

    // Repeat until the puzzle is solved
    do {

        board.printPuzzle(); // Print puzzle
        getline(cin, userEntry); // Get user input

        // Check for user commands
        if (userEntry == "Solve" || userEntry == "solve") {
            solverSuccess = solve(board, 0, 0);
            board.printPuzzle();
            break;
        }

        if (userEntry == "Clear" || userEntry == "clear") {
            board.clearPuzzle();
            continue;
        }

        // Assuming no special command, attempt to parse user input
        int count = 0;
        for (sregex_iterator i = sregex_iterator(userEntry.begin(), userEntry.end(), rgx);
             i != sregex_iterator();
             ++i) {
            smatch m = *i;
            inputInt[count] = stoi(m.str());
            ++count;
        }

        // If parsed values are out of range... throw an error and continue
        bool invalid = false;
        for (int i = 0; i < 3; i++) {
            if (!board.inBounds(inputInt[i])) {
                invalid = true;
            }
        }

        if (invalid) {
            cout << "Values entered must be between 1 and " << board.getSize() << endl;
            continue;
        }

        // Assign board value if feasible move
        if (board.feasibleUser((inputInt[0] - 1), (inputInt[1] - 1), inputInt[2]) == true) {

            if (!board.checkImmutable((inputInt[0] - 1), (inputInt[1] - 1))) {
                board.assignValue((inputInt[0] - 1), (inputInt[1] - 1), inputInt[2]);

            } else {
                cout << "You can't change that value!" << endl;
            }

        } else {
            cout << "Not feasible!" << endl;
        }

        // Reset inputs to 0, which will cause an invalid message if unchanged on the next round
        for (int i = 0; i < 3; i++) {
            inputInt[i] = 0;
        }

    } while (!board.checkPuzzle());

    string userResponse;

    if (solverSuccess) {

        cout << "The puzzle is solved!" << endl;
        playAgainPrompt(puzzleSize, numberOfBlanks);

    } else {

        cout << "Could not solve the puzzle based on pre-filled values" << endl;

        do {

            cout << "Would you like to clear and try to solve? y/n" << endl;
            getline(cin, userResponse);

        } while ((userResponse != "y") && (userResponse != "n"));

        if (userResponse == "y") {
            board.clearPuzzle();
            solve(board, 0, 0);
            board.printPuzzle();
            playAgainPrompt(puzzleSize, numberOfBlanks);
        }

    }
}
