#include "ExplosiveProjectile.h"
#include <cmath>
#include <iostream>

ExplosiveProjectile::ExplosiveProjectile(Rectangle r, Vector2 dir, float s, bool enemy, Player* p) : Projectile(r, dir, s, enemy) 
{

    player = p;
    timeToExplode = 3;
    countdown = 0.0f;
    explosionRadius = 0.0f;
    maxRadius = 80.0f;
    explosionSpeed = 50.0f;

    rotation = 0.0f;

    timerForSpriteChange = 0.0f;
    currFrame = 0;
    frameDelay = 0.05f;

    timerForExpSpriteChange = 0.0f;
    frameExpDelay = 0.1f;
    currExpFrame = 0;

    sprite = explosiveProjSprite;
    explosionSprite = explosiveSprite;
    sourceRect = {0, 0, 16, 32};
    destRect = { rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height };
    explosionSourceRect = {0, 0, 16, 16};
    explosionDestRect = { 0 };

}

void ExplosiveProjectile::Update(float delta)
{

    if (countdown < timeToExplode)
    {

        this->rect.x += direction.x * speed * delta;
        this->rect.y += direction.y * speed * delta;
        this->destRect.x += direction.x * speed * delta;
        this->destRect.y += direction.y * speed * delta;

        countdown += delta;

        float targetAngle = atan2f(direction.y, direction.x) * (180.0f / PI) + 90.0f;

        rotation = GetRotation(targetAngle, delta);

        timerForSpriteChange += delta;

        if (timerForSpriteChange >= frameDelay)
        {

            timerForSpriteChange = 0.0f;
            currFrame = (currFrame + 1) % 6;
            sourceRect.x = currFrame * 16;

        }

        DrawTexturePro(sprite, sourceRect, destRect, Vector2{destRect.width / 2, destRect.height / 2}, targetAngle, WHITE);
        DrawRectangleLinesEx(rect, 1.0f, RED);
        DrawRectangleLinesEx(destRect, 1.0f, BLACK);

    }
    else Explode(delta);

}

void ExplosiveProjectile::Explode(float delta)
{

    if (explosionSourceRect.x < 96)
    {

        timerForExpSpriteChange += delta;

        if (timerForExpSpriteChange >= frameExpDelay)
        {

            timerForExpSpriteChange = 0.0f;
            currExpFrame += 1;
            explosionSourceRect.x = currExpFrame * 16;

        }

        explosionDestRect = {rect.x - (explosionSourceRect.width * 6.0f) / 2, rect.y, explosionSourceRect.width * 6.0f, explosionSourceRect.height * 6.0f};
        DrawTexturePro(explosionSprite, explosionSourceRect, explosionDestRect, Vector2{0, 0}, 0.0f, WHITE);
        DrawRectangleLinesEx(explosionDestRect, 1.0f, BLACK);

        if (CheckCollisionRecs(player->rect, explosionDestRect))
        {

            player->hasLost = true;

        }

    }
    else toBeDeleted = true;
    
}

float ExplosiveProjectile::GetRotation(float targetAngle, float delta)
{

    float turnSpeed = 90.0f;
    float angleDiff = targetAngle - rotation;

    if (angleDiff > 90.0f) angleDiff -= 360.0f;
    if (angleDiff < -90.0f) angleDiff += 360.0f;

    if (fabs(angleDiff) < turnSpeed * delta) rotation = targetAngle;
    else rotation += (angleDiff > 1 ? 1 : -1) * turnSpeed * delta;

    return rotation;

}