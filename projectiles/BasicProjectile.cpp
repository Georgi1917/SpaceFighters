#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(Rectangle r, Vector2 dir, float s, bool enemy) 
    : Projectile(r, dir, s, enemy)
    {

        sprite = basicProjectileSprite;
        sourceRect = {0, 0, 16, 16};

    }

void BasicProjectile::Update(float delta)
{
    
    rect.x += direction.x * speed * delta;
    rect.y += direction.y * speed * delta;

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);
    DrawRectangleLinesEx(rect, 1.0f, RED);

}