#pragma once

#include "include/raylib.h"

class Projectile {

    public:
        static int nextId;
        int id;
        Rectangle rect;
        float speed;
        int yDirection;

    bool operator==(const Projectile &other) const;
    Projectile();
};