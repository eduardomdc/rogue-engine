#ifndef MONSTER_FACTORY_HPP
#define MONSTER_FACTORY_HPP

#include "../entities/entity.hpp"

// Wazowski... esqueceu a papelada de ontem à noite!

typedef void (*aiConstructor)();

Entity* makeMonster(int monsterEnum, int posX, int posY);

Entity* makeRat(int posX, int posY);

typedef struct Monster {
    std::string name; // name
    const char* ch; // should characters be constant? need to change this
    const char* chDestroyed; // character displayed when entity has been destroyed
    const color foreRgb;//foreground color
    const color backRgb;//background color
    const color origRgb;//initial color for randomizing on (for things that dance)
    bool walkable;// can walk on it
    bool transparent; // can see through it
    
    const color foreRgbDestroyed;

    Item* object; // entity is physical object

    // Ai* ai; // entity can do things
    int ai;

    Creature* creature; // entity is a living creature with needs and organs


} Monster;

enum ai {
    CRITTER,
};

enum monsterTypes {
    RAT,
    GOBLIN,
    NUMBER_OF_MONSTERS
};

extern Monster monsterCatalog[NUMBER_OF_MONSTERS];

#endif
