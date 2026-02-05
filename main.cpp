
#include <iostream>
#include <string>

#include <raylib.h>

#include "Player.h"
#include "Enemy.h"
#include "Log.h"

enum GameStates
{
    WAITING_FOR_INPUT = 0,
    PROCESS_INPUT,
    DISPLAYING_STATUS,
    FINISH_ROUND,
    PLAYER_WON,
    PLAYER_LOST
};

GameStates gameState = WAITING_FOR_INPUT;
int roundNumber = 1;

void PlayerAttacks(Player& player, Enemy& enemy, Action& enemyAction)
{
    switch (enemyAction)
    {
        case Action::ATTACK:
            Log::INFO("Both attacked! Its a clash!", false, true);
            break;

        case Action::PARRY:
            Log::ERROR(enemy.GetName() + " parries the attack. Our hero is struck!", false, true);
            if (gameState == PROCESS_INPUT)
            {
                player.UpdateHealth(-player.GetAttackPower() * 2);
                gameState = DISPLAYING_STATUS;
            }
            break;

        case Action::DEFEND:
            Log::INFO(enemy.GetName() + " is defending. The attack is less successful.", false, true);
            if (gameState == PROCESS_INPUT)
            {
                enemy.UpdateHealth(-enemy.GetAttackPower() / 2);
                gameState = DISPLAYING_STATUS;
            }
            break;

        case Action::NONE:
        default:
            break;
    }
}

void PlayerParries(Player& player, Enemy& enemy, Action& enemyAction)
{
    switch (enemyAction)
    {
        case Action::ATTACK:
            Log::INFO(player.GetName() + " parries the attack. The enemy is struck!", false, true);
            if (gameState == PROCESS_INPUT)
            {
                enemy.UpdateHealth(-enemy.GetAttackPower() * 2);
                gameState = DISPLAYING_STATUS;
            }
            break;

        case Action::PARRY:
            // No damage
            Log::WARNING("Both parried! No damage dealt.", false, true);
            break;

        case Action::DEFEND:
            // No damage
            Log::WARNING(player.GetName() + " parried while the enemy defended. No damage dealt.", false, true);
            break;

        case Action::NONE:
        default:
            break;
    }
}

void PlayerDefends(Player& player, Enemy& enemy, Action& enemyAction)
{
    switch (enemyAction)
    {
    case Action::ATTACK:
        Log::ERROR(player.GetName() + " is defending. The attack is less successful.", false, true);
        if (gameState == PROCESS_INPUT)
        {
            player.UpdateHealth(-player.GetAttackPower() / 2);
            gameState = DISPLAYING_STATUS;
        }
        break;
 
    case Action::PARRY:
        // No damage
        Log::WARNING(enemy.GetName() + " parried while our hero defended. No damage dealt.", false, true);
        break;
 
    case Action::DEFEND:
        // No damage
        Log::WARNING("Both defended! No damage dealt.", false, true);
        break;

    case Action::NONE:
    default:
        break;
    }
}

Action playerAction;
Action enemyAction;

void WaitForUserToContinue(GameStates const& nextState)
{
    Log::INFO("Press any key to continue!");

    if (GetKeyPressed() > 0)
    {
        gameState = nextState;
    }
}

void ProcessOutcome(Player& player, Enemy& enemy)
{
    if (gameState == WAITING_FOR_INPUT)
    {
        playerAction = player.ChooseAction();

        if (playerAction == NONE) return;

        enemyAction = enemy.ChooseAction();

        gameState = PROCESS_INPUT;
    }
    else if (gameState == DISPLAYING_STATUS || gameState == PROCESS_INPUT)
    {
        Log::INFO(player.GetName() + " chose to " + ActionStrings[playerAction]);
        Log::INFO(enemy.GetName() + " chose to " + ActionStrings[enemyAction]);

        switch (playerAction)
        {
        case Action::ATTACK:
            PlayerAttacks(player, enemy, enemyAction);
            break;

        case Action::PARRY:
            PlayerParries(player, enemy, enemyAction);
            break;

        case Action::DEFEND:
            PlayerDefends(player, enemy, enemyAction);
            break;

        case Action::NONE:
        default:
            break;
        }

        if (player.IsAlive() && enemy.IsAlive())
        {
            WaitForUserToContinue(WAITING_FOR_INPUT);
        }
        else if (enemy.IsAlive() == false) {
            Log::INFO("You have defeated " + enemy.GetName() + "! A stronger enemy appears!");
            player.ResetStats();

            WaitForUserToContinue(FINISH_ROUND);
        }
        else if(player.IsAlive() == false)
        {
            gameState = PLAYER_LOST;
        }
    }
    else if (gameState == FINISH_ROUND)
    {
        if (roundNumber < 5)
        {
            ++roundNumber;
            enemy.IncreaseDifficulty(roundNumber);
            gameState = WAITING_FOR_INPUT;
        }
        else
        {
            WaitForUserToContinue(PLAYER_WON);
        }
    }
    else if (gameState == PLAYER_LOST)
    {
        Log::INFO("You have been defeated! Game over!");
    }
    else if (gameState == PLAYER_WON)
    {
        Log::INFO("Congratulations! You have defeated all enemies!");
    }
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Duelists");

    Player player("Hero", 5, 2, 2, 2);
    Enemy enemy("Goblin", 1, 2, 0, 1);

    auto background = LoadTexture("../SourceArt/Arena.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexture(background, 0, 0, WHITE);

        Log::Init();

        Log::SEPARATOR();
        Log::INFO("Welcome to the Battle Arena!");
        Log::SEPARATOR();
        Log::INFO("Round " + std::to_string(roundNumber), true, true);

        Log::INFO(player.GetName() + " HP = " + std::to_string(player.GetHealth()));
        Log::INFO(enemy.GetName() + " HP = " + std::to_string(enemy.GetHealth()), false, true);

        ProcessOutcome(player, enemy);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    UnloadTexture(background);
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}