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

    timerForSpriteChange = 0.0f;
    currFrame = 0;
    frameDelay = 0.05f;

    sprite = HeavyFighterSprite;
    engineSprite = HeavyFighterEngineSprite;
    sourceRect = {0, 0, 77, 103};
    engineSource = {0, 0, 128, 50};
    rect = {spawnPoint.x, spawnPoint.y, sourceRect.width, sourceRect.height};

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

    engineDest = {(rect.x + rect.width / 2) - engineSource.width / 2, (rect.y + rect.height) - engineSource.height / 1.38f, engineSource.width, engineSource.height};

    timerForSpriteChange += delta;
    if (timerForSpriteChange >= frameDelay)
    {

        timerForSpriteChange = 0.0f;
        currFrame = (currFrame + 1) % 8;
        engineSource.x = currFrame * 128;

    }

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawTexturePro(engineSprite, engineSource, engineDest, Vector2{0, 0}, 0.0f, WHITE);

    DrawRectangleLinesEx(rect, 1.0f, color);
    DrawRectangleLinesEx(Rectangle{rect.x, rect.y + rect.height, engineSource.width, engineSource.height}, 1.0f, BLACK);

}