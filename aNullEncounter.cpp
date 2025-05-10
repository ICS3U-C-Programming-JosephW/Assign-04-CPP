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

/* Include the algorithm library for
algorithmic functions. */
#include <algorithm>
/* Include the chrono algorithm for
the delay function. */
#include <chrono>
/* Include the iostream library for
input and output functionalities. */
#include <iostream>
/* Include the cmath library for
the power function. */
#include <cmath>
/* Include the random library for
random generators. */
#include <random>
/* Include the vector library for
variable array structures. */
#include <vector>

/* Global constant for text colour
reset. The only shared constant. */
const std::string WHITE = "\033[0m";

/* Define a function to help get the correct
string answer from the user input. */
float GetCorrectString(std::string prompt, std::string targetStr, float lives) {
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
float GetCorrectInteger(std::string prompt, int targetInt, float lives) {
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

// Define a function to loop through stage questions.
float AskQuestions(const std::vector<std::vector
<std::string>> &STAGE_ENTRIES, float lives) {
    // Set a constant for blue text.
    const std::string LIGHT_BLUE = "\033[1;34m";

    /* Copy the stage entries array by
    assignment to safely modify it. */
    std::vector<std::vector<std::string>>
    stageEntriesCopy = STAGE_ENTRIES;

    // Set a random device to construct the engine.
    std::random_device randomDevice;
    /* Use the mersenne twister
    for high-quality randomizing. */ 
    std::mt19937 randomGen(randomDevice());

    // Shuffle the array copy for randomized questions.
    std::shuffle(stageEntriesCopy.begin(),
    stageEntriesCopy.end(), randomGen);

    // Display the initial line for any stage.
    std::cout << LIGHT_BLUE << "Let us see..."
    << WHITE << "\n";

    /* Use a for loop to loop through every
    question in the specific stage list. */
    for (int questionNum = 0; questionNum < stageEntriesCopy.size(); questionNum++) {
        // Check if the type of the answer is a string.
        if (stageEntriesCopy[questionNum][3] == "string") {
            // Run the string question function.
            lives = GetCorrectString(
                "\n" + LIGHT_BLUE + stageEntriesCopy
                [questionNum][0] + WHITE + "\n",
                stageEntriesCopy[questionNum][1],
                lives
            );
        } else {
            /* Otherwise, the type of the 
            answer has to be an integer. */

            /* Convert the integer answer
            as a string to an integer. */
            int integerAnswer = std::stoi(
            stageEntriesCopy[questionNum][1]);

            // Run the integer question function.
            lives = GetCorrectInteger(
                "\n" + LIGHT_BLUE + stageEntriesCopy
                [questionNum][0] + WHITE + "\n",
                integerAnswer, lives
            );
        }
        /* Check if the lives are
        less than or equal to zero. */
        if (lives <= 0) {
            // Break the loop.
            break;
        }
    }

    // Return the amount of lives left.
    return lives;
}

/* Define a function to generate a possible
void effect which challenges the user. */
float chanceVoidEFfect(int stageNum, float lives) {
    /* Declare the constant void
    effects array as a vector. */
    const std::vector<std::string> VOID_EFFECTS = {
        "The distant stars glare at the unfamiliar "
        "figure that is you, setting you ablaze internally",
        "You feel a deep pang of loneliness that eats you inside, "
        "even though null is by your side",
        "The temperature of this silent and empty void "
        "sends powerful chills down your spine",
        "The lack of entropy present in this void scares you",
        "Some meteoroids seem to have their own mind and fly "
        "towards you without your notice, surprising both "
        "you and null",
        "Lingering in this void makes you feel unwell, "
        "and you somewhat feel like leaving",
    };
    // Set a constant for purple text.
    const std::string LIGHT_PURPLE = "\033[1;35m";

    /* Determine the chance of the effect taking
    place based on the user's stage number. */
    int effectChance = (0.5 * pow(stageNum, 2))
    + (0.5 * stageNum) + 39;

    // Check if lives are less than or equal to 0.
    if (lives <= 0) {
        /* Return the lives early in the function so
        the user does not take any extra damage. */
        return lives;
    }

    // Set another random device to construct the engine.
    std::random_device randomChanceDevice;
    // Use the mersenne twister for high-quality randomizing. 
    std::mt19937 randomIntGen(randomChanceDevice());
    /* Uniformly distribute the possible integers
    over a distance of 1 to 100.*/
    std::uniform_int_distribution<int> intDist(1, 100);

    /* Check if the generated integer from 1 to 100
    is less than or equal to the effect chance. */
    if (intDist(randomIntGen) <= effectChance) {
        /* Uniformly distribute the possible integers
        over a distance of 0 to the array size
        subtracted by one. */
        std::uniform_int_distribution<int>
        effectDist(0, VOID_EFFECTS.size() - 1);

        /* Determine the possible effect by randomly
        selecting one from the void effects array. */
        std::string possibleEffect = VOID_EFFECTS
        [effectDist(randomIntGen)];

        /* Determine the damage of the effect
        based on the user's stage number. */
        float effectDamage = (0.1 * pow(stageNum, 2))
        + (0.4 * stageNum) + 0.6;

        /* Take away the user's lives
        based on the effect damage. */
        lives = std::max(lives - effectDamage, 0.0f);

        /* Display the resulting effect
        description and damage dealt. */
        std::cout << "\n" << LIGHT_PURPLE << possibleEffect << ". "
        << "You took " << effectDamage << "damage " << "and have " 
        << lives << ((lives == 1) ? "life": "lives") << "left." 
        << WHITE << "\n";   
    } else {
        /* Otherwise, the random number was greater than
        the effect chance. */
        // Display to the user that they are unaffected.
        std::cout << "\n" << LIGHT_PURPLE << "You remain unaffected "
        << "in the seemingly soundless void." << WHITE << "\n";
    }
    /* Return the lives at the end if the function
    was able to avoid the early return statement. */
    return lives;
}

// Run the main function.
int main() {
    /* Create a 3-dimensional vector array to store all the
    corresponding questions and answers for each of the six
    stages. Includes types to avoid type complexity. */

}
