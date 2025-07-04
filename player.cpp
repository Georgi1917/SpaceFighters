#include "Player.h"
#include <iostream>

Player::Player()
{

    sprite =LoadTexture("textures/player/Main Ship - Base - Full health.png");
    rect = Rectangle{300, 700, (float)sprite.width * 2.0f, (float)sprite.height * 2.0f};
    health = 1;
    score = 0;
    damage = 1;
    speed = 300.0f;
    timerForShooting = 0;
    hasLost = false;

}

void Player::CheckOutOfBounds(char axis, Vector2 &dir) 
{

    if (axis == 'x') {

        if (dir.x > 0 && (this->rect.x + this->rect.width) >= GetScreenWidth())
            this->rect.x = GetScreenWidth() - this->rect.width;
        else if (dir.x < 0 && (this->rect.x < 0))
            this->rect.x = 0;

    }
    else {

        if (dir.y > 0 && (this->rect.y + this->rect.height) >= GetScreenHeight())
            this->rect.y = GetScreenHeight() - this->rect.height;
        else if (dir.y < 0 && (this->rect.y < 0))
            this->rect.y = 0;

    }

}

void Player::Move(float delta) 
{

    Vector2 dir = { 0 };

    dir.x = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    dir.y = (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);

    this->rect.x += dir.x * this->speed * delta;
    CheckOutOfBounds('x', dir);
    this->rect.y += dir.y * this->speed * delta;
    CheckOutOfBounds('y', dir);

}

std::unique_ptr<Projectile> Player::Shoot() 
{

    Rectangle projRect;
    projRect.width = 5;
    projRect.height = 10;
    projRect.x = (this->rect.x + this->rect.width / 2) - projRect.width / 2;
    projRect.y = this->rect.y - this->rect.height / 2; 

    //Projectile proj = Projectile(projRect, {0, -1}, 800.0f, false);

    return std::make_unique<BasicProjectile>(projRect, Vector2{0, -1}, 800.0f, false);

}