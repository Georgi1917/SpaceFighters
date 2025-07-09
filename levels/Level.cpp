#include "Level.h"
#include <iostream>

Level::Level()
{

    gameTime = 0.0f;
    spawnTime = 0.0f;
    PopulateVector();

}

void Level::PopulateVector()
{

    for (int i = 0; i < 20; i++)
    {

        int count = GetRandomValue(8, 15);

        AddWave(count);

    }
}

void Level::AddWave(int count) 
{

    for (int i = 0; i < count; ++i) 
    {

        int typePool[] = {0, 0, 1, 1, 2, 2, 3, 4};
        int type = typePool[GetRandomValue(0, sizeof(typePool) / sizeof(int) - 1)];

        switch (type) 
        {

            case 0:
                {
                    Vector2 start, end;
                    int dir = GetRandomValue(0, 2);
                    if (dir == 0) 
                    {

                        start = { (float)GetRandomValue(0, 650), -100 };
                        end = { (float)GetRandomValue(0, 650), 1000 };

                    } 
                    else if (dir == 1) 
                    {

                        start = { -100, (float)GetRandomValue(0, 900) };
                        end = { 750, (float)GetRandomValue(0, 900) };

                    } 
                    else 
                    {

                        start = { 750, (float)GetRandomValue(0, 900) };
                        end = { -60, (float)GetRandomValue(0, 900) };

                    }

                    enemies.push_back(std::make_unique<Bomber>(start, end, spawnTime));
                }
                break;

            case 1:
                {

                    Vector2 start, mid, end;
                    int side = GetRandomValue(0, 2);

                    if (side == 0) 
                    {

                        start = { -100, (float)GetRandomValue(100, 800) };
                        end = { 750, (float)GetRandomValue(300, 900) };

                    } 
                    else if (side == 1) 
                    { 

                        start = { 750, (float)GetRandomValue(100, 800) };
                        end = { -100, (float)GetRandomValue(300, 900) };

                    } 
                    else 
                    {

                        start = { (float)GetRandomValue(0, 650), -100 };
                        end = { (float)GetRandomValue(0, 650), 1000 };

                    }

                    mid = { (start.x + end.x) / 2, (start.y + end.y) / 2 };
                    enemies.push_back(std::make_unique<DiveBomber>(start, mid, end, spawnTime));

                }

                break;

            case 2:
                {

                    Vector2 start;
                    std::vector<Vector2> path;
                    int entry = GetRandomValue(0, 3);

                    if (entry == 0) start = { -100, (float)GetRandomValue(0, 900) };
                    else if (entry == 1) start = { 750, (float)GetRandomValue(0, 900) };
                    else start = { (float)GetRandomValue(0, 650), -100 };

                    path.push_back(Vector2{ (float)GetRandomValue(100, 550), (float)GetRandomValue(100, 800) });
                    path.push_back(Vector2{ (float)GetRandomValue(100, 550), (float)GetRandomValue(100, 800) });
                    path.push_back(Vector2{ (float)GetRandomValue(100, 550), (float)GetRandomValue(100, 800) });
                    path.push_back(Vector2{ (float)GetRandomValue(0, 650), 950 });

                    enemies.push_back(std::make_unique<DogFighter>(start, path, spawnTime));

                }

                break;

            case 3:
                {

                    Vector2 start = { (float)GetRandomValue(120, 530), 1000 };
                    Vector2 mid = { start.x, start.y - (float)GetRandomValue(450, 750) };
                    Vector2 end = { start.x, -150 };

                    enemies.push_back(std::make_unique<HeavyFighter>(start, mid, end, spawnTime));

                }

                break;

            // case 4: // Boss (from top only)
            //     {
            //         Vector2 start = { 325, -120 };
            //         enemies.push_back(std::make_unique<Boss>(start, spawnTime));
            //     }
            //     break;

        }

        spawnTime += GetRandomValue(20, 60) / 100.0f;

    }

    spawnTime += GetRandomValue(8, 13);

}
