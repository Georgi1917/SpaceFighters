#pragma once

#include "../include/raylib.h"
#include "../Player.h"

class UIClass
{

    public:
        UIClass();
        void GameOverScreen(Player player);
        void VisualizePlayerStats(Player player);
        void VisualizeStartMenu();

    private:
        Texture2D spHealth;
        Rectangle sourceRect;

};