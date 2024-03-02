#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "../colors.hpp"
#include "item.hpp"
#include "ai.hpp"
#include "fighter.hpp"
#include "glow.hpp"
#include "player.hpp"
#include "../particles/particle_emitter.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <list>
#include <tuple>

class Entity {
public:
    Entity();
    ~Entity();

    void setPos(int x, int y);
    std::tuple<int, int> getPos();
    int posX;
    int posY;
    Item* item = NULL; // entity is physical object
    Ai* ai = NULL; // entity can do things
    Fighter* fighter = NULL; // entity can attack and be attacked
    Glow* glow = NULL;
    ParticleEmitter* particleEmitter = NULL; // entity emits particles
    Player* player = NULL; // entity is player

    color foreRgb;//foreground color
    bool hasBackground = false;
    color backRgb;//background color
    color origRgb;//initial color for randomizing on (for things that dance)
    bool walkable = false;// can walk on it
    bool transparent = true; // can see through it
    std::string name; // name
    const char* ch; // should characters be constant? need to change this
    const char* chDestroyed; // character displayed when entity has been destroyed
    color foreRgbDestroyed;

    lightColor illumination = {0,0,0};

    bool visible;
    void shineLight(short red, short green, short blue); // increase illumination values of entity

    std::vector<Entity*> inventory = {};
    bool pickUp();
    void drop(Entity* item);
    void removeItem(Entity* item);
    void deleteItem(Entity* item);
    
    void destroy(); // entity is destroyed
    void update();
    void render();
    
    void (* stepOn)(Entity* stepper); // function activated when you step on this entity
private:
};

#endif
