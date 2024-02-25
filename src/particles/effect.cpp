#include "effect.hpp"
#include "../entities/entity.hpp"

Effect::Effect(){
    this->ent = new Entity();
}

void Effect::render(){
    this->ent->particleEmitter->render();
}