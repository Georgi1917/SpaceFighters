#pragma once

#include "../include/raylib.h"
#include "../projectiles/Projectile.h"
#include "../projectiles/BasicProjectile.h"
#include "../projectiles/ExplosiveProjectile.h"
#include "../projectiles/DoubleProjectile.h"
#include "../projectiles/HomingProjectile.h"
#include "../Player.h"
#include <memory>

class Enemy 
{

    public:

        Rectangle rect;
        Vector2 velocity;
        Color color;
        int health;
        int damage;
        float speed;
        float shootDelayTimer;
        bool hasAppeared;
        bool hasDied;
        int randNum;
        int givenScore;

        std::unique_ptr<Projectile> virtual Shoot(float delta, Player* player) = 0;
        void virtual Update(float delta) = 0;

        void TakeDamage(int amount);
        bool CheckForOutOfBounds();
        float Length(Vector2 vec) const;
        Vector2 Normalize(Vector2 vec) const;
        int GenerateRandNum();

        void Die(float delta);
        
    protected:

        Texture2D sprite;
        Rectangle sourceRect;

        Texture2D deathSprite;
        Rectangle deathSourceRect;

        int numOfFrames;
        int frameWidth;
        int currDeathFrame;
        float deathFrameDelay;
        float timerForDeathSpriteChange;

        float timerForSpriteChange;
        float frameDelay;
        int currFrame;



};