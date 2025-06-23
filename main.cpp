#include "include/raylib.h"
#include "Player.h"
#include "Projectile.h"
#include "enemies/DiveBomber.h"
#include "enemies/Enemy.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

#define PLAYER_SPEED 300.0f

int generateRandomNumber() {

    srand((unsigned) time(NULL));

    return ((rand() % 10) - 5);

}

int main() {

    int screenWidth = 650;
    int screenHeight = 900;
    bool hasLost = false;

    Rectangle playerRect = {300, 700, 40, 40};
    Player player = { 0 };
    player.rect = playerRect;
    player.damage = 0;
    player.health = 0;
    player.score = 0;
    player.timerForShooting = 0;
    player.speed = PLAYER_SPEED;

    std::vector<Projectile> projectiles;
    std::vector<std::unique_ptr<Enemy>> enemies;

    enemies.push_back(std::make_unique<DiveBomber>(
        Vector2{300, 500}, Vector2{500, -10}
    ));
    enemies.push_back(std::make_unique<DiveBomber>(
        Vector2{500, 600}, Vector2{400, -10}
    ));
    enemies.push_back(std::make_unique<DiveBomber>(
        Vector2{100, 600}, Vector2{300, -10}
    ));
    enemies.push_back(std::make_unique<DiveBomber>(
        Vector2{450, 500}, Vector2{700, -10}
    ));

    InitWindow(screenWidth, screenHeight, "Space Fighters");

    SetTargetFPS(60);

    while(!WindowShouldClose() && !hasLost) {

        BeginDrawing();

        float deltaTime = GetFrameTime();
        player.Move(deltaTime);

        if (IsKeyDown(KEY_Z) && player.timerForShooting >= 0.1) {

            Projectile proj = player.Shoot();
            projectiles.push_back(proj);
            player.timerForShooting = 0;

        }
        else if (IsKeyDown(KEY_Z) && player.timerForShooting < 0.1) player.timerForShooting += deltaTime;

        DrawRectangleRec(player.rect, GREEN);

        for (auto& e : enemies) {

            e->Update(deltaTime);

            if (generateRandomNumber() < 0 && e->shootDelayTimer >= 5) {

                Projectile proj = e->Shoot(deltaTime, {player.rect.x, player.rect.y});
                projectiles.push_back(proj);
                e->shootDelayTimer = 0;

            }
            else e->shootDelayTimer += deltaTime;

            DrawRectangleRec(e->rect, RED);

        }

        for (Projectile &proj : projectiles) {

            proj.rect.y += proj.direction.y * proj.speed * deltaTime;
            proj.rect.x += proj.direction.x * proj.speed * deltaTime;

            if (proj.rect.y < 0) projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), proj), projectiles.end());
            if (CheckCollisionRecs(proj.rect, player.rect)) hasLost = true;

            DrawRectangleRec(proj.rect, RED);

        }

        ClearBackground(LIGHTGRAY);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}