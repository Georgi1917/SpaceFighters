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

int main() {

    int screenWidth = 650;
    int screenHeight = 900;

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
        1, 1, 100.0f, Vector2{300, 300}, Vector2{200, -10}
    ));

    InitWindow(screenWidth, screenHeight, "Space Fighters");

    SetTargetFPS(60);

    while(!WindowShouldClose()) {

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
            DrawRectangleRec(e->rect, RED);

        }

        for (Projectile &proj : projectiles) {

            proj.rect.y += proj.direction.y * proj.speed * deltaTime;
            proj.rect.x += proj.direction.x * proj.speed * deltaTime;

            if (proj.rect.y < 0) projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), proj), projectiles.end());

            DrawRectangleRec(proj.rect, RED);

        }

        ClearBackground(LIGHTGRAY);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}