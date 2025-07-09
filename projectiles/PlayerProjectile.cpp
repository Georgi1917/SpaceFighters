#include "PlayerProjectile.h"

PlayerProjectile::PlayerProjectile(Rectangle r, Vector2 dir, float s, bool enemy, int dmg) 
    : Projectile(r, dir, s, enemy, dmg)
    {

        sprite = playerProjSprite;
        sourceRect = {0, 0, 16, 16};

    }

void PlayerProjectile::Update(float delta)
{

    rect.x += direction.x * speed * delta;
    rect.y += direction.y * speed * delta;

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);

}