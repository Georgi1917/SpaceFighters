#pragma once

#include "../include/raylib.h"
#include "Enemy.h"

class DiveBomber : public Enemy 
{

    public:

        DiveBomber(Vector2 swp, Vector2 mp, Vector2 fp);
        std::unique_ptr<Projectile> Shoot(float delta, Player* player) override;
        void Update(float delta) override;

    private:
        Vector2 spawnPoint;
        Vector2 midPoint;
        Vector2 finalPoint;

        Vector2 currPoint;
        Vector2 nextPoint;

        float rotation;
        Rectangle destRect;

        float GetRotation(float targetAngle, float delta);

};