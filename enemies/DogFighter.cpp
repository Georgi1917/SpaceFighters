#include "DogFighter.h"
#include <cmath>
#include <iostream>

DogFighter::DogFighter(Vector2 sp, std::vector<Vector2> ep)
{

    srand((unsigned) time(NULL));

    health = 1;
    damage = 1;
    speed = 50.0f;
    rotation = 0.0f;
    randNum = GenerateRandNum();
    color = RED;

    setPoints = sp;
    endPoints = ep;

    currPointIndex = 0;
    currPoint = endPoints[currPointIndex];

    velocity = { 0 };

    hasAppeared = false;
    hasDied = false;

    timerForDeathSpriteChange = 0.0f;
    frameWidth = 48;
    numOfFrames = 8;
    currDeathFrame = 0;
    deathFrameDelay = 0.08f;

    timerForSpriteChange = 0.0f;
    frameDelay = 0.05f;
    currFrame = 0;

    sprite = DogFighterSprite;
    deathSprite = SecondDeathSprite;
    sourceRect = {0, 0, 16, 16};
    deathSourceRect = {0, 0, 48, 48};
    rect = {setPoints.x, setPoints.y, (float)sourceRect.width * 1.8f, (float)sourceRect.height * 1.8f};
    destRect = {rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height};

}

std::unique_ptr<Projectile> DogFighter::Shoot(float delta, Player* player)
{

    Rectangle projSourceRect = {0, 0, 16, 16};
    Rectangle projRect = {
        (this->rect.x + this->rect.width / 2) - (sourceRect.width * 2.0f) / 2,
        this->rect.y + this->rect.height + 10,
        projSourceRect.width * 2.0f, projSourceRect.height * 2.0f
    };

    Vector2 dir = Normalize({(player->rect.x + player->rect.width / 2) - projRect.x, player->rect.y - projRect.y});

    return std::make_unique<BasicProjectile>(projRect, dir, 100.0f, true);

}

void DogFighter::Update(float delta)
{

    if (health <= 0) return;

    float tolerance = 1.0f;

    if (fabs(this->rect.x - this->currPoint.x) < tolerance &&
        fabs(this->rect.y - this->currPoint.y < tolerance))
    {

        currPointIndex++;
        setPoints = currPoint;
        currPoint = endPoints[currPointIndex];
        hasAppeared = true;

    }

    velocity = Normalize({this->currPoint.x - this->setPoints.x, this->currPoint.y - this->setPoints.y});

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
        sourceRect.x = currFrame * 16;

    }

    DrawTexturePro(sprite, sourceRect, destRect, Vector2{destRect.width / 2, destRect.height / 2}, rotation, WHITE);
    DrawRectangleLinesEx(rect, 1.0f, RED);
    DrawRectangleLinesEx(destRect, 1.0f, BLACK);

}

float DogFighter::GetRotation(float targetAngle, float delta)
{

    float turnSpeed = 120.0f;
    float angleDiff = targetAngle - rotation;

    if (angleDiff > 120.0f) angleDiff -= 360.0f;
    if (angleDiff < -120.0f) angleDiff += 360.0f;

    if (fabs(angleDiff) < turnSpeed * delta) rotation = targetAngle;
    else rotation += (angleDiff > 1 ? 1 : -1) * turnSpeed * delta;

    return rotation;

}

