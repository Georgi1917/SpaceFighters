#pragma once
#include "include/raylib.h"
#include "utils/LoadSprites.h"
#include "projectiles/Projectile.h"
#include "projectiles/PlayerProjectile.h"
#include <memory>


class Player 
{

    public:
        Rectangle rect;

        int health;
        int score;

        float damage;
        float speed;
        float timerForShooting;

        bool hasLost;
        bool hasBeenHit;

        std::unique_ptr<Projectile> Shoot();
        void Move(float delta);
        void Die(float delta);
        void TakeDamage(int damage);
        Player();

    private:
        void CheckOutOfBounds(char axis, Vector2 &dir);

        
        Texture2D sprite;
        Texture2D engineSprite;
        Texture2D deathSprite;
        Rectangle spriteSource;
        Rectangle engineSource;
        Rectangle deathSourceRect;

        int numOfFrames;
        int frameWidth;
        int currDeathFrame;
        float deathFrameDelay;
        float timerForDeathSpriteChange;

        float timerForEngineChange;
        float frameDelay;
        int currFrame;

};