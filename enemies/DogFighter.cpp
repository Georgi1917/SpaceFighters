#include "DogFighter.h"

DogFighter::DogFighter(Vector2 sp, std::vector<Vector2> ep)
{

    id = nextId++;
    health = 1;
    damage = 1;
    speed = 110.0f;

}