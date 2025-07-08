#include "Projectile.h"
#include <iostream>
#include <cmath>

int Projectile::nextId = 1;

Projectile::Projectile(Rectangle r, Vector2 dir, float s, bool enemy) 
{

    id = nextId++;
    rect = r;
    direction = dir;
    speed = s;
    isEnemy = enemy;
    toBeDeleted = false;

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

float Projectile::Length(Vector2 vec) const
{

    return std::sqrt(vec.x * vec.x + vec.y * vec.y);

}

Vector2 Projectile::Normalize(Vector2 vec) const
{

    float len = Length(vec);

    if (len == 0) return {0, 0};

    return {vec.x / len, vec.y / len};

}