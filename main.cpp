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

void EmptyProjectilesVector(std::vector<std::unique_ptr<Projectile>> &proj)
{

    if (!proj.empty())
    {

        for (auto it = proj.begin(); it != proj.end(); )
            it = proj.erase(it);

    }

}

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

    InitWindow(screenWidth, screenHeight, "Space Fighters");
    InitAudioDevice();
    SetTargetFPS(60);

    LoadSprites();
    Music music = LoadMusicStream("music/music-loop.wav");

    Texture2D background = LoadTexture("textures/background/background.png");
    background.width = screenWidth;
    background.height = screenHeight;

    float bgScrollY = 0.0f;

    Player player = Player();
    UIClass ui;
    Level level = Level();

    Player *p = &player;

    PlayMusicStream(music);
    SetMusicVolume(music, 0.6f);

    while(!WindowShouldClose()) 
    {

        BeginDrawing();

        UpdateMusicStream(music);

        if (level.enemies.size() <= 0)
        {

            level.enemies.push_back(std::make_unique<Boss>(
                Vector2{100, -150}, Vector2{100, 200}, level.gameTime + 5.0f
            ));
            level.enemies.push_back(std::make_unique<Boss>(
                Vector2{300, -150}, Vector2{300, 200}, level.gameTime + 5.0f
            ));
            level.bossesHaveSpawned = true;

        }

        float deltaTime = GetFrameTime();

        level.gameTime += deltaTime;
        bgScrollY += 50 * deltaTime;


        if (bgScrollY > background.height) bgScrollY = 0;

        DrawTexture(background, 0, -background.height + (int)bgScrollY, WHITE);
        DrawTexture(background, 0, (int)bgScrollY, WHITE);

        if (!level.hasBegun)
        {

            if (IsKeyPressed(KEY_ENTER)) 
            {

                level.hasBegun = true;
                continue;

            }
            else if (IsKeyPressed(KEY_ESCAPE)) break;

            ui.VisualizeStartMenu();
            ClearBackground(LIGHTGRAY);
            EndDrawing();
            continue;

        }

        if (player.hasWon || player.hasLost)
        {

            if (IsKeyPressed(KEY_ENTER)) 
            {

                level.bossesHaveSpawned = false;
                level.spawnTime = 0.0f;
                level.gameTime = 0.0f;

                level.EmptyVector();
                level.PopulateVector();
                EmptyProjectilesVector(projectiles);
                PlayMusicStream(music);

                player.hasWon = false;
                player.hasLost = false;
                player.hasBeenHit = false;

                player.health = 5;
                player.SetNewBestScore();
                player.score = 0;

                ClearBackground(LIGHTGRAY);
                EndDrawing();
                continue;

            }
            
            else if (IsKeyPressed(KEY_ESCAPE)) break;

            ui.GameOverScreen(player);
            StopMusicStream(music);
            ClearBackground(LIGHTGRAY);
            EndDrawing();
            continue;

        }

        player.Move(deltaTime);

        if (IsKeyDown(KEY_Z) && player.timerForShooting >= 0.2f) 
        {

            projectiles.push_back(player.Shoot());
            player.timerForShooting = 0;

        }
        else if (IsKeyDown(KEY_Z) && player.timerForShooting < 0.2f) player.timerForShooting += deltaTime;
        else player.timerForShooting = 0;
        
        for (auto it = level.enemies.begin(); it != level.enemies.end();) 
        {

            if (level.gameTime >= (*it)->spawnTime)
                (*it)->Update(deltaTime);

            if (CheckCollisionRecs((*it)->rect, player.rect))
            {

                player.hasBeenHit = true;

            }

            if (generateRandomNumber() == (*it)->randNum && (*it)->shootDelayTimer >= 5 && (*it)->spawnTime <= level.gameTime) 
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
        if (level.bossesHaveSpawned && level.enemies.size() <= 0) player.hasWon = true;

        ui.VisualizePlayerStats(player);

        ClearBackground(LIGHTGRAY);

        EndDrawing();

    }

    CloseAudioDevice();
    UnloadTexture(background);
    UnloadSprites();

    CloseWindow();

    return 0;

}