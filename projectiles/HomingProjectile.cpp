#include "HomingProjectile.h"

HomingProjectile::HomingProjectile(Rectangle r, Vector2 dir, float s, bool enemy, int dmg, Player* p) 
    : Projectile(r, dir, s, enemy, dmg)
    {

        player = p;
        sprite = HomingProjSprite;
        sourceRect = {0, 0, 48, 48};

        timerForSpriteChange = 0.0f;
        currFrame = 0;
        frameDelay = 0.05f;
        hasBeenPassed = false;

    }

void HomingProjectile::Update(float delta)
{

    if (player->rect.y > rect.y && !hasBeenPassed) direction = Normalize({player->rect.x - rect.x, player->rect.y - rect.y});
    else hasBeenPassed = true;

    rect.x += direction.x * speed * delta;
    rect.y += direction.y * speed * delta;

    timerForSpriteChange += delta;

    if (timerForSpriteChange >= frameDelay)
    {

        timerForSpriteChange = 0.0f;
        currFrame = (currFrame + 1) % 4;
        sourceRect.x = currFrame * sourceRect.width;

    }

    DrawTexturePro(sprite, sourceRect, rect, Vector2{0, 0}, 0.0f, WHITE);

}