#include "ExplosiveProjectile.h"
#include <iostream>

ExplosiveProjectile::ExplosiveProjectile(Rectangle r, Vector2 dir, float s, bool enemy, Player* p) : Projectile(r, dir, s, enemy) 
{

    player = p;
    timeToExplode = 3;
    countdown = 0.0f;
    explosionRadius = 0.0f;
    maxRadius = 80.0f;
    explosionSpeed = 50.0f;

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

        if (CheckForCollisionWithPlayer(*player)) std::cout << "YESSS" << "\n";

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