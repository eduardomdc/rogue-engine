#ifndef ENTITY_HPP
#define ENTITY_HPP


#include "../colors.hpp"
#include "object.hpp"
#include "ai.hpp"
#include "creature.hpp"
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
    Object * object = NULL; // entity is physical object
    Ai* ai = NULL; // entity can do things
    Creature* creature = NULL; // entity is a living creature with needs and organs
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
    std::list<Entity*> lightSources; //list of light sources that affect this entity, used for updating
    void shineLight(short red, short green, short blue); // increase illumination values of entity

    
    void destroy(); // entity is destroyed
    void update();
    void render();
    
private:
};

#endif