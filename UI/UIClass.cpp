#include "UIClass.h"
#include <iostream>
#include <string>

UIClass::UIClass()
{

    spHealth = healthSprite;
    sourceRect = {0, 0, 18, 18};

}

void UIClass::VisualizePlayerStats(Player player)
{

    std::string score = std::to_string(player.score);

    DrawText("HEALTH : ", 10, 10, 18.0f, WHITE);
    DrawText("SCORE : ", 450, 10, 18.0f, WHITE);
    DrawText(score.c_str(), 530, 10, 18.0f, WHITE);

    int widthOfText = MeasureText("HEALTH : ", 12.0f);
    float step = 0.5f;

    for (int i = 1; i <= player.health; i++)
    {

        DrawTexturePro(spHealth, sourceRect,
                       {((float)widthOfText * step) + 65, 8, sourceRect.width * 1.2f, sourceRect.height * 1.2f},
                        Vector2{0, 0}, 0.0f, WHITE);
        
        step += 0.3f;

    }

}