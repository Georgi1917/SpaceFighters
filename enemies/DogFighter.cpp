#include "DogFighter.h"
#include <cmath>
#include <iostream>

DogFighter::DogFighter(Vector2 sp, std::vector<Vector2> ep)
{

    srand((unsigned) time(NULL));

    health = 1;
    damage = 1;
    speed = 50.0f;
    randNum = GenerateRandNum();
    color = RED;

    setPoints = sp;
    endPoints = ep;

    currPointIndex = 0;
    currPoint = endPoints[currPointIndex];

    velocity = { 0 };

    hasAppeared = false;
    rect = {setPoints.x, setPoints.y, 10.0f, 10.0f};

}

Projectile DogFighter::Shoot(float delta, Vector2 playerPos)
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

void DogFighter::Update(float delta)
{

    float tolerance = 1.0f;

    if (fabs(this->rect.x - this->currPoint.x) < tolerance &&
        fabs(this->rect.y - this->currPoint.y < tolerance))
    {

        currPointIndex++;
        setPoints = currPoint;
        currPoint = endPoints[currPointIndex];
        hasAppeared = true;

    }

    velocity = Normalize({this->currPoint.x - this->setPoints.x, this->currPoint.y - this->setPoints.y});

    this->rect.x += velocity.x * speed * delta;
    this->rect.y += velocity.y * speed * delta;

}

