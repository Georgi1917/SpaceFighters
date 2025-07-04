#include "include/raylib.h"
#include "Player.h"
#include "projectiles/Projectile.h"
#include "projectiles/BasicProjectile.h"
#include "enemies/DiveBomber.h"
#include "enemies/Enemy.h"
#include "enemies/DogFighter.h"
#include "enemies/Bomber.h"
#include "enemies/HeavyFighter.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

#define PLAYER_SPEED 300.0f

int generateRandomNumber() 
{

    srand((unsigned) time(NULL));

    return (rand() % 6);

}

int main() 
{

    int screenWidth = 650;
    int screenHeight = 900;

    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::unique_ptr<Enemy>> enemies;

    InitWindow(screenWidth, screenHeight, "Space Fighters");
    SetTargetFPS(60);

    Player player = Player();

    Player *p = &player;

    enemies.push_back(std::make_unique<DiveBomber>(
        Vector2{600, 600}, Vector2{500, -10}
    ));
    enemies.push_back(std::make_unique<DiveBomber>(
        Vector2{500, 600}, Vector2{400, -10}
    ));
    enemies.push_back(std::make_unique<DiveBomber>(
        Vector2{400, 600}, Vector2{300, -10}
    ));
    enemies.push_back(std::make_unique<DogFighter>(
        Vector2{-50, 600}, std::vector<Vector2>{
            {50, 580}, {120, 500}, {300, 450}, {400, 400}, {500, 300}, {700, 200}
        }
    ));
    enemies.push_back(std::make_unique<Bomber>(
        Vector2{-10, 320}, Vector2{(float) GetScreenWidth() + 20, 320}
    ));
    enemies.push_back(std::make_unique<HeavyFighter>(
        Vector2{230, 910}, Vector2{230, 400}, Vector2{230, -10}
    ));

    while(!WindowShouldClose() && !player.hasLost) 
    {

        BeginDrawing();

        float deltaTime = GetFrameTime();
        player.Move(deltaTime);

        if (IsKeyDown(KEY_Z) && player.timerForShooting >= 0.1) 
        {

            projectiles.push_back(player.Shoot());
            player.timerForShooting = 0;

        }
        else if (IsKeyDown(KEY_Z) && player.timerForShooting < 0.1) player.timerForShooting += deltaTime;
        
        for (auto it = enemies.begin(); it != enemies.end();) 
        {

            (*it)->Update(deltaTime);

            if (CheckCollisionRecs((*it)->rect, player.rect)) player.hasLost = true;

            if (generateRandomNumber() == (*it)->randNum && (*it)->shootDelayTimer >= 5) 
            {

                projectiles.push_back((*it)->Shoot(deltaTime, p));
                (*it)->shootDelayTimer = 0;

            }
            else (*it)->shootDelayTimer += deltaTime;

            for (auto proj = projectiles.begin(); proj != projectiles.end();) 
            {

                if (CheckCollisionRecs((*it)->rect, (*proj)->rect) && !(*proj)->isEnemy)
                {

                    (*it)->TakeDamage(player.damage);
                    proj = projectiles.erase(proj);

                }
                else ++proj;

            }

            if ((*it)->health <= 0 || ((*it)->CheckForOutOfBounds() && (*it)->hasAppeared))
            {

                it = enemies.erase(it);
                continue;

            }

            DrawRectangleRec((*it)->rect, (*it)->color);
            ++it;

        }

        for (auto proj = projectiles.begin(); proj != projectiles.end();) 
        {

            (*proj)->Update(deltaTime);

            if (CheckCollisionRecs((*proj)->rect, player.rect) && (*proj)->isEnemy) player.hasLost = true;

            if ((*proj)->CheckOutOfBounds() || (*proj)->toBeDeleted)
            {

                proj = projectiles.erase(proj);
                continue;

            }

            ++proj;

        }

        ClearBackground(LIGHTGRAY);

        EndDrawing();

    }

    UnloadTexture(player.sprite);
    UnloadTexture(player.engineSprite);

    CloseWindow();

    return 0;

}