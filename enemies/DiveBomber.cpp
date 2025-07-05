#include "DiveBomber.h"
#include <cmath>
#include <iostream>

DiveBomber::DiveBomber(Vector2 swp, Vector2 mp, Vector2 fp) 
{

    srand((unsigned) time(NULL));

    health = 1;
    damage = 1;
    speed = 80.0f;
    randNum = GenerateRandNum();
    rotation = 0.0f;
    color = PURPLE;

    shootDelayTimer = 0.0f;

    finalPoint = fp;
    midPoint = mp;
    spawnPoint = swp;

    currPoint = spawnPoint;
    nextPoint = midPoint;

    velocity = { 0 };

    hasAppeared = false;

    timerForSpriteChange = 0.0f;
    frameDelay = 0.05f;
    currFrame = 0;

    sprite = LoadTexture("textures/enemies/DiveBomber.png");
    sourceRect = {0, 0, 32, 16};
    rect = {spawnPoint.x, spawnPoint.y, (float)sourceRect.width * 1.8f, (float)sourceRect.height * 1.8f};
    destRect = {rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height};

}

std::unique_ptr<Projectile> DiveBomber::Shoot(float delta, Player* player) 
{

    Rectangle projRect;
    projRect.width = 8;
    projRect.height = 8;
    projRect.x = (this->rect.x + this->rect.width / 2) - projRect.width / 2;
    projRect.y = this->rect.y + this->rect.height + 10; 

    Vector2 dir = Normalize({(player->rect.x + player->rect.width / 2) - projRect.x, player->rect.y - projRect.y});

    return std::make_unique<BasicProjectile>(projRect, dir, 100.0f, true);

}

void DiveBomber::Update(float delta) 
{

    float tolerance = 1.0f;

    if (fabs(this->rect.x - this->nextPoint.x) < tolerance &&
        fabs(this->rect.y - this->nextPoint.y) < tolerance) 
    {

        currPoint = midPoint;
        nextPoint = finalPoint;
        hasAppeared = true;

    }

    velocity = Normalize({this->nextPoint.x - this->currPoint.x, this->nextPoint.y - this->currPoint.y});

    this->rect.x += velocity.x * speed * delta;
    this->rect.y += velocity.y * speed * delta;
    this->destRect.x += velocity.x * speed * delta;
    this->destRect.y += velocity.y * speed * delta;

    float targetAngle = atan2f(velocity.y, velocity.x) * (180.0f / PI) - 90.0f;

    rotation = GetRotation(targetAngle, delta);

    timerForSpriteChange += delta;

    if (timerForSpriteChange >= frameDelay)
    {

        timerForSpriteChange = 0.0f;
        currFrame = (currFrame + 1) % 2;
        sourceRect.x = currFrame * 32;

    }

    DrawTexturePro(sprite, sourceRect, destRect, Vector2{destRect.width / 2.0f, destRect.height / 2.0f}, rotation, WHITE);
    DrawRectangleLinesEx(rect, 1.0f, color);
    DrawRectangleLinesEx(destRect, 1.0f, BLACK);

}

float DiveBomber::GetRotation(float targetAngle, float delta)
{

    float turnSpeed = 90.0f;
    float angleDiff = targetAngle - rotation;

    if (angleDiff > 90.0f) angleDiff -= 360.0f;
    if (angleDiff < -90.0f) angleDiff += 360.0f;

    if (fabs(angleDiff) < turnSpeed * delta) rotation = targetAngle;
    else rotation += (angleDiff > 1 ? 1 : -1) * turnSpeed * delta;

    return rotation;

}