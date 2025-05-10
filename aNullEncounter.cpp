// Copyright (c) 2025. Joseph Wondimagnehu. All rights reserved.
//
// Created by: Joseph Wondimagnehu
// Date: May 9, 2025
/* This program contains a story-based game
where the user is trapped in a void and
meets someone named null, an entity who
later tells the user their story. The user
must endure the harmful environment of
the void and answer stages of questions
to win. */

/* Include the iostream library for
input and output functionalities. */
#include <iostream>
/* Include the algorithm library for
algorithmic functions. */
#include <algorithm>
/* Include the chrono algorithm for
the delay function. */
#include <chrono>

/* Define a function to help get the correct
string answer from the user input. */
float GetCorrectString(std::string prompt,
std::string targetStr, float lives) {
    // Declare the user's string answer.
    std::string userStrInput;
    /* Construct a do..while loop to always
    run the question prompt at least once. */
    do {
        // Display the prompt to the user.
        std::cout << prompt;
        // Get the user's string answer.
        std::getline(std::cin, userStrInput);
        /* Transform the user's string to lowercase
        to disregard the possible letter cases. */
        std::transform(userStrInput.begin(), userStrInput.end(),
        userStrInput.begin(),
        [](char scannedChar) { return std::tolower(scannedChar); });

        /* Check if the user entered an input that did
        not match the answer, meaning it was incorrect. */
        

    } while (true);
}

// Runs the main function.
int main() {}
