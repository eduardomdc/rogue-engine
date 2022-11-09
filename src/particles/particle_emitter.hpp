#ifndef PARTICLE_EMITTER_HPP
#define PARTICLE_EMITTER_HPP

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <list>
#include "particle.hpp"
#include "../colors.hpp"

class Entity;

class ParticleEmitter {
public:
    ParticleEmitter(Entity* owner);
    void update();
    void render();
    void spawnParticle();
    Entity* owner;
    int x, y;
    std::vector<std::string> chs; // character displayed depend on concentration of particles
    color foreRgb; // particle colors
    std::list<Particle*> particles;
    float dampening; // how much the particle slows down each frame
    int maxParticles;
    Uint32 spawnRate; // in ms
    float angle; // in radians
    float angleSpread; // in radians
    float speed;
    float speedSpread;
    Uint32 lastSpawn;
    SDL_Rect src;
    SDL_Rect dest;
    Uint32 startTime;
    int duration; // in ms
    bool done = false;
};

#endif 