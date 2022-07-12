#ifndef OBJECT_HPP
#define OBJECT_HPP

#pragma once
#include "entity.hpp"
#include <time.h>
#include <string.h>
#include <iostream>

class Object : public Entity{
public:
    int posX;
    int posY;
    bool walkable;
    bool transparent;
    std::string name;
    
    Object(const char* ch, const color foreRgb, bool walkable, bool transparent, int posX, int posY);

private:
};

#endif