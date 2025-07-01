#pragma once

#include "Projectile.h"

class ExplosiveProjectile : public Projectile
{

    public:

        void Update(float delta) override;
        void Explode(float delta); 
        ExplosiveProjectile(Rectangle r, Vector2 dir, float s, bool enemy);

    private:

        int timeToExplode;
        float countdown;
        float explosionRadius;
        float explosionSpeed;
        float maxRadius;

};