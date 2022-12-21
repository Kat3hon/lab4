#pragma once

#include "TileType.h"
#include "Weapon.h"

#include <memory>

class Tile {

    TileType tile_type;
    std::weak_ptr<Weapon> weapon;

    float x_position{};
    float y_position{};

public:

    static float tile_width;
    static float tile_height;

    using Ptr = std::shared_ptr<Tile>;

    Tile() = default;

    explicit Tile(TileType type, float x, float y);

    TileType getType();

    bool isBuildable();

    bool hasWeapon();

    void setWeapon(std::weak_ptr<Weapon> weapon);

    Weapon::Ptr getWeapon();

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;
};


