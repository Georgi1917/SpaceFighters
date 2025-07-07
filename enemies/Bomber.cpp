#include "Bomber.h"
#include <cmath>
#include <iostream>

Bomber::Bomber(Vector2 sp, Vector2 ep) {

    srand((unsigned) time(NULL));

    health = 3;
    damage = 2;
    speed = 50.0f;
    shootDelayTimer = 0;
    rotation = 0.0f;
    color = BLUE;

    hasAppeared = false;

    randNum = GenerateRandNum();

    spawnPoint = sp;
    endPoint = ep;

    velocity = { 0 };

    timerForSpriteChange = 0.0f;
    currFrame = 0;
    frameDelay = 0.05f;
    
    sprite = bomberSprite;
    sourceRect = {0, 0, 32, 32};
    rect = {spawnPoint.x, spawnPoint.y, sourceRect.width * 2.0f, sourceRect.height * 2.0f};
    destRect = {rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height};

}

std::unique_ptr<Projectile> Bomber::Shoot(float delta, Player* player)
{

    Rectangle projSourceRect = {0, 0, 16, 32};
    Rectangle projRect = {
        (this->rect.x + this->rect.width / 2) - projSourceRect.width / 2,
        this->rect.y + this->rect.height + 10,
        projSourceRect.width * 1.6f, projSourceRect.height * 1.6f
    };

    Vector2 dir = Normalize({(player->rect.x + player->rect.width / 2) - projRect.x, player->rect.y - projRect.y});

    return std::make_unique<ExplosiveProjectile>(projRect, dir, 100.0f, true, player);

}

void Bomber::Update(float delta)
{

    velocity = Normalize({this->endPoint.x - this->spawnPoint.x, this->endPoint.y - this->spawnPoint.y});

    this->rect.x += velocity.x * speed * delta;
    this->rect.y += velocity.y * speed * delta;
    this->destRect.x += velocity.x * speed * delta;
    this->destRect.y += velocity.y * speed * delta;

    if (this->rect.x > 0 && 
        this->rect.y > 0 && 
        this->rect.x + this->rect.width < GetScreenWidth() &&
        this->rect.y + this->rect.height < GetScreenHeight()) hasAppeared = true;

    float targetAngle = atan2f(velocity.y, velocity.x) * (180.0f / PI) - 90.0f;

    rotation = GetRotation(targetAngle, delta);

    timerForSpriteChange += delta;

    if (timerForSpriteChange >= frameDelay) 
    {

        timerForSpriteChange = 0.0f;
        currFrame = (currFrame + 1) % 2;
        sourceRect.x = currFrame * 32;

    }

    DrawTexturePro(sprite, sourceRect, destRect, Vector2{destRect.width / 2, destRect.height / 2}, rotation, WHITE);
    DrawRectangleLinesEx(rect, 1.0f, color);
    DrawRectangleLinesEx(destRect, 1.0f, BLACK);

}

float Bomber::GetRotation(float targetAngle, float delta)
{

    float turnSpeed = 90.0f;
    float angleDiff = targetAngle - rotation;

    if (angleDiff > 90.0f) angleDiff -= 360.0f;
    if (angleDiff < -90.0f) angleDiff += 360.0f;

    if (fabs(angleDiff) < turnSpeed * delta) rotation = targetAngle;
    else rotation += (angleDiff > 1 ? 1 : -1) * turnSpeed * delta;

    return rotation;

}