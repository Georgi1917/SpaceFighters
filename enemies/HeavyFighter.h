#pragma once

#include "Enemy.h"

class HeavyFighter : public Enemy
{

    public:

        std::unique_ptr<Projectile> Shoot(float delta, Player* player) override;
        void Update(float delta) override;

        HeavyFighter(Vector2 sp, Vector2 mp, Vector2 ep);

    private:

        Vector2 spawnPoint;
        Vector2 midPoint;
        Vector2 endPoint;

        float stayTime;
        float countdown;

};