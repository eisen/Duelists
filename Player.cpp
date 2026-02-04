#include <iostream>
#include <raylib.h>

#include "Player.h"
#include "Log.h"

Player::Player(std::string name, int maxHealth, int attackPower, int armor, int maxStamina) : Character(name, maxHealth, attackPower, armor, maxStamina)
{

}

Action Player::ChooseAction()
{
    int input = 0;
    Log::INFO("Choose your action: 1- Attack 2- Parry 3- Defend");

        if (IsKeyDown(KEY_ONE))
        {
            input = 1;
        }
        else if (IsKeyDown(KEY_TWO))
        {
            if (GetStamina() == 0)
            {
                Log::ERROR("Not enough stamina to parry. Please choose another action.", true, true);
            }
            else
            {
                input = 2;
            }

        }
        else if (IsKeyDown(KEY_THREE))
        {
            input = 3;
        }

    return GetActionFromInput(input - 1); // Adjust for 0-based indexing
}