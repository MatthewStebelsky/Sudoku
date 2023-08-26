/*
Main driver of the Sudoku game
*/
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "altproj.hpp"
#include "game.hpp"
#include "tests.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    int seed; // Random seed
    int gameSize = 9; // Default size of the game
    int numberOfBlanks = 10; // Default number of prefilled spaces
    int simulationRuns = 0; // Number of simulation runs (if running speed tests)
    bool isVerbose = false; // Print each simulation result for speed tests
    string solvingMethod = "backtrace"; // Choose solving method

    // Handle command line args
    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "--seed") || 
            (std::string(argv[i]) == "-s")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> seed))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                std::cerr << "--seed option requires one argument." 
                          << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--gamesize") || 
            (std::string(argv[i]) == "-g")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> gameSize))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                std::cerr << "--gamesize option requires one argument." 
                          << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--nobs") || 
            (std::string(argv[i]) == "-n")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> numberOfBlanks))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                std::cerr << "--nobs option requires one argument." 
                          << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--Unittest") || 
            (std::string(argv[i]) == "-u")) {

            if (i + 1 < argc) {
                istringstream ss(argv[++i]);
                if (!(ss >> simulationRuns))
                    cerr << "Invalid number " << argv[i++] << endl;
            } else {
                std::cerr << "--Unittest option requires one argument." 
                          << std::endl;
                return 1;
            }
        }

        if ((std::string(argv[i]) == "--Verbose") || 
            (std::string(argv[i]) == "-v")) {
            isVerbose = true;
        }

        if ((std::string(argv[i]) == "--RP") || 
            (std::string(argv[i]) == "-rp")) {
            solvingMethod = "RP";
        }

    }

    srand(seed); // Set the random seed

    // Welcome message
    cout << "===========================================" << endl;
    cout << "============ Welcome to Sudoku! ===========" << endl;
    cout << "===========================================" << endl;

    // Play the game or run simulations
    if (simulationRuns == 0) {
        playGame(gameSize, numberOfBlanks);
    } else {
        unitTest(gameSize, numberOfBlanks, simulationRuns, isVerbose);
    }

    return 0;
}
