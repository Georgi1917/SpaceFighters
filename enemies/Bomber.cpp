#include "Bomber.h"
#include <iostream>

Bomber::Bomber(Vector2 sp, Vector2 ep) {

    srand((unsigned) time(NULL));

    health = 3;
    damage = 2;
    speed = 50.0f;
    shootDelayTimer = 0;
    color = BLUE;

    hasAppeared = false;

    randNum = GenerateRandNum();

    spawnPoint = sp;
    endPoint = ep;

    velocity = { 0 };
    
    rect = {spawnPoint.x, spawnPoint.y, 50.0f, 25.0f};

}

std::unique_ptr<Projectile> Bomber::Shoot(float delta, Vector2 playerPos)
{

    Rectangle projRect;
    projRect.width = 8;
    projRect.height = 8;
    projRect.x = (this->rect.x + this->rect.width / 2) - projRect.width / 2;
    projRect.y = this->rect.y + this->rect.height + 10; 

    Vector2 dir = Normalize({playerPos.x - projRect.x, playerPos.y - projRect.y});

    return std::make_unique<BasicProjectile>(projRect, dir, 100.0f, true);

}

void Bomber::Update(float delta)
{

    velocity = Normalize({this->endPoint.x - this->spawnPoint.x, this->endPoint.y - this->spawnPoint.y});

    this->rect.x += velocity.x * speed * delta;
    this->rect.y += velocity.y * speed * delta;

    if (this->rect.x > 0 && 
        this->rect.y > 0 && 
        this->rect.x + this->rect.width < GetScreenWidth() &&
        this->rect.y + this->rect.height < GetScreenHeight()) hasAppeared = true;

}