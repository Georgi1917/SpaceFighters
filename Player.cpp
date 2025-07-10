#include "Player.h"
#include <iostream>

Player::Player()
{

    sprite = playerSprite;
    engineSprite = playerEngineSprite;
    deathSprite = SecondDeathSprite;
    spriteSource = Rectangle{16, 0, 16, 16};
    engineSource = Rectangle{0, 0, 16, 16};
    deathSourceRect = {0, 0, 48, 48};
    rect = Rectangle{300, 700, spriteSource.width * 3.4f, spriteSource.height * 3.4f};

    health = 5;
    score = 0;
    bestScore = 0;
    damage = 1;
    speed = 300.0f;

    timerForShooting = 0;
    timerForEngineChange = 0;
    currFrame = 0;
    frameDelay = 0.05f;

    timerForDeathSpriteChange = 0.0f;
    currDeathFrame = 0;
    frameWidth = 48;
    frameDelay = 0.08f;
    numOfFrames = 8;

    hasLost = false;
    hasBeenHit = false;
    hasWon = false;

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

    if (hasBeenHit) return;

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

    DrawTexturePro(sprite, spriteSource, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawTexturePro(engineSprite, engineSource, 
                   Rectangle{(rect.x + rect.width / 2.0f) - engineSource.width - 6, 
                              rect.y + rect.height, engineSource.width * 2.8f, engineSource.height * 2.8f}, 
                   Vector2{0, 0}, 0.0f, WHITE);

}

std::unique_ptr<Projectile> Player::Shoot() 
{

    Rectangle sourceRect = {0, 0, 16, 16};
    Rectangle projRect = {
        (rect.x + rect.width / 2) - (sourceRect.width * 3.0f) / 2,
        rect.y - sourceRect.height * 3.0f,
        sourceRect.width * 3.0f, sourceRect.height * 3.0f
    }; 

    return std::make_unique<PlayerProjectile>(projRect, Vector2{0, -1}, 800.0f, false, damage);

}

void Player::Die(float delta)
{

    if (currDeathFrame < numOfFrames - 1)
    {

        timerForDeathSpriteChange += delta;

        if (timerForDeathSpriteChange >= frameDelay)
        {

            timerForDeathSpriteChange = 0.0f;
            currDeathFrame += 1;
            deathSourceRect.x = currDeathFrame * frameWidth;

        }

        DrawTexturePro(deathSprite, deathSourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);

    }
    else hasLost = true;

}

void Player::TakeDamage(int damage)
{
    
    if ((health - damage) <= 0) health = 0;
    else health -= damage;

}

void Player::SetNewBestScore()
{

    if (score > bestScore) bestScore = score;

}
