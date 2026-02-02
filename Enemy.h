#pragma once

#include <random>

#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(std::string name, int maxHealth, int attackPower, int armor, int maxStamina);

    Action ChooseAction() override;
    void IncreaseDifficulty(int roundNumber);

private:
    std::mt19937 _rng{ std::random_device{}() };
    std::uniform_int_distribution<int> _distribution{ 0, 2 };
};
