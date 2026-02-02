
#include <iostream>
#include <string>

#include "Player.h"
#include "Enemy.h"
#include "Log.h"

void PlayerAttacks(Player& player, Action& playerAction, Enemy& enemy, Action& enemyAction)
{
    switch (enemyAction)
    {
        case Action::ATTACK:
            Log::INFO("Both attacked! Its a clash!", false, true);
            break;

        case Action::PARRY:
            Log::ERROR(enemy.GetName() + " parries the attack. Our hero is struck!", false, true);
            player.UpdateHealth(-player.GetAttackPower() * 2);
            break;

        case Action::DEFEND:
            Log::INFO(enemy.GetName() + " is defending. The attack is less successful.", false, true);
            enemy.UpdateHealth(-enemy.GetAttackPower() / 2);
            break;
    }
}

void PlayerParries(Player& player, Action& playerAction, Enemy& enemy, Action& enemyAction)
{
    switch (enemyAction)
    {
        case Action::ATTACK:
            Log::INFO(player.GetName() + " parries the attack. The enemy is struck!", false, true);
            enemy.UpdateHealth(-enemy.GetAttackPower() * 2);
            break;

        case Action::PARRY:
            // No damage
            Log::WARNING("Both parried! No damage dealt.", false, true);
            break;

        case Action::DEFEND:
            // No damage
            Log::WARNING(player.GetName() + " parried while the enemy defended. No damage dealt.", false, true);
            break;
    }
}

void PlayerDefends(Player& player, Action& playerAction, Enemy& enemy, Action& enemyAction)
{
    switch (enemyAction)
    {
    case Action::ATTACK:
        Log::ERROR(player.GetName() + " is defending. The attack is less successful.", false, true);
        player.UpdateHealth(-player.GetAttackPower() / 2);
        break;
 
    case Action::PARRY:
        // No damage
        Log::WARNING(enemy.GetName() + " parried while our hero defended. No damage dealt.", false, true);
        break;
 
    case Action::DEFEND:
        // No damage
        Log::WARNING("Both defended! No damage dealt.", false, true);
        break;
    }
}

void ProcessOutcome(Player& player, Enemy& enemy)
{
    Action playerAction = player.ChooseAction();
    Action enemyAction = enemy.ChooseAction();

    Log::INFO(player.GetName() + "[" + std::to_string(player.GetHealth()) + "] chose to " + ActionStrings[playerAction], true);
    Log::INFO(enemy.GetName() + "[" + std::to_string(enemy.GetHealth()) + "] chose to " + ActionStrings[enemyAction]);

    switch (playerAction)
    {
    case Action::ATTACK:
        PlayerAttacks(player, playerAction, enemy, enemyAction);
        break;

    case Action::PARRY:
        PlayerParries(player, playerAction, enemy, enemyAction);
        break;

    case Action::DEFEND:
        PlayerDefends(player, playerAction, enemy, enemyAction);
        break;
    }
}

int main()
{
    Player player("Hero", 5, 2, 2, 2);
    Enemy enemy("Goblin", 1, 2, 0, 1);

    int roundNumber = 1;

    Log::SEPARATOR();
    Log::INFO("Welcome to the Battle Arena!");
    Log::SEPARATOR();
    Log::INFO("Round " + std::to_string(roundNumber), true, true);
   
    while (player.IsAlive())
    {
        ProcessOutcome(player, enemy);

        if (enemy.IsAlive() == false) {
            Log::INFO("You have defeated " + enemy.GetName() + "! A stronger enemy appears!");
            ++roundNumber;
            if(roundNumber > 5)
            {
                Log::INFO("Congratulations! You have defeated all enemies!");
                break;
            }
            Log::SEPARATOR();
            Log::INFO("Round " + std::to_string(roundNumber), true, true);
            enemy.IncreaseDifficulty(roundNumber);
        }
    }

    if(player.IsAlive() == false)
    {
        Log::ERROR("You have been defeated. Game Over.");
    }

    return 0;
}