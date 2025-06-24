#include "Enemy.h"

unsigned int Enemy::nextId = 1;

bool Enemy::operator==(const Enemy &other) const 
{

    return (id == other.id);

}