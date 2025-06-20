#include "../include/raylib.h"
#include "DiveBomber.h"
#include <cmath>
#include <iostream>

DiveBomber::DiveBomber(int hp, int dmg, float sp, Vector2 fp, Vector2 swp) {

    health = hp;
    damage = dmg;
    speed = sp;
    finalPos = fp;
    spawnPoints = swp;

    rect = {spawnPoints.x, spawnPoints.y, 10.0f, 10.0f};

}

float DiveBomber::Length(Vector2 vec) const {

    return std::sqrt(vec.x * vec.x + vec.y * vec.y);

}

Vector2 DiveBomber::Normalize(Vector2 vec) const {

    float len = Length(vec);

    if (len == 0) return {0, 0};

    return {vec.x / len, vec.y / len};

}

Projectile DiveBomber::Shoot(float delta, Vector2 playerPos) {

    Rectangle projRect;
    projRect.width = 8;
    projRect.height = 8;
    projRect.x = (this->rect.x + this->rect.width / 2) - projRect.width / 2;
    projRect.y = this->rect.y + this->rect.height / 2; 

    Projectile proj;
    proj.rect = projRect;
    proj.direction.y = -1;
    proj.direction.x = playerPos.x > this->rect.x ? 1 : -1;
    proj.speed = 400.0f;

    return proj;

}

void DiveBomber::TakeDamage(int amount) {

    this->health -= amount;

}

void DiveBomber::Update(float delta) {

    Vector2 direction = Normalize({this->finalPos.x - this->rect.x, this->finalPos.y - this->rect.y});

    if (this->rect.x != finalPos.x && this->rect.y != finalPos.y) {

        std::cout << "NO" << "\n";
        this->rect.x += direction.x * speed * delta;
        this->rect.y += direction.y * speed * delta;

    }
    else if (this->rect.x == finalPos.x || this->rect.y == finalPos.y) {

        std::cout << "YES" << "\n";
        this->rect.x -= direction.x * speed * delta;
        this->rect.y -= direction.y * speed * delta;

    }

}