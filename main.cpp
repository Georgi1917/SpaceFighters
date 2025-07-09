#include "include/raylib.h"
#include "utils/LoadSprites.h"
#include "Player.h"
#include "projectiles/Projectile.h"
#include "projectiles/BasicProjectile.h"
#include "enemies/DiveBomber.h"
#include "enemies/Enemy.h"
#include "enemies/DogFighter.h"
#include "enemies/Bomber.h"
#include "enemies/HeavyFighter.h"
#include "enemies/Boss.h"
#include "UI/UIClass.h"
#include "levels/Level.h"
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
    // std::vector<std::unique_ptr<Enemy>> enemies;

    InitWindow(screenWidth, screenHeight, "Space Fighters");
    SetTargetFPS(60);

    LoadSprites();

    Texture2D background = LoadTexture("textures/background/background.png");
    background.width = screenWidth;
    background.height = screenHeight;

    float bgScrollY = 0.0f;

    Player player = Player();
    UIClass ui;
    Level level = Level();

    Player *p = &player;

    // enemies.push_back(std::make_unique<DiveBomber>(
    //     Vector2{600, -10}, Vector2{320, 500}, Vector2{100, -10}, 5
    // ));
    // enemies.push_back(std::make_unique<DiveBomber>(
    //     Vector2{600, -70}, Vector2{320, 500}, Vector2{100, -10}, 5
    // ));
    // enemies.push_back(std::make_unique<DiveBomber>(
    //     Vector2{600, -130}, Vector2{320, 500}, Vector2{100, -10}, 5
    // ));
    // enemies.push_back(std::make_unique<Bomber>(
    //     Vector2{-70, 320}, Vector2{(float) GetScreenWidth() + 20, 320}, 20
    // ));
    // enemies.push_back(std::make_unique<Bomber>(
    //     Vector2{700, 200}, Vector2{-10, 500}, 20
    // ));
    // enemies.push_back(std::make_unique<HeavyFighter>(
    //     Vector2{230, 910}, Vector2{230, 400}, Vector2{230, -10}, 30
    // ));
    // enemies.push_back(std::make_unique<DogFighter>(
    //     Vector2{-50, 600}, std::vector<Vector2>{
    //         {50, 580}, {120, 500}, {300, 450}, {400, 400}, {500, 300}, {700, 200}
    //     }, 10
    // ));
    // enemies.push_back(std::make_unique<DogFighter>(
    //     Vector2{(float)GetScreenWidth() + 10, 200}, std::vector<Vector2>{
    //         {600, 230}, {590, 280}, {590, 340}, {450, 340}, {320, 500}, {-30, 350}
    //     }, 10
    // ));
    // enemies.push_back(std::make_unique<Boss>(
    //     Vector2{230, -300}, Vector2{230, 150}, 40
    // ));

    while(!WindowShouldClose() && !player.hasLost) 
    {

        BeginDrawing();

        float deltaTime = GetFrameTime();

        level.gameTime += deltaTime;
        bgScrollY += 50 * deltaTime;

        if (bgScrollY > background.height) bgScrollY = 0;

        DrawTexture(background, 0, -background.height + (int)bgScrollY, WHITE);
        DrawTexture(background, 0, (int)bgScrollY, WHITE);

        player.Move(deltaTime);

        if (IsKeyDown(KEY_Z) && player.timerForShooting >= 0.2f) 
        {

            projectiles.push_back(player.Shoot());
            player.timerForShooting = 0;

        }
        else if (IsKeyDown(KEY_Z) && player.timerForShooting < 0.2f) player.timerForShooting += deltaTime;
        else player.timerForShooting = 0;

        std::cout << level.enemies.size() << "\n";
        
        for (auto it = level.enemies.begin(); it != level.enemies.end();) 
        {

            if (level.gameTime >= (*it)->spawnTime)
                (*it)->Update(deltaTime);

            if (CheckCollisionRecs((*it)->rect, player.rect))
            {

                player.hasBeenHit = true;

            }

            if (generateRandomNumber() == (*it)->randNum && (*it)->shootDelayTimer >= 5 && (*it)->spawnTime >= level.gameTime) 
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

            if ((*it)->health <= 0)
            {

                (*it)->Die(deltaTime);

                if ((*it)->hasDied) 
                {
                    
                    player.score += (*it)->givenScore;
                    it = level.enemies.erase(it);
                    continue;

                }

            }

            if (((*it)->CheckForOutOfBounds() && (*it)->hasAppeared))
            {

                it = level.enemies.erase(it);
                continue;

            }

            ++it;

        }

        for (auto proj = projectiles.begin(); proj != projectiles.end();) 
        {

            (*proj)->Update(deltaTime);

            if (CheckCollisionRecs((*proj)->rect, player.rect) && (*proj)->isEnemy)
            {

                player.TakeDamage((*proj)->damage);
                if (player.health <= 0) player.hasBeenHit = true;

                proj = projectiles.erase(proj);
                continue;

            }

            if ((*proj)->CheckOutOfBounds() || (*proj)->toBeDeleted)
            {

                proj = projectiles.erase(proj);
                continue;

            }

            ++proj;

        }

        if (player.hasBeenHit) player.Die(deltaTime);

        ui.VisualizePlayerStats(player);

        ClearBackground(LIGHTGRAY);

        EndDrawing();

    }

    UnloadTexture(background);
    UnloadSprites();

    CloseWindow();

    return 0;

}