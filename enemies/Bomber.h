#pragma once

#include "Enemy.h"

class Bomber : public Enemy {

    public:
        Vector2 spawnPoint;
        Vector2 endPoint;

        std::unique_ptr<Projectile> Shoot(float delta, Vector2 playerPos) override;
        void Update(float delta) override;

        Bomber(Vector2 sp, Vector2 ep);

};