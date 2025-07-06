#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(Rectangle r, Vector2 dir, float s, bool enemy) 
    : Projectile(r, dir, s, enemy)
    {

        sprite = basicProjSprite;
        sourceRect = {0, 0, 16, 16};

        timerForSpriteChange = 0.0f;
        currFrame = 0;
        frameDelay = 0.1f;

    }

void BasicProjectile::Update(float delta)
{
    
    rect.x += direction.x * speed * delta;
    rect.y += direction.y * speed * delta;

    timerForSpriteChange += delta;

    if (timerForSpriteChange >= frameDelay)
    {

        timerForSpriteChange = 0.0f;
        currFrame = (currFrame + 1) % 4;
        sourceRect.x = currFrame * 16;

    }

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(rect, 1.0f, RED);

}