#include "HomingProjectile.h"

HomingProjectile::HomingProjectile(Rectangle r, Vector2 dir, float s, bool enemy, Player* p) 
    : Projectile(r, dir, s, enemy)
    {

        player = p;
        sprite = HomingProjSprite;
        sourceRect = {0, 0, 48, 48};

        timerForSpriteChange = 0.0f;
        currFrame = 0;
        frameDelay = 0.05f;

    }

void HomingProjectile::Update(float delta)
{

    direction = Normalize({player->rect.x - rect.x, player->rect.y - rect.y});

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
    DrawRectangleLinesEx(rect, 1.0f, RED);

}