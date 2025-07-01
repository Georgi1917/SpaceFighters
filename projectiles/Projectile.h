#pragma once

#include "../include/raylib.h"

class Projectile 
{

    public:
        static int nextId;
        int id;
        Rectangle rect;
        Texture2D sprite;
        Vector2 direction;
        float speed;
        bool isEnemy;

    void virtual Update(float delta) = 0;

    bool CheckOutOfBounds();
    bool operator==(const Projectile &other) const;
    Projectile(Rectangle r, Vector2 dir, float s, bool enemy);
    
};