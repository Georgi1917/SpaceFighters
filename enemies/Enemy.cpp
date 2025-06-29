#include "Enemy.h"
#include <cmath>
#include <random>

bool Enemy::CheckForOutOfBounds()
{

    return (rect.x + rect.width < 0 || 
            rect.x > GetScreenWidth() || 
            rect.y + rect.height < 0 || 
            rect.y > GetScreenHeight());

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

int Enemy::GenerateRandNum() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 5);

    return dis(gen);

}