#include "Boss.h"
#include <iostream>
#include <cmath>

Boss::Boss(Vector2 sp, Vector2 ep)
{

    srand((unsigned) time(NULL));

    spawnPoint = sp;
    endPoint = ep;

    health = 10;
    damage = 2;
    speed = 50.0f;
    shootDelayTimer = 0.0f;
    randNum = GenerateRandNum();
    givenScore = 100;

    velocity = { 0 };

    hasAppeared = false;
    hasDied = false;

    timerForDeathSpriteChange = 0.0f;
    currDeathFrame = 0;
    frameWidth = 48;
    numOfFrames = 8;
    deathFrameDelay = 0.08f;

    sprite = BossSprite;
    deathSprite = SecondDeathSprite;
    sourceRect = {0, 0, 116, 114};
    deathSourceRect = {0, 0, 48, 48};
    rect = {spawnPoint.x, spawnPoint.y, (float)sprite.width * 2.0f, (float)sprite.height * 2.0f};

}

void Boss::Update(float delta)
{

    if (health <= 0) return;

    float tolerance = 1.0f;

    if (fabs(rect.x - endPoint.x) < tolerance &&
        fabs(rect.y - endPoint.y) < tolerance)
    {

        hasAppeared = true;

    }

    velocity = Normalize(Vector2{endPoint.x - spawnPoint.x, endPoint.y - spawnPoint.y});

    if (!hasAppeared)
    {

        rect.x += velocity.x * speed * delta;
        rect.y += velocity.y * speed * delta;

    }

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(rect, 1.0f, RED);

}

std::unique_ptr<Projectile> Boss::Shoot(float delta, Player* player)
{

    Rectangle projSourceRect = {0, 0, 48, 48};
    Rectangle projRect = {
        (rect.x + rect.width / 2) - (sourceRect.width) / 2,
        rect.y + rect.height + 10,
        projSourceRect.width, projSourceRect.height
    };

    Vector2 dir = Normalize({(player->rect.x + player->rect.width / 2) - projRect.x, player->rect.y - projRect.y});

    return std::make_unique<HomingProjectile>(projRect, dir, 100.0f, true, damage, player);

}