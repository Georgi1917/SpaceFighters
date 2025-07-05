#pragma once

#include "../include/raylib.h"
#include "../projectiles/Projectile.h"
#include "../projectiles/BasicProjectile.h"
#include "../projectiles/ExplosiveProjectile.h"
#include "../projectiles/DoubleProjectile.h"
#include "../Player.h"
#include <memory>

class Enemy 
{

    public:

        Texture2D sprite;
        Rectangle sourceRect;
        Rectangle rect;
        Vector2 velocity;
        Color color;
        int health;
        int damage;
        float speed;
        float shootDelayTimer;
        bool hasAppeared;
        int randNum;

        std::unique_ptr<Projectile> virtual Shoot(float delta, Player* player) = 0;
        void virtual Update(float delta) = 0;

        void TakeDamage(int amount);
        bool CheckForOutOfBounds();
        float Length(Vector2 vec) const;
        Vector2 Normalize(Vector2 vec) const;
        int GenerateRandNum();
        
    protected:
        float timerForSpriteChange;
        float frameDelay;
        int currFrame;

};