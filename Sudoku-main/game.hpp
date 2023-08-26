/*

Gameplay function declarations
*/

#pragma once
#include <iostream>
#include <regex>
#include <sstream>
#include "solver.hpp"
#include "altproj.hpp"

// Main function to run the user interactive game
void playGame(int puzzleSize, int numberOfBlanks);

// Helper function to prompt the user to play again
void playAgainPrompt(int puzzleSize, int numberOfBlanks);
