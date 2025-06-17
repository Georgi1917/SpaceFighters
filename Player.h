#pragma once
#include "include/raylib.h"


class Player {

    public:
        Rectangle rect;
        float health;
        int score;
        float damage;

        void Shoot();
        void Move(float delta);


};