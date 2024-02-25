#ifndef ITEM_HPP
#define ITEM_HPP

#pragma once
#include <time.h>
#include <string.h>
#include <iostream>

class Entity;
class Game;

namespace material{
enum material{
    NONE,
    WOOD,
    STONE,
    IRON,
    STEEL,
    SILVER,
    GOLD,
    GEM,
};
}

namespace element{
enum element{
    NONE,
    FIRE,
    WATER,
    WIND,
    ICE,
    ELECTRIC,
};
}

namespace itemType{
enum itemType{
    NONE,
    USABLE,
    TREASURE,
    WEAPON,
    ARMOUR,
    SHIELD,
};
}

namespace equipSlots{
enum equipSlots{
    NONE,
    HEAD,
    NECK,
    BODY,
    LEG,
    FEET,
    HAND1,
    HAND2,
    RING1,
    RING2,
};
}

class Item {
public:
    Item(Entity* owner);
    bool pickable = true;
    bool equipable = false;
    equipSlots::equipSlots equipSlot = equipSlots::NONE;//enum head, body, ring etc...
    Entity* owner;
    // attributes
    int armorClassBonus = 0;
    int damageDie = 0;
    int dieAmount = 0;
    int damageMod = 0; // damage given is: dieAmount d damageDie + damageMod + other mods
    float weight = 0; // Kg
    short type = 0;

    // usable item function
    void (* use)(Entity* user, Entity* item);
private:
};

void HealingPotion(Entity* user, Entity* item);

#endif