#pragma once
#include "Projectile.h"

class PlayerProjectile : public Projectile
{

    public:

        void Update(float delta) override;
        PlayerProjectile(Rectangle r, Vector2 dir, float s, bool enemy);

};