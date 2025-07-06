#include "LoadSprites.h"

Texture2D playerProjSprite;
Texture2D basicProjSprite;
Texture2D playerSprite;
Texture2D playerEngineSprite;
Texture2D bomberSprite;
Texture2D diveBomberSprite;
Texture2D DogFighterSprite;
Texture2D HeavyFighterSprite;
Texture2D HeavyFighterEngineSprite;

void LoadSprites()
{

    playerProjSprite = LoadTexture("textures/player_projectiles/player_proj1.png");
    basicProjSprite = LoadTexture("textures/enemy_projectiles/basicProj.png");
    playerSprite = LoadTexture("textures/player/Player_ship (16 x 16).png");
    playerEngineSprite = LoadTexture("textures/player/Boosters (16 x 16).png");
    bomberSprite = LoadTexture("textures/enemies/Bomber.png");
    diveBomberSprite = LoadTexture("textures/enemies/DiveBomber.png");
    DogFighterSprite = LoadTexture("textures/enemies/DogFighter.png");
    HeavyFighterSprite = LoadTexture("textures/enemies/HeavyFighter.png");
    HeavyFighterEngineSprite = LoadTexture("textures/enemies/HeavyFighterEngine.png");

}

void UnloadSprites()
{

    UnloadTexture(playerProjSprite);
    UnloadTexture(basicProjSprite);
    UnloadTexture(playerSprite);
    UnloadTexture(playerEngineSprite);
    UnloadTexture(bomberSprite);
    UnloadTexture(diveBomberSprite);
    UnloadTexture(DogFighterSprite);
    UnloadTexture(HeavyFighterSprite);
    UnloadTexture(HeavyFighterEngineSprite);

}