#include "include/raylib.h"
#include <iostream>

#define PLAYER_SPEED 300.0f

void CheckOutOfBounds(char axis, Rectangle &playerRect, Vector2 dir) {

    if (axis == 'x') {

        if (dir.x > 0 && (playerRect.x + playerRect.width) >= GetScreenWidth())
            playerRect.x = GetScreenWidth() - playerRect.width;
        else if (dir.x < 0 && (playerRect.x < 0))
            playerRect.x = 0;

    }
    else {

        if (dir.y > 0 && (playerRect.y + playerRect.height) >= GetScreenHeight())
            playerRect.y = GetScreenHeight() - playerRect.height;
        else if (dir.y < 0 && (playerRect.y < 0))
            playerRect.y = 0;

    }

}

void UpdatePlayerPos(Rectangle &playerRect, float delta) {

    Vector2 dir = { 0 };

    dir.x = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    dir.y = (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);

    playerRect.x += dir.x * PLAYER_SPEED * delta;
    CheckOutOfBounds('x', playerRect, dir);
    playerRect.y += dir.y * PLAYER_SPEED * delta;
    CheckOutOfBounds('y', playerRect, dir);

}

int main() {

    int screenWidth = 650;
    int screenHeight = 900;

    Rectangle playerRect = {300, 700, 40, 40};

    InitWindow(screenWidth, screenHeight, "Space Fighters");

    SetTargetFPS(60);

    while(!WindowShouldClose()) {

        BeginDrawing();

        float deltaTime = GetFrameTime();

        UpdatePlayerPos(playerRect, deltaTime);

        DrawRectangleRec(playerRect, GREEN);

        ClearBackground(LIGHTGRAY);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}