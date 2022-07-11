#ifndef ENTITY_HPP
#define ENTITY_HPP

#pragma once
#include "../colors.hpp"

class Entity {
public:
    int posX;
    int posY;
    color foreRgb;//foreground color
    color backRgb;//background color
    const char* ch;
    Entity();
    ~Entity();
private:
};

#endif