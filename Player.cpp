#include <iostream>

#include "Player.h"
#include "Log.h"

Player::Player(std::string name, int maxHealth, int attackPower, int armor, int maxStamina) : Character(name, maxHealth, attackPower, armor, maxStamina)
{

}

Action Player::ChooseAction()
{
    int input = 0;
    while (true)
    {
        std::cout << "Choose your action:\n\t1. Attack\n\t2. Parry\n\t3. Defend\n";
        std::cin >> input;
        if(std::cin.fail() || input < 0 || input > 3)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Log::ERROR("Invalid input. Please try again.", true, true);
            continue;
        }
        else if (input == 2 && GetStamina() == 0)
        {
            Log::ERROR("Not enough stamina to parry. Please choose another action.", true, true);
            continue;
        }
        return GetActionFromInput(input - 1); // Adjust for 0-based indexing
    }
}