#pragma once
#include "include/raylib.h"
#include "Projectile.h"


class Player {

    public:
        Rectangle rect;
        float health;
        int score;
        float damage;
        float speed;
        float projectileSpeed;

        Projectile Shoot();
        void Move(float delta);

    private:
        void CheckOutOfBounds(char axis, Vector2 &dir);


};