#pragma once

#include "../include/raylib.h"
#include "../Projectile.h"

class Enemy 
{

    public:

        static unsigned int nextId;
        unsigned int id;
        Rectangle rect;
        Texture2D sprite;
        Vector2 velocity;
        int health;
        int damage;
        float speed;
        float shootDelayTimer;

        Projectile virtual Shoot(float delta, Vector2 playerPos) = 0;
        void virtual TakeDamage(int amount) = 0;
        void virtual Update(float delta) = 0;
        bool operator==(const Enemy &other) const;

};