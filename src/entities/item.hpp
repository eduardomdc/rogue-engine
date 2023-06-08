#ifndef ITEM_HPP
#define ITEM_HPP

#pragma once
#include <time.h>
#include <string.h>
#include <iostream>

class Item {
public:
    Item();
    bool pickable = true;
    bool equipable = false;
    int equipSlot = 0;//enum head, body, ring etc...
    
    // attributes
    int armorClassBonus = 0;
    int damageDie = 0;
    int dieAmount = 0;
    int damageMod = 0; // damage given is: dieAmount d damageDie + damageMod + other mods
    float weight = 0; // Kg

private:
};

enum equipSlots{
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

#endif
