#include "Character.h"

Action Character::GetActionFromInput(int input)
{
    switch (input)
    {
    case 0:
        return Action::ATTACK;
    case 1:
        UpdateHealth(false);
        return Action::PARRY;
    case 2:
        UpdateStamina(true);
        return Action::DEFEND;
    default:
        return Action::NONE;
        break;
    }
    return Action::NONE;
}

void Character::ResetStats()
{
    _health = _maxHealth;
    _stamina = _maxStamina;
}

void Character::UpdateHealth(int damage)
{
    _health += damage;
    if (_health < 0) _health = 0;
    else if (_health > _maxHealth) _health = _maxHealth;
};

void Character::UpdateStamina(bool increase)
{
    _stamina = increase ? 1 : -1;
    if (_stamina < 0) _stamina = 0;
    else if (_stamina > _maxStamina) _stamina = _maxStamina;
};