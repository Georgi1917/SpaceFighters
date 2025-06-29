#pragma once

#include "../include/raylib.h"
#include "../Projectile.h"

class Enemy 
{

    public:

        Rectangle rect;
        Texture2D sprite;
        Vector2 velocity;
        Color color;
        int health;
        int damage;
        float speed;
        float shootDelayTimer;
        bool hasAppeared;
        int randNum;

        Projectile virtual Shoot(float delta, Vector2 playerPos) = 0;
        void virtual Update(float delta) = 0;

        void TakeDamage(int amount);
        bool CheckForOutOfBounds();
        float Length(Vector2 vec) const;
        Vector2 Normalize(Vector2 vec) const;
        int GenerateRandNum();

};