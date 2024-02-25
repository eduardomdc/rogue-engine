#include "effect.hpp"
#include "../entities/entity.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <algorithm>

Effect::Effect(){
    this->ent = new Entity();
    this->start = SDL_GetTicks();
}

void Effect::update(){
    Uint32 time = SDL_GetTicks();
    Uint32 delta = time-start;
    if (ent->glow != nullptr){
        ent->glow->intensity = initialIntensity*(lifetime-delta)/lifetime;
    }
    if (ent->particleEmitter != nullptr){
        ent->particleEmitter->spawnRate = initialSpawnrate*(lifetime-delta)/lifetime;
    }
    if (delta>lifetime){
        this->end();
    }
}

void Effect::end(){
    std::vector<Effect*>* gameEffects = &game->map->effects;
    gameEffects->erase(
        std::remove(
            gameEffects->begin(),
            gameEffects->end(),
            this
        )
    );
    delete this;
}

void Effect::render(){
    this->ent->particleEmitter->render();
    update();
}

void Effect::setup(){
    if (this->ent->glow != nullptr){
        initialIntensity = this->ent->glow->intensity;
    }
    if (this->ent->particleEmitter != nullptr){
        initialSpawnrate = this->ent->particleEmitter->spawnRate;
    }
}
