#ifndef TILE_HPP
#define TILE_HPP

#pragma once
#include "entity.hpp"
#include <iostream>

class Tile : public Entity{
public:
    bool walkable;
    bool transparent;
    Tile(const char* ch, const color foreRgb, const color backRgb, bool walkable, bool transparent);

private:
};

#endif