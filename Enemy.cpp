#include "Enemy.h"

Enemy::Enemy(std::string name, int maxHealth, int attackPower, int armor, int maxStamina) : Character(name, maxHealth, attackPower, armor, maxStamina)
{

}

Action Enemy::ChooseAction()
{
    int action = _distribution(_rng);
    if (action == 1 && GetStamina() == 0)
    {
        std::uniform_int_distribution<> limitedDistribution(0, 1);
        action = limitedDistribution(_rng) == 0 ? 0 : 2;
    }
    return GetActionFromInput(action);
}

void Enemy::IncreaseDifficulty(int roundNumber)
{
    switch (roundNumber)
    {
    case 1:
        break;

    case 2:
        _name = "Goblin Warrior";
        _health = roundNumber;
        break;

    case 3:
        _name = "Gladiator";
        _health = roundNumber;
        _attackPower += roundNumber;
        break;

    case 4:
        _name = "Berserker";
        _health = roundNumber;
        _attackPower += roundNumber;
        break;

    case 5:
        _name = "Knight Champion";
        _health = roundNumber;
        _attackPower += roundNumber;
        _armor += roundNumber >> 1;
        break;

    default:
        break;
    }
}