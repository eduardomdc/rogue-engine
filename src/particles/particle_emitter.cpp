#include "particle_emitter.hpp"
#include "../entities/entity.hpp"
#include <iostream>

ParticleEmitter::ParticleEmitter(Entity* owner){
    lastSpawn = SDL_GetTicks();
    startTime = SDL_GetTicks();
    this->owner = owner;
}

void ParticleEmitter::render(){
    std::_List_iterator<Particle*> it;

    it = particles.begin();
    while (it != particles.end()){
        Particle* p = *it;
        p->render();
        it++;
    }
}

float randFloat(float min, float max){
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

void ParticleEmitter::spawnParticle(){
    Particle* p = new Particle();
    p->posX = this->x + randFloat(0,1);
    p->posY = this->y + randFloat(0,1);
    p->ch = chs[rand()%chs.size()];
    p->velocity = {std::cos(this->angle + randFloat(-this->angleSpread,this->angleSpread)), std::sin(this->angle + randFloat(-this->angleSpread,this->angleSpread))};
    float randomSpeed = this->speed + randFloat(-this->speedSpread,this->speedSpread);
    p->velocity[0] *= randomSpeed;
    p->velocity[1] *= randomSpeed;
    p->startTime = SDL_GetTicks();
    p->duration = duration;
    p->foreRgb = foreRgb;
    particles.push_back(p);
    lastSpawn = SDL_GetTicks();
}

void ParticleEmitter::update(){
    this->x = owner->posX;
    this->y = owner->posY;
    if (SDL_GetTicks() - lastSpawn > spawnRate){
        spawnParticle();
    }

    std::_List_iterator<Particle*> it;
    it = particles.begin();
    while (it != particles.end()){
        Particle* p = *it;
        p->update();
        if (p->done == true){
            it = particles.erase(it);
        } else {
            it++;
        }
    }
    this->render();
}