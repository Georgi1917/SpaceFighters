#include "DoubleProjectile.h"

DoubleProjectile::DoubleProjectile(Rectangle r, Vector2 dir, float s, bool enemy, Rectangle r2) : Projectile(r, dir, s, enemy)
{

    rect2 = r2;

}

void DoubleProjectile::Update(float delta)
{

    this->rect.x += direction.x * speed * delta;
    this->rect.y += direction.y * speed * delta;

    this->rect2.x += direction.x * speed * delta;
    this->rect2.y += direction.y * speed * delta;

    DrawRectangleRec(rect, RED);
    DrawRectangleRec(rect2, RED);

}