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

/* Global constant for text colour
reset. The only shared constant. */
const std::string WHITE = "\033[0m";

/* Define a function to help get the correct
string answer from the user input. */
float GetCorrectString(std::string prompt,
std::string targetStr, float lives) {
    // Set a constant for bold text.
    const std::string BOLD = "\033[1m";
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
        if (userStrInput != targetStr) {
            /* Take away one life from the user
            and keep it from going below zero. */
            lives = std::max(lives - 1.0f, 0.0f);

            /* Display to the user that they were incorrect,
            along with their resulting lives. */
            std::cout << BOLD << "Incorrect, you lost one life "
            << "and have " << lives << " left." << WHITE << "\n";
        } else {
            // Otherwise, the user answered correctly.
            /* Display to the user that they were correct,
            along with their resulting lives. */
            std::cout << BOLD << "Correct. You currently have "
            << lives << ((lives == 1) ? "life" : "lives")
            << "left." << WHITE << "\n";
        }
    /* Repeat this while the user's answer is incorrect
    and their lives are greater than 0. */  
    } while ((userStrInput != targetStr) && (lives > 0));
    
    // Return the amount of lives left.
    return lives;
}

/* Define a function to help get the correct
integer answer from the user input. */
float GetCorrectInteger(std::string prompt,
int targetInt, float lives) {
    // Set a constant for bold text.
    const std::string BOLD = "\033[1m";
    /* Declare the user's integer answer
    as a string. */
    std::string userIntInputStr;
    /* Declare the user's answer as
    an actual integer. */
    int userIntInput;

    /* Construct a do..while loop to always
    run the question prompt at least once. */
    do {
        // Display the prompt to the user.
        std::cout << prompt;
        // Get the user's integer answer as a string.
        std::getline(std::cin, userIntInputStr);

        // Try to validate and proceed with the user input.
        try {
            /* Attempt to convert the entered
            string into an integer. */
            userIntInput = std::stoi(userIntInputStr);

            /* Check if the user entered an input that did
            not match the answer, meaning it was incorrect. */
            if (userIntInput != targetInt) {
                /* Take away one life from the user
                and keep it from going below zero. */
                lives = std::max(lives - 1.0f, 0.0f);

                /* Display to the user that they were incorrect,
                along with their resulting lives. */
                std::cout << BOLD << "Incorrect, you lost one life "
                << "and have " << lives << " left." << WHITE << "\n";
            } else {
                // Otherwise, the user answered correctly.
                /* Display to the user that they were correct,
                along with their resulting lives. */
                std::cout << BOLD << "Correct. You currently have "
                << lives << ((lives == 1) ? "life" : "lives")
                << "left." << WHITE << "\n";
                
            }
        }
        /* Runs if std::stoi() could not convert the
        user's string input into an integer. */
        catch (std::invalid_argument) {
            /* Display to the user that they
            did not enter a valid integer. */
            std::cout << BOLD << userIntInputStr
            << " is not a valid integer. Try again."
            << WHITE << "\n";
        }
    /* Repeat this while the user's answer is incorrect
    and their lives are greater than 0. */  
    } while ((userIntInput != targetInt) && (lives > 0));
    
    // Return the amount of lives left.
    return lives;
}

// Runs the main function.
int main() {

}
