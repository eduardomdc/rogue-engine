#ifndef TILE_HPP
#define TILE_HPP

#pragma once
#include "entity.hpp"
#include <iostream>

class Door;

class Tile : public Entity{
public:
    bool walkable;
    bool transparent;
    Door* door = NULL;
    Tile(const char* ch, const color foreRgb, const color backRgb, bool walkable, bool transparent);

private:
};

class Door{
public:
    bool locked;
    bool open;
    Tile* owner;
    Door(Tile* owner, Entity* key); 
    void OpenClose();
};


#endif
