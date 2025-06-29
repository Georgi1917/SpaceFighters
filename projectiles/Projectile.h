#pragma once

#include "../include/raylib.h"

class Projectile 
{

    public:
        static int nextId;
        int id;
        Rectangle rect;
        Vector2 direction;
        float speed;
        bool isEnemy;

    void Update(float delta);
    bool CheckOutOfBounds();
    bool operator==(const Projectile &other) const;
    Projectile();
    
};