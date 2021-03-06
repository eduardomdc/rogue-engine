#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "../colors.hpp"
#include "object.hpp"
#include "ai.hpp"
#include "creature.hpp"
#include <SDL2/SDL.h>
#include <string>

class Entity {
public:
    int posX;
    int posY;
    Object * object = NULL; // entity is physical object
    Ai* ai = NULL; // entity can do things
    Creature* creature = NULL; // entity is a living creature with needs and organs
    color foreRgb;//foreground color
    color backRgb;//background color
    color origRgb;//initial color for randomizing on (for things that dance)
    bool walkable = false;// can walk on it
    bool transparent = true; // can see through it
    std::string name; // name
    const char* ch; // should characters be constant? need to change this
    const char* chDestroyed; // character displayed when entity has been destroyed
    color foreRgbDestroyed;
    
    Entity();
    ~Entity();

    void destroy(); // entity is destroyed
    void update();
    void render();
private:
};

#endif