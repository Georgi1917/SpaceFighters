#include "../include/raylib.h"
#include "DiveBomber.h"
#include <cmath>
#include <iostream>

DiveBomber::DiveBomber(Vector2 fp, Vector2 swp) {

    health = 1;
    damage = 1;
    speed = 80.0f;
    finalPos = fp;
    spawnPoints = swp;

    hasReachedFinalPos = false;
    rect = {spawnPoints.x, spawnPoints.y, 20.0f, 20.0f};

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

    Vector2 direction = Normalize({this->finalPos.x - this->spawnPoints.x, this->finalPos.y - this->spawnPoints.y});

    float tolerance = 1.0f;

    if (fabs(this->rect.x - this->finalPos.x) < tolerance &&
        fabs(this->rect.y - this->finalPos.y) < tolerance) {

        hasReachedFinalPos = true;

    }

    if (!hasReachedFinalPos) {

        this->rect.x += direction.x * speed * delta;
        this->rect.y += direction.y * speed * delta;

    }

    if (hasReachedFinalPos) {

        this->rect.x += direction.x * speed * delta;
        this->rect.y -= direction.y * speed * delta;

    }

}