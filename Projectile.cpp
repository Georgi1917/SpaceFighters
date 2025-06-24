#include "include/raylib.h"
#include "Projectile.h"

int Projectile::nextId = 1;

Projectile::Projectile() : id(nextId++) {}

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