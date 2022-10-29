#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    //Display game title
    cout << "*********************" << endl
         << "      Mad Libs" << endl
         << "*********************" << endl << endl;

    //Declare variables for name, adjective, and noun
    string nameInput, adjectiveInput1, nounInput1;

    //Prompt user to input each of the three words and store them in their
    //relative variables
    cout << "Please give me a name: ";
    getline(cin, nameInput);
    cout << "Please give me an adjective: ";
    getline(cin, adjectiveInput1);
    cout << "Please give me a noun: ";
    getline(cin, nounInput1);

    //Output full mad lib with input
    cout << endl << "Hall Pass Mad Lib:" << endl
         << "******************" << endl
         << "Please excuse " << endl
         << nameInput << endl
         << "who is far too " << adjectiveInput1 << endl
         << "to attend " << nounInput1 << " class." << endl << endl;

    //Display game title
    cout << "*********************" << endl
         << "      Mad Libs" << endl
         << "*********************" << endl << endl;

    //Declare variables for a noun1, adjective, time of day, noun2, & place
    string nounInput2, adjectiveInput2, timeOfDayInput, nounInput3, placeInput;

    //Prompt user for input in these variables
    cout << "Please give me a noun: ";
    getline(cin, nounInput2);
    cout << "Please give me an adjective: ";
    getline(cin, adjectiveInput2);
    cout << "Please give me a time of day: ";
    getline(cin, timeOfDayInput);
    cout << "Please give me another noun: ";
    getline(cin, nounInput3);
    cout << "Please give me a place: ";
    getline(cin, placeInput);

    //Output full mad lib
    cout << endl << "Stop Believin\'" << endl
         << "**************" << endl
         << "Just a small town " << nounInput2 << endl
         << "Livin\' in a " << adjectiveInput2 << " world" << endl
         << "She took the " << timeOfDayInput
         << " train going anywhere." << endl
         << "Just a city " << nounInput3 << endl
         << "Born and raised in " << placeInput << endl
         << "He took the " << timeOfDayInput
         << " train going anywhere." << endl << endl;

    //Declare variables for total number of characters and average
    double totalNumChars1 = 0.0, averageNumChars1;
    double totalNumChars2 = 0.0, averageNumChars2;

    //Declare int constants for number of inputs in each game
    const int GAME1INPUTNUM = 3, GAME2INPUTNUM = 5;

    //For each input in game 1, add characters to running total of characters
    totalNumChars1 += nameInput.size();
    totalNumChars1 += adjectiveInput1.size();
    totalNumChars1 += nounInput1.size();

    //Divide by number of characters by input number for average
    averageNumChars1 = totalNumChars1 / GAME1INPUTNUM;

    //Repeat for game 2
    totalNumChars2 += nounInput2.size();
    totalNumChars2 += adjectiveInput2.size();
    totalNumChars2 += timeOfDayInput.size();
    totalNumChars2 += nounInput3.size();
    totalNumChars2 += placeInput.size();

    averageNumChars2 = totalNumChars2 / GAME2INPUTNUM;

    //Display stats
    cout << "First Mad Lib | Total number of characters: " << totalNumChars1
         << " | Averaged " << setprecision(3) << averageNumChars1
         << " characters per word" << endl;
    cout << "Second Mad Lib | Total number of characters: " << totalNumChars2
         << " | Averaged " << setprecision(3) << averageNumChars2
         << " characters per word" << endl;

    return 0;
}