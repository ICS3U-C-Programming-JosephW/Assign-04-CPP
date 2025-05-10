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
/* Include the cmath library for
the power function. */
#include <cmath>
/* Include the iostream library for
input and output functionalities. */
#include <iostream>
/* Include the random library for
random generators. */
#include <random>
/* Include the string library to
adhere to style guidelines. */
#include <string>
/* Include the thread library to 
alter threads. */
#include <thread>
/* Include the vector library for
variable array structures. */
#include <vector>

/* Global constant for text colour
reset. The only shared constant.
Make it an array of characters
to adhere to style guidelines. */
const char WHITE[] = "\033[0m";

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
            << lives << ((lives == 1) ? " life." : " lives.")
            << WHITE << "\n";
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
    /* Initialize a position 
    tracker of the size type. */
    size_t intPosition = 0;

    /* Construct a do..while loop to always
    run the question prompt at least once. */
    do {
        // Display the prompt to the user.
        std::cout << prompt;
        // Get the user's integer answer as a string.
        std::getline(std::cin, userIntInputStr);

        // Try to validate and proceed with the user input.
        try {
            /* Attempt to convert the entered string into
            an integer and get the captured size. */
            userIntInput = std::stoi(userIntInputStr, &intPosition);

            /* Check if the raw size entered by the user is equal
            to the size of the successful conversion of std::stoi(). */
            if (intPosition == userIntInputStr.length()) {
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
                    << lives << ((lives == 1) ? " life." : " lives.")
                    << WHITE << "\n";
                }
            } else {
                /* Otherwise, the user did not enter a true
                integer and they added characters after it. */
                /* Display to the user that the integer input
                was invalid and that they must try again. */
                std::cout << BOLD << userIntInputStr
                << " is not a valid integer. Try again."
                << WHITE << "\n";
            }
        }
        /* Runs if any exceptions arise from
        std::stoi(). */
        catch (std::exception) {
            /* Display to the user that they
            did not enter a valid integer. */
            std::cout << BOLD << userIntInputStr
            << " is not a valid integer. Try again."
            << WHITE << "\n";
        }
    /* Repeat this while the user's answer is incorrect or they did
    not enter an integer, and their lives are greater than 0. */  
    } while (((userIntInput != targetInt) ||
    (intPosition != userIntInputStr.length())) && (lives > 0));

    // Return the amount of lives left.
    return lives;
}

// Define a function to loop through stage questions.
float AskQuestions(const std::vector<std::vector
<std::string>> &STAGE_ENTRIES, float lives) {
    // Set a constant for light blue text.
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
    question in the specific stage array. */
    for (int questionNum = 0; questionNum < stageEntriesCopy.size();
    questionNum++) {
        // Check if the type of the answer is a string.
        if (stageEntriesCopy[questionNum][2] == "string") {
            // Run the string question function.
            lives = GetCorrectString(
                "\n" + LIGHT_BLUE + stageEntriesCopy
                [questionNum][0] + WHITE,
                stageEntriesCopy[questionNum][1],
                lives);
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
                [questionNum][0] + WHITE,
                integerAnswer, lives);
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
float ChanceVoidEFfect(int stageNum, float lives) {
    /* Set a constant void effects array containing
    various effect descriptions as a vector. */
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
    // Set a constant for light purple text.
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
        subtracted by one to generate a random index. */
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
        << "You took " << effectDamage << " damage " << "and have "
        << lives << ((lives == 1) ? " life ": " lives ") << "left."
        << WHITE << "\n\n";
    } else {
        /* Otherwise, the random number was greater than
        the effect chance. */
        // Display to the user that they are unaffected.
        std::cout << "\n" << LIGHT_PURPLE << "You remain unaffected "
        << "in the seemingly soundless void." << WHITE << "\n\n";
    }
    /* Return the lives at the end if the function
    was able to avoid the early return statement. */
    return lives;
}

// Run the main function.
int main() {
    /* Create a constant 3-dimensional vector array to store
    all the corresponding questions and answers for each of
    the six stages. Includes literal types to avoid type complexity. */
    const std::vector<std::vector<std::vector<std::string>>> STAGE_ENTRIES {
        {
            {"3 + 4 = ", "7", "int"},
            {"Are truths and lies the same? (yes/no): ", "no", "string"},
            {"13 - 8 = ", "5", "int"},
        },
        {
            {"Is it okay to forget often...? (yes/no): ", "no", "string"},
            {"(2 x 3) + 3 = ", "9", "int"},
            {"1 + (12 / 12) * 12 = ", "13", "int"},
            {"In this void, does time still exist? "
            "(yes/no): ", "yes", "string"},
        },
        {
            {"Is life supposed to be fun? (yes/no): ", "yes", "string"},
            {"2^4 = ", "16", "int"},
            {"5 + (3 x 4)^2 + ((10 - 2) / 2) = ", "153", "int"},
            {"What is my name? (null/nothing/nobody): ", "null", "string"},
            {"(2 + 1) x (3 - 2) x 16 = ", "48", "int"},
        },
        {
            {"Do morals always mean good...? (yes/no): ", "no", "string"},
            {"10 % 2 + 9^(3/6) = ", "3", "int"},
            {"Could this all be an illusion? "
            "(yes/no/maybe): ", "maybe", "string"},
            {"2 x (4^9^0.5) = ", "128", "int"},
        },
        {
            {"(-3 x (3 - 4)) + 31 = ", "34", "int"},
            {"What is good to one person can be bad to another. "
            "(yes/no): ", "yes", "string"},
            {"(6 + 3 x 2) x 2^3 + 4 + (12-2) = ", "110", "int"},
        },
        {
            {"1 + (1 % 1) - 1 + 1 + (1^0.88) / 1 - (1^1) "
            " - 1 + 1 - (1^0.5) + 1 = ", "1", "int"},
            {"Morality is complex and everyone sees it differently. "
            "(yes/no): ", "yes", "string"},
        },
    };

    /* Create another constant 3-dimensional vector array to store
    all the corresponding dialogue lines and delay times for
    each of the six story parts. Assume delay types are
    string to avoid type complexity. */
    const std::vector<std::vector<std::vector<std::string>>> STAGE_DIALOGUES {
        {
            {
                "\nYou are in a void of space, yet you still can breathe. "
                "You are confused. What is all this?",
                "2",
            },
            {"Null: ...", "2"},
            {"User: Who... are you?", "2.5"},
            {"Null: I am null.", "2.5"},
            {"User: Null? As in nothing?", "2.5"},
            {
                "Null: Well, sort of. "
                "I forgot my name and practically everything else, "
                "so that is what I go by.",
                "2.5",
            },
            {"User: Wow... may I ask why I'm here?", "2.5"},
            {
                "Null: I do not know. "
                "People just spawn here like this is "
                "some sort of dimension.",
                "3",
            },
            {"User: So I'm stuck here forever???", "2.5"},
            {
                "Null: No. Others managed to leave, "
                "some shorter than the others. "
                "I would tell my story, and most of them would "
                "just disappear before I even finish it.",
                "3",
            },
            {"User: Ah... wait, story? You have a backstory?", "2"},
            {
                "Null: Yes. I would be happy to share it.",
                "2.5",
            },
            {
                "User: Sure! It's not like I have anything else to do... "
                "Tell me what happened to you and how you got here.",
                "3",
            },
            {"Null: Alright.", "1.5"},
            {".", "0.75"},
            {".", "1"},
            {".", "1.5"},
            {
                "It was a sunny day outside. The birds were chirping, "
                "flowers were blooming, and the scattered breezes made\nit all "
                "the more pleasant.",
                "3.5",
            },
            {
                "I felt like I could stay in this happy state forever. "
                "As I lay on the seemingly endless field of grass and flowers, "
                "it felt like I was one with nature.",
                "3.5",
            },
            {
                "I would attend to school, do my work, "
                "and look forward to the next day.",
                "3"
            },
            {
                "I repeated this routine daily, quickly eating my breakfast "
                "so I could go outside early and run to the large field, "
                "just to experience that feeling over and over again.",
                "3.5",
            },
            {
                "However, as days passed, everything "
                "got weirder and less exciting.",
                "3"
            },
            {
                "I still went to the field, but I could "
                "not make the same connections, ever.",
                "3",
            },
            {
                "I thought it was normal and the weather "
                "changes had to do with it, but even doing "
                "work and attending classes got harder.",
                "3.5",
            },
            {"It was...", "2.5"},
        },
        {
            {"...ME. It was me.", "2.5"},
            {
                "I was losing touch. My memory started receding, "
                "and I silently panicked in my\n"
                "head, fighting endless battles against my "
                "diminishing neurons.",
                "3.5",
            },
            {
                "Things were blurry, and my grades "
                "were hitting an all-time low.",
                "3.5"
            },
            {
                "I tried to make up for them by working "
                "extra time, but it did not do\n"
                "anything but add on to my confusion and distress.",
                "3.5",
            },
            {
                "Asking my parents for help because "
                "I forgot how to do simple tasks "
                "made them very concerned.",
                "3.5",
            },
            {
                "The final nail in the coffin was genuinely "
                "asking my parents\nhow to make a "
                "grilled cheese sandwich, which is what I "
                "always prepare for lunch.",
                "3.5",
            },
            {
                "They looked at me fearfully, and that "
                "was when I got sent to the hospital.",
                "3.5",
            },
        },
        {
            {
                "Most other people outside of the hospital "
                "held the same feelings. Not even the neurologists "
                "could find anything wrong,\nand they looked at each other, "
                "baffled. This was not some typical condition.",
                "3.5",
            },
            {"It was like a nightmare, especially for my parents.", "2.5"},
            {
                "It is excruciatingly painful when your "
                "own child suddenly does not remember "
                "anything about you anymore.\nI saw those "
                "feelings etched on my parents faces as "
                "tears freely flowed from their faces.",
                "3.5",
            },
            {
                "My parents urged the other doctors to "
                "do something, but it was to no avail.",
                "3",
            },
            {
                "Family, friends, work, the flower field, "
                "and routine, all forgotten. That was "
                "when I completely faded and ceased to live.",
                "3",
            },
        },
        {
            {
                "I escaped out of my own body for a "
                "short period of time, being able to see "
                "the reaction of my parents and other friends."
                "\nIt was heartbreaking, but I "
                "did not have a heart anymore.",
                "3.5",
            },
            {
                "After that short period of time, I "
                "could only see black and some distant dots.",
                "3",
            },
            {
                "I came to realize I was in what "
                "looked like outer space with stars, "
                "but I did not know why.",
                "3",
            },
            {
                "I could feel my own body and "
                "breathe, unaffected by being "
                "present in this empty space.",
                "3",
            },
            {
                "Maybe this was a reflection of "
                "my diminishing memories, or not. I "
                "never felt like connecting all the pieces.",
                "4",
            },
            {
                "Being able to tell this story "
                "multiple times was surprising. It's "
                "like some instance of\nmyself that "
                "somewhat wasn't affected "
                "by forgetfulness was reloaded.",
                "3.5",
            },
        },
        {
            {
                "I could not count time, do work, "
                "play, or go to the fields anymore. "
                "All I could do was\nreflect and "
                "contemplate in this VOID.",
                "3.5",
            },
            {"There were no feelings, but that would change.", "3"},
            {
                "Once I saw someone appear in my 'realm,' I got scared "
                "for some reason, thinking how it was possible.",
                "3",
            },
            {
                "People were able to fade out of my realm as well "
                "since they were still connected\nto their living selves, "
                "unlike me.",
                "3.5",
            },
            {
                "However, every person that managed to crawl into my space "
                "seemed to have the same feelings of loss and forgetfulness.",
                "3",
            },
            {
                "I could immediately connect myself to them, just like how I "
                "felt when I embraced nature on what seemed like the "
                "perfect day.",
                "3.5",
            },
            {
                "Knowing that, I wished them the best as "
                "they faded, and decided to "
                "keep contemplating until someone else appeared.",
                "3.5",
            },
            {
                "Those gaps in time seemed long, "
                "although it felt like I was being "
                "impatient. I was grateful, anyway.\n"
                "Even if they faded sooner than "
                "I expected, I still sighed in relief, "
                "every time.",
                "4",
            },
            {
                "And I will sigh in relief again "
                "once you manage to fade, user.",
                "3.5"
            },
        },
        {
            {
                "Every day, hour, minute, second, "
                "millisecond, without any doubt, "
                "I will have to embrace the\n"
                "everlasting confusion and void feelings "
                "that wander about in my head.",
                "3.5",
            },
            {"...ha.", "3.5"},
        },
    };
    /* Set constants for dark gray, light
    green, and light red text. */
    const std::string DARK_GRAY = "\033[1;30m",
    LIGHT_GREEN = "\033[1;32m",
    LIGHT_RED = "\033[1;31m";

    /* Set the user's current lives to
    25, which can change overtime. */
    float userCurrentLives = 25;

    // Loop through all the stage entries.
    for (int baseStageNum = 0; baseStageNum < STAGE_ENTRIES.size();
    baseStageNum++) {
        // Check if the user's lives are zero or less.
        if (userCurrentLives <= 0) {
            // Break the loop.
            break;
        }
        /* Nest a for loop inside to loop through all
        the dialogue lines before the corresponding
        stage entries. */
        for (int lineNum = 0; lineNum < STAGE_DIALOGUES[baseStageNum].size();
        lineNum++) {
            // Display the line of dialogue based on the current line number.
            std::cout << DARK_GRAY << STAGE_DIALOGUES[baseStageNum][lineNum][0]
            << WHITE << "\n\n";
            /* Delay the whole program based on the corresponding
            dialogue line for dynamic pacing. Convert the string
            delay time into a float to use it. */
            std::this_thread::sleep_for(std::chrono::duration<float>(
            std::stof(STAGE_DIALOGUES[baseStageNum][lineNum][1])));
        }

        /* Ask the user questions depending on their base stage number
        and assign their remaining lives to their current lives. */
        userCurrentLives = AskQuestions(STAGE_ENTRIES[baseStageNum],
        userCurrentLives);

        /* Generate a possible void effect based on the user's actual
        stage number and assign their remaining lives to their current
        lives. */
        userCurrentLives = ChanceVoidEFfect(baseStageNum + 1,
        userCurrentLives);
    }

    /* After the loop, do a final check to
    determine whether the user is alive. */
    if (userCurrentLives > 0) {
        // Display the winning dialogue with pacing.
        std::cout << LIGHT_GREEN << "Null: Well, that is the extent of "
        << "my story that continues to decline in quality.\n"
        << "Your resolve allowed you to endure these harsh "
        << "conditions, and I am glad you were able to listen."
        << WHITE << "\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << LIGHT_GREEN << "User: I am sorry for this."
        << WHITE << "\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << LIGHT_GREEN << "Null: Why? I do not mind wandering "
        << "here. It is like my heaven, sort of..." << WHITE << "\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << LIGHT_GREEN << "User: This place... heaven? Wait... "
        << "I am fading, just like you said!" << WHITE << "\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << LIGHT_GREEN << "Null: Yes. I did not want this to "
        << "happen so soon, but you are heading back to the real world. "
        << "Farewell, my friend." << WHITE << "\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << LIGHT_GREEN << "User: Farewell, null."
        << WHITE << "\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << LIGHT_GREEN << "Null continues to wander, "
        << "hopeful for the next person... The end."<< WHITE << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
    } else {
        // Otherwise, the user is dead.
        // Display the game over message.
        std::cout << LIGHT_RED << "\n. . . You have faltered under the void. "
        << "Who knows, maybe this was all just an illusion." << WHITE << "\n";
    }
}
