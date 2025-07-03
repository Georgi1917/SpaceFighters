#pragma once

#include "Projectile.h"

class DoubleProjectile : public Projectile
{

    public:
        Rectangle rect2;

        void Update(float delta) override;
        DoubleProjectile(Rectangle r, Vector2 dir, float s, bool enemy, Rectangle r2);

};