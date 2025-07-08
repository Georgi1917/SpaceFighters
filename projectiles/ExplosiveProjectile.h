#pragma once

#include "Projectile.h"
#include "../Player.h"

class ExplosiveProjectile : public Projectile
{

    public:

        void Update(float delta) override;
        void Explode(float delta);
        ExplosiveProjectile(Rectangle r, Vector2 dir, float s, bool enemy, int dmg, Player* p);

    private:

        Texture2D explosionSprite;
        Rectangle destRect;
        Rectangle explosionSourceRect;
        Rectangle explosionDestRect;

        int timeToExplode;
        float countdown;
        float explosionRadius;
        float explosionSpeed;
        float maxRadius;
        float rotation;
        Player* player;

        float timerForExpSpriteChange;
        float frameExpDelay;
        int currExpFrame;

        float GetRotation(float targetAngle, float delta);

};