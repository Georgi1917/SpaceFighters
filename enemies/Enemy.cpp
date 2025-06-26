#include "../include/raylib.h"
#include "Enemy.h"
#include <cmath>

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

void Enemy::TakeDamage(int amount)
{

    this->health -= amount;

}


float Enemy::Length(Vector2 vec) const 
{

    return std::sqrt(vec.x * vec.x + vec.y * vec.y);

}

Vector2 Enemy::Normalize(Vector2 vec) const 
{

    float len = Length(vec);

    if (len == 0) return {0, 0};

    return {vec.x / len, vec.y / len};

}