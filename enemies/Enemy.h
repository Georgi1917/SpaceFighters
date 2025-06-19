#pragma once

#include "../include/raylib.h"

class Enemy {

    public:

        Rectangle rect;
        Texture2D sprite;
        int health;
        int damage;
        float speed;

        void virtual Update(float deltaTime, Vector2 playerPos) = 0;
        void virtual TakeDamage(int amount) = 0;

    private:

        void virtual UpdateMovement(float deltaTime) = 0;
        void virtual UpdateShooting(float deltaTime, Vector2 playerPos) = 0;

        Vector2 pos;
        Vector2 velocity;

};