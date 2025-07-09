#include "HeavyFighter.h"
#include <cmath>
#include <iostream>

HeavyFighter::HeavyFighter(Vector2 sp, Vector2 mp, Vector2 ep, float st)
{

    health = 6;
    damage = 2;
    speed = 50.0f;
    shootDelayTimer = 0.0f;
    stayTime = 4;
    countdown = 0;
    randNum = GenerateRandNum();
    color = PINK;
    givenScore = 30;

    hasAppeared = false;
    hasReachedMidPoint = false;
    hasDied = false;

    velocity = { 0 };

    spawnPoint = sp;
    midPoint = mp;
    endPoint = ep;
    spawnTime = st;

    currPoint = spawnPoint;
    nextPoint = midPoint;

    timerForSpriteChange = 0.0f;
    currFrame = 0;
    frameDelay = 0.05f;

    timerForDeathSpriteChange = 0.0f;
    currDeathFrame = 0;
    frameWidth = 128;
    numOfFrames = 12;
    deathFrameDelay = 0.08f;

    deathSprite = HeavyFighterDeathSprite;
    sprite = HeavyFighterSprite;
    engineSprite = HeavyFighterEngineSprite;
    sourceRect = {0, 0, 77, 103};
    engineSource = {0, 0, 128, 50};
    deathSourceRect = {0, 0, 128, 128};
    rect = {spawnPoint.x, spawnPoint.y, sourceRect.width * 1.8f, sourceRect.height * 1.8f};

}

std::unique_ptr<Projectile> HeavyFighter::Shoot(float delta, Player* player)
{

    Rectangle projSourceRect = {0, 0, 32, 32};

    Rectangle projRect{ this->rect.x, 
                        this->rect.y + this->rect.height,
                        projSourceRect.width, projSourceRect.height};
    Rectangle projRect2{ (this->rect.x + this->rect.width) - projSourceRect.width, 
                         this->rect.y + this->rect.height, 
                         projSourceRect.width, projSourceRect.height};

    Vector2 dir = { 0, 1 };

    return std::make_unique<DoubleProjectile>(projRect, dir, 80.0f, true, damage, projRect2, player);

}

void HeavyFighter::Update(float delta)
{

    if (health <= 0) return;

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

    engineDest = {(rect.x + rect.width / 2) - (engineSource.width * 1.8f) / 2, 
                  (rect.y + rect.height) - (engineSource.height * 1.8f) / 1.38f, 
                  engineSource.width * 1.8f, engineSource.height * 1.8f};

    timerForSpriteChange += delta;

    if (timerForSpriteChange >= frameDelay)
    {

        timerForSpriteChange = 0.0f;
        currFrame = (currFrame + 1) % 8;
        engineSource.x = currFrame * 128;

    }

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawTexturePro(engineSprite, engineSource, engineDest, Vector2{0, 0}, 0.0f, WHITE);

}