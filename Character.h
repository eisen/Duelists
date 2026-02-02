#pragma once
#include <string>
#include <map>

enum Action {
    ATTACK = 0,
    PARRY,
    DEFEND,
    NONE
};

static std::map<Action, std::string> ActionStrings{
    {ATTACK, "Attack" },
    {PARRY, "Parry"},
    {DEFEND, "Defend"},
    {NONE, "None"}
};

class Character
{
public:
    Character(std::string name, int maxHealth, int attackPower, int armor, int maxStamina) : _name(name), _maxHealth(maxHealth), _attackPower(attackPower), _armor(armor), _maxStamina(maxStamina)
    {
        ResetStats();
    };

    unsigned int GetHealth() const { return _health; }
    void UpdateHealth(int damage);
    void UpdateStamina(bool increase = false);
    bool IsAlive() const { return _health > 0; }

    virtual Action ChooseAction() = 0;
    Action GetActionFromInput(int input);

    std::string GetName() const { return _name; }

    int GetAttackPower() const { return _attackPower; }
    int GetStamina() const { return _stamina; }

    void ResetStats();

protected:
    std::string _name;

    int _maxHealth;
    int _health;
    int _attackPower;
    int _armor;
    int _maxStamina;
    int _stamina;
};
