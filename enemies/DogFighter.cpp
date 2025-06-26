#include "DogFighter.h"

DogFighter::DogFighter(Vector2 sp, std::vector<Vector2> ep)
{

    id = nextId++;
    health = 1;
    damage = 1;
    speed = 110.0f;

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

    velocity = Normalize({this->setPoints.x - this->currPoint.x, this->setPoints.y - this->currPoint.y});

    float tolerance = 1.0f;

    if (fabs(this->rect.x - this->currPoint.x) < tolerance &&
        fabs(this->rect.y - this->currPoint.y < tolerance))
    {

        currPointIndex++;
        currPoint = endPoints[currPointIndex];
        
    }

}

