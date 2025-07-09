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

    DrawText("HEALTH : ", 10, 10, 18.0f, WHITE);
    DrawText(TextFormat("SCORE : %i", player.score), 450, 10, 18.0f, WHITE);
    DrawText(TextFormat("BEST SCORE : %i", player.bestScore), 395, 25, 18.0f, WHITE);

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

void UIClass::GameOverScreen(Player player)
{

    int scoreTextWidth = MeasureText(TextFormat("FINAL SCORE : %i", player.score), 30.0f);
    int bestScoreTextWidth = MeasureText(TextFormat("BEST SCORE : %i", player.bestScore), 30.0f);

    int continueTextWidth = MeasureText("PRESS ENTER TO PLAY AGAIN.", 30.0f);
    int exitTextWidth = MeasureText("PRESS ESCAPE TO EXIT THE GAME.", 30.0f);

    if (player.hasLost)
    {

        int lostTextWidth = MeasureText("YOU LOST!", 30.0f);
        DrawText("YOU LOST!", (GetScreenWidth() / 2) - (lostTextWidth / 2), 420, 30.0f, WHITE);

    }
    else if (player.hasWon)
    {

        int wonTextWidth = MeasureText("YOU WON!", 30.0f);
        DrawText("YOU WON!", (GetScreenWidth() / 2) - (wonTextWidth / 2), 420, 30.0f, WHITE);

    }

    DrawText(TextFormat("FINAL SCORE : %i", player.score), (GetScreenWidth() / 2) - (scoreTextWidth / 2), 450, 30.0f, WHITE);
    DrawText(TextFormat("BEST SCORE : %i", player.bestScore), (GetScreenWidth() / 2) - (bestScoreTextWidth / 2), 480, 30.0f, WHITE);
    DrawText("PRESS ENTER TO PLAY AGAIN.", (GetScreenWidth() / 2) - (continueTextWidth / 2), 510, 30.0f, WHITE);
    DrawText("PRESS ESCAPE TO EXIT THE GAME.", (GetScreenWidth() / 2) - (exitTextWidth / 2), 540, 30.0f, WHITE);

}

void UIClass::VisualizeStartMenu()
{

    int titleWidth = MeasureText("SPACE FIGHTERS", 45.0f);
    int moveInstructionWidth = MeasureText("USE THE ARROW KEYS TO MOVE", 30.0f);
    int shootInstructionWidth = MeasureText("HOLD DOWN THE Z KEY TO SHOOT", 30.0f);
    int beginGameTextWidth = MeasureText("PRESS ENTER TO START", 30.0f);
    int endGameTextWidth = MeasureText("PRESS ESCAPE TO EXIT GAME", 30.0f);
    int haveFunTextWidth = MeasureText("HAVE FUN :)", 30.0f);

    DrawText("SPACE FIGHTERS", (GetScreenWidth() / 2) - (titleWidth / 2), 350, 45.0f, WHITE);
    DrawText("USE THE ARROW KEYS TO MOVE", (GetScreenWidth() / 2) - (moveInstructionWidth / 2), 395, 30.0f, WHITE);
    DrawText("HOLD DOWN THE Z KEY TO SHOOT", (GetScreenWidth() / 2) - (shootInstructionWidth / 2), 430, 30.0f, WHITE);
    DrawText("PRESS ENTER TO START", (GetScreenWidth() / 2) - (beginGameTextWidth / 2), 460, 30.0f, WHITE);
    DrawText("PRESS ESCAPE TO EXIT GAME", (GetScreenWidth() / 2) - (endGameTextWidth / 2), 490, 30.0f, WHITE);
    DrawText("HAVE FUN :)", (GetScreenWidth() / 2) - (haveFunTextWidth / 2), 550, 30.0f, WHITE);

}