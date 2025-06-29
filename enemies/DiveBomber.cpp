#include "../include/raylib.h"
#include "DiveBomber.h"
#include <cmath>
#include <iostream>

DiveBomber::DiveBomber(Vector2 fp, Vector2 swp) 
{

    srand((unsigned) time(NULL));

    health = 1;
    damage = 1;
    speed = 80.0f;
    randNum = GenerateRandNum();
    color = PURPLE;

    shootDelayTimer = 0.0f;

    finalPos = fp;
    spawnPoints = swp;

    velocity = { 0 };

    hasAppeared = false;
    rect = {spawnPoints.x, spawnPoints.y, 20.0f, 20.0f};

}

Projectile DiveBomber::Shoot(float delta, Vector2 playerPos) 
{

    Rectangle projRect;
    projRect.width = 8;
    projRect.height = 8;
    projRect.x = (this->rect.x + this->rect.width / 2) - projRect.width / 2;
    projRect.y = this->rect.y + this->rect.height + 10; 

    Vector2 dir = Normalize({playerPos.x - projRect.x, playerPos.y - projRect.y});

    Projectile proj;
    proj.rect = projRect;
    proj.direction.y = dir.y;
    proj.direction.x = dir.x;
    proj.speed = 100.0f;
    proj.isEnemy = true;

    return proj;

}

void DiveBomber::Update(float delta) 
{

    velocity = Normalize({this->finalPos.x - this->spawnPoints.x, this->finalPos.y - this->spawnPoints.y});

    float tolerance = 1.0f;

    if (fabs(this->rect.x - this->finalPos.x) < tolerance &&
        fabs(this->rect.y - this->finalPos.y) < tolerance) {

        hasAppeared = true;

    }

    if (!hasAppeared) {

        this->rect.x += velocity.x * speed * delta;
        this->rect.y += velocity.y * speed * delta;

    }

    if (hasAppeared) {

        this->rect.x += velocity.x * speed * delta;
        this->rect.y -= velocity.y * speed * delta;

    }

}