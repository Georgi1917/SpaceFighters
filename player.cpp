#include "Player.h"
#include <iostream>

Player::Player()
{

    sprite = LoadTexture("textures/player/Player_ship (16 x 16).png");
    engineSprite = LoadTexture("textures/player/Boosters (16 x 16).png");
    spriteSource = Rectangle{16, 0, 16, 16};
    engineSource = Rectangle{0, 0, 16, 16};
    rect = Rectangle{300, 700, (float)sprite.width * 1.5f, (float)sprite.height * 4};

    health = 1;
    score = 0;
    damage = 1;
    speed = 300.0f;

    timerForShooting = 0;
    timerForEngineChange = 0;
    currFrame = 0;
    frameDelay = 0.05f;

    hasLost = false;

}

void Player::CheckOutOfBounds(char axis, Vector2 &dir) 
{

    if (axis == 'x') {

        if (dir.x > 0 && (this->rect.x + this->rect.width) >= GetScreenWidth())
            this->rect.x = GetScreenWidth() - this->rect.width;
        else if (dir.x < 0 && (this->rect.x < 0))
            this->rect.x = 0;

    }
    else {

        if (dir.y > 0 && (this->rect.y + this->rect.height) >= GetScreenHeight())
            this->rect.y = GetScreenHeight() - this->rect.height;
        else if (dir.y < 0 && (this->rect.y < 0))
            this->rect.y = 0;

    }

}

void Player::Move(float delta) 
{

    Vector2 dir = { 0 };

    dir.x = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    dir.y = (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);

    this->rect.x += dir.x * this->speed * delta;
    CheckOutOfBounds('x', dir);
    this->rect.y += dir.y * this->speed * delta;
    CheckOutOfBounds('y', dir);

    if (dir.x == -1) spriteSource.x = 0;
    else if (dir.x == 1) spriteSource.x = 32;
    else spriteSource.x = 16;

    timerForEngineChange += delta;

    if (timerForEngineChange >= frameDelay)
    {

        timerForEngineChange = 0.0f;
        currFrame = (currFrame + 1) % 2;
        engineSource.x = currFrame * 16;

    }

    DrawRectangleLinesEx(rect, 1.0f, GREEN);
    DrawTexturePro(sprite, spriteSource, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawTexturePro(engineSprite, engineSource, 
                   Rectangle{(rect.x + (sprite.width - engineSprite.width) / 2.0f) + 3.5f, 
                              rect.y + rect.height, (float)engineSprite.width * 1.5f, (float)engineSprite.height * 3.0f}, 
                   Vector2{0, 0}, 0.0f, WHITE);

}

std::unique_ptr<Projectile> Player::Shoot() 
{

    Rectangle projRect;
    projRect.width = 5;
    projRect.height = 10;
    projRect.x = (this->rect.x + this->rect.width / 2) - projRect.width / 2;
    projRect.y = this->rect.y - this->rect.height / 2; 

    return std::make_unique<BasicProjectile>(projRect, Vector2{0, -1}, 800.0f, false);

}