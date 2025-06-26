#pragma once

#include "Enemy.h"
#include "vector"

class DogFighter : public Enemy 
{

    public:

        Vector2 setPoints;
        int currPointIndex;
        Vector2 currPoint;
        std::vector<Vector2> endPoints;

        DogFighter(Vector2 sp, std::vector<Vector2> ep);
        Projectile Shoot(float delta, Vector2 playerPos) override;
        void Update(float delta) override;

};