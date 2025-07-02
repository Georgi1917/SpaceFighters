#pragma once

#include "Projectile.h"
#include "../Player.h"

class ExplosiveProjectile : public Projectile
{

    public:

        void Update(float delta) override;
        void Explode(float delta);
        bool CheckForCollisionWithPlayer(Player player);
        ExplosiveProjectile(Rectangle r, Vector2 dir, float s, bool enemy, Player* p);

    private:

        int timeToExplode;
        float countdown;
        float explosionRadius;
        float explosionSpeed;
        float maxRadius;
        Player* player;

};