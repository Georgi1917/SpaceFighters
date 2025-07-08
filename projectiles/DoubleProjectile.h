#pragma once

#include "Projectile.h"
#include "../Player.h"

class DoubleProjectile : public Projectile
{

    public:
        Rectangle rect2;
        Player* player;

        void Update(float delta) override;
        DoubleProjectile(Rectangle r, Vector2 dir, float s, bool enemy, int dmg, Rectangle r2, Player* p);
        bool CheckForPlayerHit();

};