#ifndef MONSTER_FACTORY_HPP
#define MONSTER_FACTORY_HPP

#include "entity.hpp"

// Wazowski... esqueceu a papelada de ontem à noite!

class monsterFactory {
public:
    static Entity* makeMonster(int monsterEnum, int posX, int posY);
};

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

    //Object * object; // entity is physical object

    //Ai* ai; // entity can do things

    //Creature* creature; // entity is a living creature with needs and organs


} Monster;

enum monsterTypes {
    RAT,
    NUMBER_OF_MONSTERS
};

extern Monster monsterCatalog[NUMBER_OF_MONSTERS];

#endif