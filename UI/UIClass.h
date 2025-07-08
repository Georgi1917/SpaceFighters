#pragma once

#include "../include/raylib.h"
#include "../Player.h"

class UIClass
{

    public:
        UIClass();
        void StartMenu();
        void VisualizePlayerStats(Player player);

    private:
        Texture2D spHealth;
        Rectangle sourceRect;

};