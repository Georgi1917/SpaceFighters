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
        bool hasAppeared;

        Projectile virtual Shoot(float delta, Vector2 playerPos) = 0;
        void TakeDamage(int amount);
        void virtual Update(float delta) = 0;
        bool operator==(const Enemy &other) const;
        bool CheckForOutOfBounds();
        float Length(Vector2 vec) const;
        Vector2 Normalize(Vector2 vec) const;

};