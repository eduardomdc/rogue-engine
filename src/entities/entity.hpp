#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "../colors.hpp"
#include "object.hpp"
#include <string>

class Entity {
public:
    int posX;
    int posY;
    //Object * object = NULL; // entity is object
    color foreRgb;//foreground color
    color backRgb;//background color
    bool walkable = false;// can walk on it
    bool transparent = true; // can see through it
    std::string name; // name
    const char* ch; // should characters be constant? need to change this
    Entity();
    ~Entity();

    void render(class Map* map);
private:
};

#endif