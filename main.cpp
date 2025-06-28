#include "include/raylib.h"
#include "Player.h"
#include "Projectile.h"
#include "enemies/DiveBomber.h"
#include "enemies/Enemy.h"
#include "enemies/DogFighter.h"
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
    bool hasLost = false;

    Rectangle playerRect = {300, 700, 40, 40};
    Player player = { 0 };
    player.rect = playerRect;
    player.damage = 1;
    player.health = 1;
    player.score = 0;
    player.timerForShooting = 0;
    player.speed = PLAYER_SPEED;

    std::vector<Projectile> projectiles;
    std::vector<std::unique_ptr<Enemy>> enemies;

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

    InitWindow(screenWidth, screenHeight, "Space Fighters");

    SetTargetFPS(60);

    while(!WindowShouldClose() && !hasLost) 
    {

        BeginDrawing();

        float deltaTime = GetFrameTime();
        player.Move(deltaTime);

        if (IsKeyDown(KEY_Z) && player.timerForShooting >= 0.1) 
        {

            Projectile proj = player.Shoot();
            projectiles.push_back(proj);
            player.timerForShooting = 0;

        }
        else if (IsKeyDown(KEY_Z) && player.timerForShooting < 0.1) player.timerForShooting += deltaTime;

        DrawRectangleRec(player.rect, GREEN);

        for (auto it = enemies.begin(); it != enemies.end();) 
        {

            (*it)->Update(deltaTime);

            std::cout << (*it)->randNum << "\n";

            if (CheckCollisionRecs((*it)->rect, player.rect)) hasLost = true;

            if (generateRandomNumber() == (*it)->randNum && (*it)->shootDelayTimer >= 5) 
            {

                Projectile proj = (*it)->Shoot(deltaTime, {player.rect.x, player.rect.y});
                projectiles.push_back(proj);
                (*it)->shootDelayTimer = 0;

            }
            else (*it)->shootDelayTimer += deltaTime;

            for (auto proj = projectiles.begin(); proj != projectiles.end();) 
            {

                if (CheckCollisionRecs((*it)->rect, (*proj).rect) && !(*proj).isEnemy) (*it)->TakeDamage(player.damage);
                ++proj;

            }

            if ((*it)->health <= 0 || ((*it)->CheckForOutOfBounds() && (*it)->hasAppeared))
            {

                it = enemies.erase(it);
                continue;

            }

            DrawRectangleRec((*it)->rect, RED);
            ++it;

        }

        for (Projectile &proj : projectiles) 
        {

            proj.rect.y += proj.direction.y * proj.speed * deltaTime;
            proj.rect.x += proj.direction.x * proj.speed * deltaTime;

            if (proj.CheckOutOfBounds()) projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), proj), 
                                         projectiles.end());
            if (CheckCollisionRecs(proj.rect, player.rect) && proj.isEnemy) hasLost = true;

            DrawRectangleRec(proj.rect, RED);

        }

        ClearBackground(LIGHTGRAY);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}