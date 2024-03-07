#include "item_factory.hpp"
#include "../map.hpp"
#include "../actions/action.hpp"

Entity* makeLongsword(int x, int y){
    Entity* sword = new Entity();
    sword->ch = "\\";
    sword->name = "Longsword";
    sword->item = new Item(sword);
    sword->foreRgb = colors::white;
    sword->item->type = itemType::WEAPON;
    sword->item->equipSlot=equipSlots::HAND1;
    sword->item->damageDie = 8;
    sword->item->damageMod = 0;
    sword->item->dieAmount = 1;
    sword->item->pickable = true;
    sword->item->equipable = true;
    sword->posX = x;
    sword->posY = y;
    return sword;
}

Entity* makeShortsword(int x, int y){
    Entity* sword = new Entity();
    sword->ch = "\\";
    sword->name = "Shortsword";
    sword->item = new Item(sword);
    sword->foreRgb = colors::white;
    sword->item->type = itemType::WEAPON;
    sword->item->equipSlot=equipSlots::HAND1;
    sword->item->damageDie = 6;
    sword->item->damageMod = 0;
    sword->item->dieAmount = 1;
    sword->item->pickable = true;
    sword->item->equipable = true;
    sword->posX = x;
    sword->posY = y;
    return sword;
}

Entity* makeMinersHat(int x, int y){
    Entity* hat = new Entity();
    hat->ch = "^";
    hat->name = "Miner's Hat";
    hat->item = new Item(hat);
    hat->foreRgb = colors::yellow;
    hat->glow = new Glow(hat, colors::yellowFire, 10);
    hat->item->type = itemType::ARMOUR;
    hat->item->equipSlot = equipSlots::HEAD;
    hat->item->pickable = true;
    hat->item->equipable = true;
    hat->posX = x;
    hat->posY = y;
    return hat;
}

Entity* makeHealingPotion(int x, int y){
    Entity* potion = new Entity();
    potion->ch = "¡";
    potion->name = "Healing Potion";
    potion->foreRgb = colors::red;
    potion->item = new Item(potion);
    potion->item->type = itemType::USABLE;
    potion->item->pickable = true;
    potion->posX = x;
    potion->posY = y;
    potion->item->use = &HealingPotion;
    return potion;
}

Entity* makeFireplace(int x, int y){
    Entity * redFire;
    redFire = new Entity();
    redFire->ch = "*";
    redFire->name = "Fireplace";
    redFire->origRgb = colors::fire;
    redFire->foreRgb = colors::fire;
    redFire->stepOn = &stepOnFire;
    ParticleEmitter* pemit;
    pemit = new ParticleEmitter(redFire);
    pemit->chs = {".", ",","*","`"};
    pemit->foreRgb = colors::yellow;
    pemit->maxParticles = 10;
    pemit->spawnRate = 500;
    pemit->angle = -M_PI/2;
    pemit->speed = 0.01;
    pemit->speedSpread = 0.005;
    pemit->angleSpread = M_PI/6;
    pemit->duration = 2000;
    redFire->particleEmitter = pemit;
    redFire->glow = new Glow(redFire, colors::fire, 20);
    redFire->posX = x;
    redFire->posY = y;
    return redFire;
}

Entity* makeTikiTorch(int x, int y){
    Entity * redFire;
    redFire = new Entity();
    redFire->ch = "î";
    redFire->name = "Tiki Torch";
    redFire->origRgb = colors::fire;
    redFire->foreRgb = colors::fire;
    ParticleEmitter* pemit;
    pemit = new ParticleEmitter(redFire);
    pemit->chs = {".", ",","*","`"};
    pemit->foreRgb = colors::yellow;
    pemit->maxParticles = 10;
    pemit->spawnRate = 500;
    pemit->angle = -M_PI/2;
    pemit->speed = 0.02;
    pemit->speedSpread = 0.005;
    pemit->angleSpread = M_PI/6;
    pemit->duration = 1000;
    redFire->particleEmitter = pemit;
    redFire->glow = new Glow(redFire, colors::fire, 20);
    redFire->posX = x;
    redFire->posY = y;
    return redFire;
}

Entity* makeChest(int x, int y){
    Entity* chest;
    chest = new Entity();
    chest->ch = "▄";
    chest->name = "Wooden Chest";
    chest->foreRgb = colors::brown;
    chest->posX = x;
    chest->posY = y;
    return chest;
}
