#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(Rectangle r, Vector2 dir, float s, bool enemy) : Projectile(r, dir, s, enemy) {}

void BasicProjectile::Update(float delta)
{
    
    rect.x += direction.x * speed * delta;
    rect.y += direction.y * speed * delta;

}