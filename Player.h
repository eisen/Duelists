#pragma once

#include "Character.h"

class Player : public Character
{
public:
    Player(std::string name, int maxHealth, int attackPower, int armor, int maxStamina);

    Action ChooseAction() override;
};