#include <iostream>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int diceRoll(int, int);                 // Rolls dice by type and number
int abilityModRoll();                   // Calculates an ability modifier
int attack(int, int, int, int, int, bool, bool);  // Performs both attack rolls
int opponentAttack(int, int, int, int, int, bool, bool); // Different lines
char mainMenu();                        // Displays main menu
int levelSelect(bool, bool, bool);      // Displays level selection menu
char combatMenu(string);                // Displays attack menu
int levelOne(int, int, int, int);       // Contains level one
int levelTwo(int, int, int, int);       // Contains level two

int main()
{
    srand(time(NULL));
    
    int playerLevel = 1,            // Player's current level
        proficiencyBonus = 3,       // Player's proficiency bonus
        constitutionMod = 0,        // Player's constitution modifier
        strengthMod = 0,            // Player's strength modifier
        dexterityMod = 0,           // Player's dexterity modifier
        playerHPMax = 0,            // Player's Maximum HP
        playerHP = 0,               // Player's Current HP
        playerAC = 0,               // Player's Armor Class
        treasureGained = 0,         // Treasure gained from level
        treasureTotal = 0,          // Player's accumulated treasure
        levelSelection = 0;         // Selection in level menu

    bool level1Unlocked = true,     // Set of bool variables stating whether
         level2Unlocked = false,    // each level is unlocked
         level3Unlocked = false,
         gameRunning = true;        // Whether or not game is still running

    char menuSelection = ' ';   // Choice selected from main menu

    // Conduct ability mod rolls for constitution and strength modifiers
    constitutionMod = abilityModRoll();
    strengthMod = abilityModRoll() + 2;
    dexterityMod = abilityModRoll() + 1;

    // Use constitution modifier to calculate hp at level 1 (5 in book)
    playerHPMax = 10 + ((playerLevel + 5) * constitutionMod) + diceRoll(10, 5);
    playerHP = playerHPMax;

    // Use dexterity modifier to calculate player's armor class
    playerAC = 14 + dexterityMod;
    
    while(gameRunning)
    {
        menuSelection = mainMenu();
        switch(menuSelection)
        {
            case 'a':
                levelSelection = levelSelect(level1Unlocked, level2Unlocked,
                    level3Unlocked);
                break;
            case 'b':
                break;
            case 'c':
                break;
            case 'd':
                cout << "Quitting Game." << endl;
                return 0;
        }

        switch(levelSelection)
        {
            case 1:
                treasureGained = levelOne(proficiencyBonus, strengthMod, playerHP,
                    playerAC);
                treasureTotal += treasureGained;
                playerHP = playerHPMax;
                if(treasureGained > 0)
                {
                    level2Unlocked = true;
                }
                break;
            case 2:
                treasureGained = levelTwo(proficiencyBonus, strengthMod, playerHP,
                    playerAC);
                treasureTotal += treasureGained;
                playerHP = playerHPMax;
        }
    }
    
    return 0;
}

// Function to roll dice by type of dice and number of that type of dice rolled
int diceRoll(int diceType, int numDice)
{
    int diceTotal = 0;

    for(int i = 1; i <= numDice; i++)
    {
        diceTotal += rand() % diceType + 1;
    }

    return diceTotal;
}

// Function to calculate an ability modifier by rolling 4d6 and adding the top
// three rolls
int abilityModRoll()
{
    int statRoll_1, statRoll_2, statRoll_3, statRoll_4, min, statTot = 0;

    statRoll_1 = diceRoll(6, 1);
    statRoll_2 = diceRoll(6, 1);
    statRoll_3 = diceRoll(6, 1);
    statRoll_4 = diceRoll(6, 1);

    statTot = statRoll_1 + statRoll_2 + statRoll_3;

    if(statRoll_1 < statRoll_2)
    {
        if(statRoll_1 < statRoll_3)
        {
            min = statRoll_1;
        }
        else
        {
            min = statRoll_3;
        }
    }
    else
    {
        if(statRoll_2 < statRoll_3)
        {
            min = statRoll_2;
        }
        else
        {
            min = statRoll_3;
        }
    }

    if (statRoll_4 > min)
    {
        statTot = statTot - min + statRoll_4;
    }

    return (statTot - 10) / 2;
}

// Function to perform an attack roll using proficiency bonus, relevant ability
// modifier, AC of opponent, type of dice, number of dice
int attack
(
    int proficiencyBonus,   // Set by proficiency bonus var in main()
    int abilityMod,         // Generally strength, but could be any ability mod
    int opponentAC,         // AC of opponent, determines if attack hits
    int diceType,           // Type of dice needed for damage roll
    int numDice,            // Number of that dice rolled
    bool advantage,         // Whether or not attack has advantage
    bool disadvantage       // Whether or not attack has disadvantage
)
{
    int attackRoll = 0, damageRoll = 0, roll_1, roll_2;
    
    if(advantage && disadvantage)
    {
        attackRoll = diceRoll(20, 1) + proficiencyBonus + abilityMod;
    }
    else if(advantage)
    {
        roll_1 = diceRoll(20, 1);
        roll_2 = diceRoll(20, 1);

        if(roll_1 > roll_2)
        {
            attackRoll = roll_1 + proficiencyBonus + abilityMod;
        }
        else
        {
            attackRoll = roll_2 + proficiencyBonus + abilityMod;
        }
    }
    else if(disadvantage)
    {
        roll_1 = diceRoll(20, 1);
        roll_2 = diceRoll(20, 1);

        if(roll_1 < roll_2)
        {
            attackRoll = roll_1 + proficiencyBonus + abilityMod;
        }
        else
        {
            attackRoll = roll_2 + proficiencyBonus + abilityMod;
        }
    }
    else
    {
        attackRoll = diceRoll(20, 1) + proficiencyBonus + abilityMod;
    }

    if(attackRoll == (20 + proficiencyBonus + abilityMod))
    {
        cout << "Natural 20!!!" << endl;
        sleep_for(seconds(1));
        damageRoll = diceRoll(diceType, numDice) + diceRoll (diceType, numDice)
            + abilityMod;
        cout << "You dealt " << damageRoll << " damage!" << endl;

    }
    else if (attackRoll >= opponentAC)
    {
        cout << "The attack lands!" << endl;
        sleep_for(seconds(1));
        damageRoll = diceRoll(diceType, numDice) + abilityMod;
        cout << "You dealt " << damageRoll << " damage!" << endl;
    }
    else
    {
        cout << "The attack misses!" << endl;
        sleep_for(seconds(1));
        cout << "You dealt no damage!" << endl;
        damageRoll = 0;
    }

    sleep_for(seconds(2));
    return damageRoll;
}

// Function to perform opponent's attack roll
int opponentAttack
(
    int attackBonus,        // Opponent's bonus on attack roll
    int damageBonus,        // Opponent's bonus on damage roll
    int diceType,           // Type of dice needed for damage roll
    int numDice,            // Number of that dice rolled
    int playerAC,           // Player's armor class
    bool advantage,         // Whether or not opponent has advantage
    bool disadvantage       // Whether or not opponent has disadvantage
)
{
    int attackRoll = 0, damageRoll = 0, roll_1, roll_2;

    cout << "Your opponent is now attacking." << endl;
    sleep_for(seconds(1));
    
    if(advantage && disadvantage)
    {
        attackRoll = diceRoll(20, 1) + attackBonus;
    }
    else if(advantage)
    {
        roll_1 = diceRoll(20, 1);
        roll_2 = diceRoll(20, 1);

        if(roll_1 > roll_2)
        {
            attackRoll = roll_1 + attackBonus;
        }
        else
        {
            attackRoll = roll_2 + attackBonus;
        }
    }
    else if(disadvantage)
    {
        roll_1 = diceRoll(20, 1);
        roll_2 = diceRoll(20, 1);

        if(roll_1 < roll_2)
        {
            attackRoll = roll_1 + attackBonus;
        }
        else
        {
            attackRoll = roll_2 + attackBonus;
        }
    }
    else
    {
        attackRoll = diceRoll(20, 1) + attackBonus;
    }

    if(attackRoll == (20 + attackBonus))
    {
        cout << "It's a critical hit." << endl;
        sleep_for(seconds(1));
        damageRoll = diceRoll(diceType, numDice) + diceRoll (diceType, numDice)
            + damageBonus;
        cout << "You lost " << damageRoll << " HP!" << endl;

    }
    else if (attackRoll >= playerAC)
    {
        cout << "The attack lands!" << endl;
        sleep_for(seconds(1));
        damageRoll = diceRoll(diceType, numDice) + playerAC;
        cout << "You lost " << damageRoll << " HP!" << endl;
    }
    else
    {
        cout << "The attack misses!" << endl;
        sleep_for(seconds(1));
        cout << "You lost no HP." << endl;
        damageRoll = 0;
    }

    sleep_for(seconds(2));
    return damageRoll;
}

// Function to display the game's main menu and ask for user char input,
// returning a bool value of true if user quits game and false otherwise
char mainMenu()
{
    string userInput = " ";
    char menuSelection = ' ';
    bool choiceSelected = false;

    while (! choiceSelected)
    {
        // Display menu
        cout << "*****************************" << endl;
        cout << "          Main Menu" << endl;
        cout << "*****************************" << endl << endl;

        cout << "a. Level Select" << endl;
        cout << "b. Shop" << endl;
        cout << "c. Player Stats" << endl;
        cout << "d. Quit Game" << endl << endl;

        cout << "Enter your selection: ";
        getline(cin, userInput);
        menuSelection = userInput[0];
    
        // Return user's input to main() if valid, repeat if not
        switch(menuSelection)
        {
            case 'A':
            case 'a':
                choiceSelected = true;
                return 'a';
            case 'B':
            case 'b':
                choiceSelected = true;
                return 'b';
            case 'C':
            case 'c':
                choiceSelected = true;
                return 'c';
            case 'D':
            case 'd':
                cout << "You chose Quit." << endl;
                cout << "Are you sure you want to quit? (y/n) ";
                getline(cin, userInput);
                menuSelection = userInput[0];

                if(menuSelection == 'y')
                {
                    choiceSelected = true;
                    return 'd';
                }
                else
                {
                    cout << endl << endl << "Okay then..." << endl << endl;
                    choiceSelected = false;
                    break;
                }
            default:
                cout << "INVALID INPUT" << endl << endl;
                choiceSelected = false;
        }

        sleep_for(seconds(2));
    }

    // This statement shouldn't be reached, but the program should quit if it
    // is
    return 'd';
}

// Function to display level selection menu, returning integer value to main()
int levelSelect(bool level1Unlocked, bool level2Unlocked, bool level3Unlocked)
{
    string userInput = "";
    int levelSellection = 0;
    bool levelSelected = false;

    // While level unselected, display menu and ask for numerical input
    while (! levelSelected)
    {
        cout << endl << "******************************" << endl;
        cout << "         Level Select" << endl;
        cout << "******************************" << endl << endl;

        cout << "Level 1: ";
        if(level1Unlocked)
        {
            cout << "An Unexpected Tutorial" << endl;
        }
        else
        {
            cout << "?????" << endl;
        }

        cout << "Level 2: ";
        if(level2Unlocked)
        {
            cout << "The Bigger, Badder Boss" << endl;
        }
        else
        {
            cout << "?????" << endl;
        }

        cout << "Level 3: ";
        if(level3Unlocked)
        {
            cout << "[LEVEL 3 NAME]" << endl;
        }
        else
        {
            cout << "?????" << endl;
        }

        // Take user input and act according to input validity and selection
        cout << endl << "Enter your selection (just the number): ";
        getline(cin, userInput);
        if(isdigit(userInput[0]))
        {
            levelSellection = stoi(userInput);

            switch(levelSellection)
            {
                case 1:
                    if (level1Unlocked)
                    {
                        levelSelected = true;
                        return 1;
                    }
                    else
                    {
                        cout << "LEVEL LOCKED" << endl;
                        cout << "Try a level with a title." << endl;
                        levelSelected = false;
                    }

                    break;
                case 2:
                    if (level2Unlocked)
                    {
                        levelSelected = true;
                        return 2;
                    }
                    else
                    {
                        cout << "LEVEL LOCKED" << endl;
                        cout << "Try a level with a title." << endl;
                        levelSelected = false;
                    }
                
                    break;
                case 3:
                    if (level3Unlocked)
                    {
                        levelSelected = true;
                        return 3;
                    }
                    else
                    {
                        cout << "LEVEL LOCKED" << endl;
                        cout << "Try a level with a title." << endl;
                        levelSelected = false;
                    }
                
                    break;
                default:
                    cout << "INVALID INPUT" << endl;
                    levelSelected = false;
            }
        }
        else
        {
            cout << "INVALID INPUT" << endl;
            levelSelected = false;
        }

        sleep_for(seconds(2));
    }
    
return 0;
}

// Function to display combat menu, returning a character to the current level
char combatMenu(string secondaryAttack)
{
    string userInput = "";
    char combatSelection = ' ';
    bool choiceSelected = false;

    while(! choiceSelected)
    {
        cout << endl << "******************************" << endl;
        cout << "        Combat Options" << endl;
        cout << "******************************" << endl << endl;

        cout << "a. Longsword Attack" << endl;
        cout << "b. " << secondaryAttack << endl;
        cout << "c. Dodge" << endl << endl;

        cout << "Enter your selection: ";
        getline(cin, userInput);
        combatSelection = userInput[0];

        switch(combatSelection)
        {
            case 'A':
            case 'a':
                cout << "You selected Longsword Attack." << endl;
                sleep_for(seconds(1));
                choiceSelected = true;
                return 'a';
            case 'B':
            case 'b':
                if(secondaryAttack == "[NO SECONDARY ATTACK]")
                {
                    cout << "You don't have a secondary attack unlocked." << endl;
                    cout << "Try one of the other options." << endl;
                    choiceSelected = false;
                    break;
                }
                else
                {
                    cout << "You selected " << secondaryAttack << "." << endl;
                    sleep_for(seconds(1));
                    choiceSelected = true;
                    return 'b';
                }
            case 'C':
            case 'c':
                cout << "You selected Dodge." << endl;
                cout << "Your opponent is now at disadvantage on attack." << endl;
                sleep_for(seconds(2));
                choiceSelected = true;
                return 'c';
            default:
                cout << "INVALID INPUT" << endl;
                choiceSelected = false;
                break;
        }

        sleep_for(seconds(2));
    }

    return ' ';
}

// Function containing level one of game, returns int of player's accumulated
// treasure
int levelOne(int proficiencyBonus, int strengthMod, int playerHP, int playerAC)
{
    char combatSelection = ' ';
    int damageRoll = 0, goblinHP = 7;
    bool opponentDisadvantage = false, opponentAdvantage = false;

    cout << endl << "*********************************************" << endl;
    cout << "     Level One -- An Unexpected Tutorial" << endl;
    cout << "*********************************************" << endl << endl;

    sleep_for(seconds(1));
    cout << "Why Hello There." << endl << endl;
    sleep_for(seconds(2));

    cout << "I'm so glad you've made it." << endl;
    cout << "I was beginning to wonder if you'd turned tail and run." << endl;
    sleep_for(seconds(2));

    cout << endl << "It's so hard to find reliable mercenaries these days.";
    cout << endl;
    sleep_for(seconds(3));

    cout << endl << "Well let's get fighting!" << endl;
    sleep_for(seconds(2));
    cout << "I'm told you haven't fought too much before," << endl;
    cout << "but not to worry, I'll whip you up into fighting shape in no time.";
    cout << endl << endl;
    sleep_for(seconds(3));

    cout << "You see that Goblin over there." << endl;
    sleep_for(seconds(1));
    cout << "Yeah, right there!" << endl;
    sleep_for(seconds(2));

    cout << endl << "Those buggers don't usually set out alone." << endl;
    sleep_for(seconds(2));
    cout << "Looks like your training's starting off early!" << endl << endl;
    sleep_for(seconds(2));

    cout << "He's distracted, so you've got the element of surprise." << endl;
    sleep_for(seconds(2));
    cout << "I'd recommend starting off with an attack from that longsword";
    cout << endl << "of yours. Show him what you've got!" << endl;
    sleep_for(seconds(3));

    while(goblinHP > 0)
    {
        opponentDisadvantage = false;

        // Use combat menu to get a combat selection
        combatSelection = combatMenu("[NO SECONDARY ATTACK]");

        // Make changes in combat based on selection
        switch(combatSelection)
        {
            case 'a':
                damageRoll = attack(proficiencyBonus, strengthMod, 15, 10, 1,
                    true, false);
                goblinHP -= damageRoll;

                if (goblinHP < 0)
                {
                    goblinHP = 0;
                }
                break;
            case 'b':
                break; // Can be developed later as new secondary weapons added
            case 'c':
                opponentDisadvantage = true;
        }

        if(goblinHP == 0)
        {
            cout << endl << "That's what I'm talking about!" << endl;
            cout << "You killed the goblin!" << endl;
            sleep_for(seconds(2));
        }
        else
        {
            cout << endl << "The goblin has " << goblinHP << " HP remaining";
            cout << endl << endl;
            sleep_for(seconds(2));

            damageRoll = opponentAttack(4, 2, 6, 1, playerAC, false,
                opponentDisadvantage);
            playerHP -= damageRoll;

            if(playerHP <= 0)
            {
                cout << endl << "You were knocked unconscious." << endl;
                sleep_for(seconds(1));
                cout << "Don't worry, you can try this level again" << endl;
                cout << "once you're feeling better." << endl << endl;
                sleep_for(seconds(2));

                return 0;
            }
            else
            {
                cout << "You have " << playerHP << " HP remaining." << endl;
            }
        }
    }

    cout << endl << "You sure you've never fought before?!" << endl;
    sleep_for(seconds(1));
    cout << "Look at that bugger. You REALLY did him in." << endl << endl;
    sleep_for(seconds(2));

    cout << "Uh oh." << endl << endl;
    sleep_for(seconds(2));

    cout << "Looks like our little friend has a bigger friend!" << endl;
    sleep_for(seconds(2));
    cout << "If I recall, that there's a Goblin Boss." << endl << endl;
    sleep_for(seconds(2));

    cout << "A GOBLIN BOSS THAT'S HEADED STRAIGHT FOR YOU!!!" << endl;
    sleep_for(seconds(1));
    cout << "Now might be a good time to try out that dodge!" << endl;
    sleep_for(seconds(2));

    goblinHP = 21;
    opponentAdvantage = true;

    while(goblinHP > 0)
    {
        opponentDisadvantage = false;

        // Use combat menu to get a combat selection
        combatSelection = combatMenu("[NO SECONDARY ATTACK]");

        // Make changes in combat based on selection
        switch(combatSelection)
        {
            case 'a':
                damageRoll = attack(proficiencyBonus, strengthMod, 15, 10, 1,
                    false, false);
                goblinHP -= damageRoll;

                if (goblinHP < 0)
                {
                    goblinHP = 0;
                }
                break;
            case 'b':
                break; // Can be developed later as new secondary weapons added
            case 'c':
                opponentDisadvantage = true;
        }

        if(goblinHP == 0)
        {
            cout << endl << "Why I never!" << endl;
            cout << "You killed the Goblin Boss!" << endl;
            sleep_for(seconds(2));
        }
        else
        {
            cout << endl << "The goblin has " << goblinHP << " HP remaining";
            cout << endl << endl;
            sleep_for(seconds(2));

            damageRoll = opponentAttack(4, 2, 6, 1, playerAC, opponentAdvantage,
                opponentDisadvantage);
            playerHP -= damageRoll;

            if(playerHP <= 0)
            {
                cout << "You were knocked unconscious." << endl;
                sleep_for(seconds(1));
                cout << "Don't worry, you can try this level again" << endl;
                cout << "once you're feeling better." << endl << endl;
                sleep_for(seconds(2));

                return 0;
            }
            else
            {
                cout << "You have " << playerHP << " HP remaining." << endl;
            }
        }

        opponentAdvantage = false;
    }

    cout << endl << "Well, I think that's all the training you need." << endl;
    sleep_for(seconds(2));
    cout << "Oh boy, that Goblin Boss could've really roughed me up" << endl;
    cout << "If you weren't around." << endl << endl;
    sleep_for(seconds(2));

    cout << "Here, take 50 gold as a token of my gratitude." << endl;
    sleep_for(seconds(3));

    return 50;
}

// Function containing level two of game, returns int of player's accumulated
// treasure
int levelTwo(int proficiencyBonus, int strengthMod, int playerHP, int playerAC)
{
    char combatSelection = ' ';
    int damageRoll = 0, bugbearHP = 27;
    bool opponentDisadvantage = false, opponentAdvantage = false;

    cout << endl << "**********************************************" << endl;
    cout << "     Level Two -- The Bigger, Badder Boss" << endl;
    cout << "**********************************************" << endl << endl;

    sleep_for(seconds(1));
    cout << "You know, this whole thing reminded me about that old addage.";
    cout << endl;
    sleep_for(seconds(2));
    cout << "How'd it go?" << endl << endl;
    
    cout << "Oh, that's right! There's always a bigger fish!" << endl;
    sleep_for(seconds(2));
    cout << "Oh no! A bigger fish!" << endl << endl;
    sleep_for(seconds(1));

    cout << "IT'S A BUGBEAR!!!" << endl << endl;
    sleep_for(seconds(2));

    while(bugbearHP > 0)
    {
        opponentDisadvantage = false;

        // Use combat menu to get a combat selection
        combatSelection = combatMenu("[NO SECONDARY ATTACK]");

        // Make changes in combat based on selection
        switch(combatSelection)
        {
            case 'a':
                damageRoll = attack(proficiencyBonus, strengthMod, 16, 10, 1,
                    false, false);
                bugbearHP -= damageRoll;

                if (bugbearHP < 0)
                {
                    bugbearHP = 0;
                }
                break;
            case 'b':
                break; // Can be developed later as new secondary weapons added
            case 'c':
                opponentDisadvantage = true;
        }

        if(bugbearHP == 0)
        {
            cout << endl << "Hold on, I thought you were a beginner!" << endl;
            cout << "You just killed a bugbear!" << endl;
            sleep_for(seconds(2));
        }
        else
        {
            cout << endl << "The bugbear has " << bugbearHP << " HP remaining";
            cout << endl << endl;
            sleep_for(seconds(2));

            damageRoll = opponentAttack(4, 3, 8, 1, playerAC, false,
                opponentDisadvantage);
            playerHP -= damageRoll;

            if(playerHP <= 0)
            {
                cout << endl << "You were knocked unconscious." << endl;
                sleep_for(seconds(1));
                cout << "Don't worry, you can try this level again" << endl;
                cout << "once you're feeling better." << endl << endl;
                sleep_for(seconds(2));

                return 0;
            }
            else
            {
                cout << "You have " << playerHP << " HP remaining." << endl;
            }
        }
    }

    cout << "I don't think I can give you any better thaining than" << endl;
    cout << "what you've got already. I" << endl << endl;
    sleep_for(seconds(2));

    cout << "Here, have another 75 gold. I'm lucky to be alive" << endl;
    sleep_for(seconds(2));

    cout << "Good job sir, very good job." << endl << endl;
    sleep_for(seconds(3));

    return 75;
}