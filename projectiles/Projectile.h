#pragma once

#include "../include/raylib.h"
#include "../utils/LoadSprites.h"

class Projectile 
{

    public:
        static int nextId;
        int id;
        int damage;
        Rectangle rect;
        Texture2D sprite;
        Vector2 direction;
        float speed;
        bool isEnemy;
        bool toBeDeleted;

    void virtual Update(float delta) = 0;

    bool CheckOutOfBounds();
    bool operator==(const Projectile &other) const;
    Projectile(Rectangle r, Vector2 dir, float s, bool enemy, int dmg);

    protected:
        Rectangle sourceRect;

        float frameDelay;
        int currFrame;
        float timerForSpriteChange;
        float Length(Vector2 vec) const;
        Vector2 Normalize(Vector2 vec) const;
    
};