#pragma once

#include "Projectile.h"
#include "../Player.h"

class HomingProjectile : public Projectile
{

    public:

        HomingProjectile(Rectangle r, Vector2 dir, float s, bool enemy, int dmg, Player* p);
        void Update(float delta) override;

    private:

        Player* player;
        bool hasBeenPassed;

};