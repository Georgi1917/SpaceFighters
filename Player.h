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
        Texture2D sprite;
        Texture2D engineSprite;

        float health;
        int score;
        float damage;
        float speed;
        float timerForShooting;
        bool hasLost;

        std::unique_ptr<Projectile> Shoot();
        void Move(float delta);
        Player();

    private:
        void CheckOutOfBounds(char axis, Vector2 &dir);

        Rectangle spriteSource;
        Rectangle engineSource;

        float timerForEngineChange;
        float frameDelay;
        int currFrame;

};