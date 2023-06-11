#include "item_factory.hpp"

Entity* makeLongsword(){
    Entity* sword = new Entity();
    sword->ch = "\\";
    sword->name = "Longsword";
    sword->item = new Item();
    sword->foreRgb = colors::white;
    sword->item->equipSlot=equipSlots::HAND1;
    sword->item->damageDie = 8;
    sword->item->damageMod = 0;
    sword->item->dieAmount = 1;
    sword->item->weight = 1;
    sword->item->pickable = true;
    return sword;
}

Entity* makeFireplace(){
    Entity * redFire;
    redFire = new Entity();
    redFire->ch = "*";
    redFire->name = "Fireplace";
    redFire->origRgb = colors::fire;
    redFire->foreRgb = colors::fire;
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
    redFire->glow = new Glow(redFire, colors::fire, 10);
    redFire->item = new Item();
    return redFire;
}
