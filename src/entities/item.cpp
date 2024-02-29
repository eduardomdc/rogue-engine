#include "item.hpp"
#include <cstddef>
#include <sstream>
#include "../game.hpp"
#include "../draw/draw_ui.hpp"
#include "../particles/effect.hpp"
#include "../particles/particle_emitter.hpp"
#include "../entities/glow.hpp"
#include "../map.hpp"

Item::Item(Entity* owner){
    this->owner = owner;
}

void HealingPotion(Entity *user, Entity* item){
    if (user->fighter == nullptr) return;
    int amountHealed = user->fighter->getHealed(user->fighter->maxHp);
    // healing effect
    Effect* ef = new Effect();
    ef->lifetime = 400;
    ParticleEmitter* pemit = new ParticleEmitter(ef->ent);
    pemit->chs = {".", "+","*","+","#"};
    pemit->foreRgb = colors::red;
    pemit->maxParticles = 10;
    pemit->spawnRate = 5;
    pemit->angle = -M_PI/2;
    pemit->speed = 0.1;
    pemit->speedSpread = 0.005;
    pemit->angleSpread = M_PI;
    pemit->duration = 2000;
    ef->ent->glow = new Glow(ef->ent, colors::red, 50);
    ef->ent->particleEmitter = pemit;
    ef->ent->posX = user->posX;
    ef->ent->posY = user->posY;
    ef->setup();
    game->map->effects.push_back(ef);
    std::ostringstream mesg;
    mesg<<user->name<<" drinks "<<item->name<<" and is healed by "<<amountHealed;
    game->log.push_back(mesg.str());
    user->deleteItem(item);
}
