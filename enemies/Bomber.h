#pragma once

#include "Enemy.h"

class Bomber : public Enemy {

    public:
        Vector2 spawnPoint;
        Vector2 endPoint;

        Projectile Shoot(float delta, Vector2 playerPos) override;
        void Update(float delta) override;

        Projectile ShootSpecial(float delta, Vector2 playerPos);

};