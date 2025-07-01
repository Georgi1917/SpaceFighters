#pragma once
#include "Projectile.h"

class BasicProjectile : public Projectile
{
    public:
        void Update(float delta) override;
        BasicProjectile(Rectangle r, Vector2 dir, float s, bool enemy);

};