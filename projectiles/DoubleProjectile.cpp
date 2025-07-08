#include "DoubleProjectile.h"

DoubleProjectile::DoubleProjectile(Rectangle r, Vector2 dir, float s, bool enemy, int dmg, Rectangle r2, Player* p) 
: Projectile(r, dir, s, enemy, dmg)
{

    sprite = doubleProjSprite;
    sourceRect = {0, 0, 32, 32};
    rect2 = r2;
    player = p;

    frameDelay = 0.05f;
    currFrame = 0;
    timerForSpriteChange = 0.0f;

}

void DoubleProjectile::Update(float delta)
{

    this->rect.x += direction.x * speed * delta;
    this->rect.y += direction.y * speed * delta;

    this->rect2.x += direction.x * speed * delta;
    this->rect2.y += direction.y * speed * delta;

    timerForSpriteChange += delta;

    if (timerForSpriteChange >= frameDelay)
    {

        timerForSpriteChange = 0.0f;
        currFrame = (currFrame + 1) % 5;
        sourceRect.x = currFrame * 32;

    }

    if (CheckForPlayerHit())
    {

        player->TakeDamage(damage);
        if (player->health <= 0) player->hasBeenHit = true;
        toBeDeleted = true;

    }

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawTexturePro(sprite, sourceRect, rect2, Vector2{0, 0}, 0.0f, WHITE);

    DrawRectangleLinesEx(rect, 1.0f, RED);
    DrawRectangleLinesEx(rect2, 1.0f, RED);

}

bool DoubleProjectile::CheckForPlayerHit()
{

    return (CheckCollisionRecs(rect, player->rect) || CheckCollisionRecs(rect2, player->rect));

}