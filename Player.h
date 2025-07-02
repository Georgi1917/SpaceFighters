#pragma once
#include "include/raylib.h"
#include "projectiles/Projectile.h"
#include "projectiles/BasicProjectile.h"
#include <memory>


class Player 
{

    public:
        Rectangle rect;
        float health;
        int score;
        float damage;
        float speed;
        float timerForShooting;
        bool hasLost;

        std::unique_ptr<Projectile> Shoot();
        void Move(float delta);

    private:
        void CheckOutOfBounds(char axis, Vector2 &dir);


};