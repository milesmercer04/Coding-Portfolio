#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{
    // Declare variables for random number, max value, guess, and number of
    // guesses
    int randomNumber, maxValue = 10, guess = -1, remainingGuesses = 4;
    int hintUpperRange, hintLowerRange;
    string userInput = "";
    bool isNumber;

    // Ask user to set maximum value for random number
    cout << "************************************" << endl;
    cout << "          Over Under Game!" << endl;
    cout << "************************************" << endl;
    cout << "What should the guessing range be between? 1 to ...? ";
    getline(cin, userInput);

    if (isdigit(userInput[0]))
    {
        maxValue = stoi(userInput);
    }
    
    // Pick random number between 1 and max value
    srand(time(NULL));
    randomNumber = (rand() % maxValue) + 1;

    // Define ranges for hints
    // Lower and upper range should always have equal size
    if (maxValue % 3 < 2)
    {
        hintLowerRange = maxValue / 3;
        hintUpperRange = maxValue - hintLowerRange + 1;
        // ex: max = 10, lower = 3, upper = 8
        // 3 numbers in lower third, 4 numbers in middle, and 3 in upper
    }
    else
    {
        hintLowerRange = maxValue / 3 + 1;
        hintUpperRange = maxValue - hintLowerRange + 1;
        // ex: max = 14, lower = 5, upper = 10
        // 5 numbers in in lower third, 4 in middle, 5 in upper
    }

    // Ask user for first guess
    cout << "Guess the number I'm thinking of between 1 and " << maxValue << endl;

    // While guess not equal to random number, ask for guess and say if it's
    // too high or too low
    while (guess != randomNumber && remainingGuesses > 0)
    {
        cout << "You have " << remainingGuesses << " guesses left." << endl;
        cout << endl << "Enter your new guess: ";
        getline(cin, userInput);

        // Test if user input is a number or not
        if (isdigit(userInput[0]))
        {
            isNumber = true;
            guess = stoi(userInput);
        }
        else
        {
            isNumber = false;
        }
        
        // Execute normal game code only if user input is a number
        if (isNumber)
        {
            // Make sure guess is in the acceptable range of values
            if (guess < 1 || guess > maxValue)
            {
                cout << "INVALID INPUT" << endl;
                return 0;
            }

            // Output statement based on guess' relationship to random number
            if (guess == randomNumber)
            {
                cout << endl << "You're right! You win!" << endl;
            }
            else if (guess < randomNumber)
            {
                cout << endl << "You're too low, try again." << endl;
            }
            else
            {
                cout << endl << "You're too high, try again." << endl;
            }

            // Decrease remaining guesses by 1
            remainingGuesses --;
        }
        else // If user input is not a number, move to cheat codes
        {
            if (userInput == "S") // If S, give solution
            {
                cout << endl << "Secret Number is: " << randomNumber << endl;
            }
            else if (userInput == "h") // If h, give hint
            {
                cout << endl << "Give hint!" << endl;

                if (randomNumber >= hintUpperRange)
                {
                    cout << "It's kinda high" << endl;
                }
                else if (randomNumber <= hintLowerRange)
                {
                    cout << "It's kinda low" << endl;
                }
                else
                {
                    cout << "It's kinda in the middle" << endl;
                }
            }
            else if (userInput == "q") // If q, ask to quit
            {
                string quitAnswer = "";
                cout << endl << "Are you sure you want to quit? (y/n) ";
                getline(cin, quitAnswer);

                if (quitAnswer == "y") // If user enters y, quit game
                {
                    remainingGuesses = 0;
                    guess = randomNumber;
                }
                else // Otherwise, resume game
                {
                    cout << "Okay then..." << endl;
                }
            }
            else // If not number and also neither S nor h nor q, input is invalid
            {
                cout << "INVALID INPUT" << endl;
                return 0;
            }
        }
    }

    // If user lost, output loss statement
    if (guess != randomNumber)
    {
        cout << "You didn't find my secret number! You lost." << endl;
    }

    // Output game over statement regardless of win or loss
    cout << "Game over - nice playing with you." << endl;

    return 0;
}