#include "LoadSprites.h"

Texture2D playerProjSprite;
Texture2D basicProjSprite;
Texture2D doubleProjSprite;
Texture2D explosiveProjSprite;
Texture2D explosiveSprite;
Texture2D HomingProjSprite;

Texture2D playerSprite;
Texture2D playerEngineSprite;
Texture2D bomberSprite;
Texture2D diveBomberSprite;
Texture2D DogFighterSprite;
Texture2D HeavyFighterSprite;
Texture2D HeavyFighterEngineSprite;
Texture2D BossSprite;

Texture2D HeavyFighterDeathSprite;
Texture2D FirstDeathSprite;
Texture2D SecondDeathSprite;

Texture2D healthSprite;

void LoadSprites()
{

    playerProjSprite = LoadTexture("textures/player_projectiles/player_proj1.png");
    basicProjSprite = LoadTexture("textures/enemy_projectiles/basicProj.png");
    doubleProjSprite = LoadTexture("textures/enemy_projectiles/DoubleProj.png");
    explosiveProjSprite = LoadTexture("textures/enemy_projectiles/ExplosiveProj.png");
    explosiveSprite = LoadTexture("textures/enemy_projectiles/Explosion.png");
    HomingProjSprite = LoadTexture("textures/enemy_projectiles/HomingProj.png");

    playerSprite = LoadTexture("textures/player/Player_ship (16 x 16).png");
    playerEngineSprite = LoadTexture("textures/player/Boosters (16 x 16).png");
    bomberSprite = LoadTexture("textures/enemies/Bomber.png");
    diveBomberSprite = LoadTexture("textures/enemies/DiveBomber.png");
    DogFighterSprite = LoadTexture("textures/enemies/DogFighter.png");
    HeavyFighterSprite = LoadTexture("textures/enemies/HeavyFighter.png");
    HeavyFighterEngineSprite = LoadTexture("textures/enemies/HeavyFighterEngine.png");
    BossSprite = LoadTexture("textures/enemies/Boss.png");

    HeavyFighterDeathSprite = LoadTexture("textures/death_sprites/HeavyFighterDeath.png");
    FirstDeathSprite = LoadTexture("textures/death_sprites/death1.png");
    SecondDeathSprite = LoadTexture("textures/death_sprites/death2.png");

    healthSprite = LoadTexture("textures/ui-elements/health.png");

}

void UnloadSprites()
{

    UnloadTexture(playerProjSprite);
    UnloadTexture(basicProjSprite);
    UnloadTexture(doubleProjSprite);
    UnloadTexture(explosiveProjSprite);
    UnloadTexture(explosiveSprite);
    UnloadTexture(HomingProjSprite);

    UnloadTexture(playerSprite);
    UnloadTexture(playerEngineSprite);
    UnloadTexture(bomberSprite);
    UnloadTexture(diveBomberSprite);
    UnloadTexture(DogFighterSprite);
    UnloadTexture(HeavyFighterSprite);
    UnloadTexture(HeavyFighterEngineSprite);
    UnloadTexture(BossSprite);

    UnloadTexture(HeavyFighterDeathSprite);
    UnloadTexture(FirstDeathSprite);
    UnloadTexture(SecondDeathSprite);

    UnloadTexture(healthSprite);

}