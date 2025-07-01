#include "Projectile.h"
#include <iostream>

int Projectile::nextId = 1;

Projectile::Projectile(Rectangle r, Vector2 dir, float s, bool enemy) 
{

    id = nextId++;
    rect = r;
    direction = dir;
    speed = s;
    isEnemy = enemy;

}

bool Projectile::CheckOutOfBounds() 
{

    return (rect.x < 0 || 
            rect.x + rect.width > GetScreenWidth() || 
            rect.y < 0 || 
            rect.y + rect.height > GetScreenHeight());

}

bool Projectile::operator==(const Projectile& other) const 
{

    return id == other.id;
    
}
