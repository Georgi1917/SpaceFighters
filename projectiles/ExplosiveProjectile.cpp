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

    sprite = explosiveProjSprite;
    sourceRect = {0, 0, 16, 32};
    destRect = { rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height };

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

    if (explosionRadius < maxRadius)
    {

        DrawCircle(this->rect.x, this->rect.y, explosionRadius, RED);

        if (CheckForCollisionWithPlayer(*player))
        {

            player->hasLost = true;

        } 

        explosionRadius += explosionSpeed * delta;

    }
    else 
    {

        toBeDeleted = true;
        explosionRadius = 0;
        countdown = 0;

    }
    
}

bool ExplosiveProjectile::CheckForCollisionWithPlayer(Player player)
{

    return CheckCollisionCircleRec(Vector2{this->rect.x, this->rect.y}, explosionRadius, player.rect);

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