#pragma once

#include "Enemy.h"

class Boss : public Enemy
{

    public:

        Boss(Vector2 sp, Vector2 ep);
        std::unique_ptr<Projectile> Shoot(float delta, Player* player) override;
        void Update(float delta) override;

    private:

        Vector2 spawnPoint;
        Vector2 endPoint;

};