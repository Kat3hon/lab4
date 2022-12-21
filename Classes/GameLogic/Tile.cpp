#include "Tile.h"

#include <utility>

Tile::Tile(TileType type, float x, float y) :
    tile_type(type), x_position(x), y_position(y) {}

TileType Tile::getType() {
    return tile_type;
}

bool Tile::isBuildable() {
    return tile_type == Path || tile_type == Field;
}

bool Tile::hasWeapon() {
    return !weapon.expired();
}

void Tile::setWeapon(std::weak_ptr<Weapon> weapon_var) {
    weapon = std::move(weapon_var);
}

float Tile::getX() const {
    return x_position;
}

float Tile::getY() const {
    return y_position;
}

Weapon::Ptr Tile::getWeapon() {
    return weapon.lock();
}