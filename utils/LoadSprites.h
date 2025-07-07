#pragma once

#include "../include/raylib.h"

extern Texture2D playerProjSprite;
extern Texture2D basicProjSprite;
extern Texture2D doubleProjSprite;
extern Texture2D explosiveProjSprite;
extern Texture2D explosiveSprite;

extern Texture2D playerSprite;
extern Texture2D playerEngineSprite;
extern Texture2D bomberSprite;
extern Texture2D diveBomberSprite;
extern Texture2D DogFighterSprite;
extern Texture2D HeavyFighterSprite;
extern Texture2D HeavyFighterEngineSprite;

extern Texture2D HeavyFighterDeathSprite;
extern Texture2D FirstDeathSprite;
extern Texture2D SecondDeathSprite;

void LoadSprites();
void UnloadSprites();