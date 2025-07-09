#pragma once
#include <vector>
#include "../enemies/Enemy.h"
#include "../enemies/DiveBomber.h"
#include "../enemies/Enemy.h"
#include "../enemies/DogFighter.h"
#include "../enemies/Bomber.h"
#include "../enemies/HeavyFighter.h"
#include "../enemies/Boss.h"
#include <memory>

class Level
{

    public:
        float gameTime;
        std::vector<std::unique_ptr<Enemy>> enemies;
        Level();

};