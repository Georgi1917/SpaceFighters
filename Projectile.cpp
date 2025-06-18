#include "Projectile.h"

int Projectile::nextId = 1;

Projectile::Projectile() : id(nextId++) {}

bool Projectile::operator==(const Projectile& other) const {
    return id == other.id;
}