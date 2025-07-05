#include "HeavyFighter.h"
#include <cmath>
#include <iostream>

HeavyFighter::HeavyFighter(Vector2 sp, Vector2 mp, Vector2 ep)
{

    health = 6;
    damage = 2;
    speed = 50.0f;
    shootDelayTimer = 0.0f;
    stayTime = 4;
    countdown = 0;
    randNum = GenerateRandNum();
    color = PINK;

    hasAppeared = false;
    hasReachedMidPoint = false;

    velocity = { 0 };

    spawnPoint = sp;
    midPoint = mp;
    endPoint = ep;

    currPoint = spawnPoint;
    nextPoint = midPoint;

    rect = {spawnPoint.x, spawnPoint.y, 30.0f, 60.0f};

}

std::unique_ptr<Projectile> HeavyFighter::Shoot(float delta, Player* player)
{

    Rectangle projRect{ (this->rect.x + this->rect.width / 3) - 4, 
                        (this->rect.y + this->rect.height) + 10,
                        8, 8 };
    Rectangle projRect2{ ((this->rect.x + this->rect.width) - this->rect.width / 3) - 4, 
                         (this->rect.y + this->rect.height) + 10, 
                         8, 8 };

    Vector2 dir = { 0, 1 };

    return std::make_unique<DoubleProjectile>(projRect, dir, 80.0f, true, projRect2);

}

void HeavyFighter::Update(float delta)
{

    float tolerance = 1.0f;

    if (fabs(this->rect.x - this->nextPoint.x) < tolerance &&
        fabs(this->rect.y - this->nextPoint.y) < tolerance)
    {

        currPoint = midPoint;
        nextPoint = endPoint;
        hasAppeared = true;
        hasReachedMidPoint = true;

    }

    velocity = Normalize({(this->nextPoint.x - this->currPoint.x), (this->nextPoint.y - this->currPoint.y)});

    if (hasReachedMidPoint && countdown < stayTime) countdown += delta;
    else 
    {

        this->rect.x += velocity.x * speed * delta;
        this->rect.y += velocity.y * speed * delta;

    }

    DrawRectangleLinesEx(rect, 1.0f, color);

}