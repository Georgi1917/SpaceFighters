#include "Level.h"
#include <iostream>

Level::Level()
{

    gameTime = 0.0f;

    std::cout << "HELLOOOOO" << "n";

    enemies.push_back(std::make_unique<DogFighter>(
        Vector2{50, -20}, std::vector<Vector2>{
            {50, 700}, {1000, 700}
        }, 5
    ));
    // enemies.push_back(std::make_unique<DogFighter>(
    //     Vector2{50, -50}, std::vector<Vector2>{
    //         {50, 700}, {1000, 700}
    //     }, 5
    // ));
    // enemies.push_back(std::make_unique<DogFighter>(
    //     Vector2{50, -80}, std::vector<Vector2>{
    //         {50, 700}, {1000, 700}
    //     }, 5
    // ));
    // enemies.push_back(std::make_unique<DogFighter>(
    //     Vector2{50, -110}, std::vector<Vector2>{
    //         {50, 700}, {1000, 700}
    //     }, 5
    // ));

}