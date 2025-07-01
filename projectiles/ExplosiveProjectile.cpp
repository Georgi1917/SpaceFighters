#include "ExplosiveProjectile.h"

ExplosiveProjectile::ExplosiveProjectile(Rectangle r, Vector2 dir, float s, bool enemy) : Projectile(r, dir, s, enemy) 
{

    timeToExplode = 4;
    countdown = 0.0f;
    explosionRadius = 0.0f;
    maxRadius = 60.0f;
    explosionSpeed = 100.0f;

}

void ExplosiveProjectile::Update(float delta)
{

    if (countdown < timeToExplode)
    {

        this->rect.x += direction.x * speed * delta;
        this->rect.y += direction.y * speed * delta;
        countdown += delta;

    }
    else Explode(delta);

}

void ExplosiveProjectile::Explode(float delta)
{

    if (explosionRadius < maxRadius)
    {

        DrawCircle(this->rect.x, this->rect.y, explosionRadius, RED);
        explosionRadius += explosionSpeed * delta;

    }
    else 
    {

        explosionRadius = 0;
        countdown = 0;

    }
    
}