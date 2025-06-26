#pragma once
#include "../include/raylib.h"
#include "Enemy.h"

class DiveBomber : public Enemy 
{

    public:
        Vector2 finalPos;
        Vector2 spawnPoints;

        DiveBomber(Vector2 fp, Vector2 swp);
        Projectile Shoot(float delta, Vector2 playerPos) override;
        void Update(float delta) override;

};