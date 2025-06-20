#pragma once

#include "include/raylib.h"

class Projectile {

    public:
        static int nextId;
        int id;
        Rectangle rect;
        float speed;
        Vector2 direction;

    bool operator==(const Projectile &other) const;
    Projectile();
};