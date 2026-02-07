#include <iostream>
#include <raylib.h>

#include "Player.h"
#include "CombatLog.h"

Player::Player(std::string name, int maxHealth, int attackPower, int armor, int maxStamina) : Character(name, maxHealth, attackPower, armor, maxStamina)
{

}

Action Player::ChooseAction()
{
    int input = 0;
    DrawText("Choose your action: 1- Attack 2- Parry 3- Defend", 22, 102, 20, BLACK);
    DrawText("Choose your action: 1- Attack 2- Parry 3- Defend", 20, 100, 20, GREEN);

    if (IsKeyDown(KEY_ONE))
    {
        input = 1;
    }
    else if (IsKeyDown(KEY_TWO))
    {
        if (GetStamina() == 0)
        {
            CombatLog::AddEntry({"Not enough stamina to parry. Please choose another action.", RED, ENTRY_SHORT_DURATION});
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