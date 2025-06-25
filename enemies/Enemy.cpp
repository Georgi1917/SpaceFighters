#include "../include/raylib.h"
#include "Enemy.h"

unsigned int Enemy::nextId = 1;

bool Enemy::operator==(const Enemy &other) const 
{

    return (id == other.id);

}

bool Enemy::CheckForOutOfBounds()
{

    return (rect.x < 0 || 
            rect.x + rect.width > GetScreenWidth() || 
            rect.y < 0 || 
            rect.y + rect.height > GetScreenHeight());

}