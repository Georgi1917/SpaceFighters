#include "HeavyFighter.h"

HeavyFighter::HeavyFighter(Vector2 sp, Vector2 mp, Vector2 ep)
{

    health = 6;
    damage = 2;
    speed = 60.0f;
    shootDelayTimer = 0.0f;
    stayTime = 4;
    countdown = 0;
    randNum = GenerateRandNum();
    color = PINK;

    hasAppeared = false;

    velocity = { 0 };

    spawnPoint = sp;
    midPoint = mp;
    endPoint = ep;

    rect = {spawnPoint.x, spawnPoint.y, 30.0f, 60.0f};

}

std::unique_ptr<Projectile> HeavyFighter::Shoot(float delta, Player* player)
{



}

void HeavyFighter::Update(float delta)
{



}