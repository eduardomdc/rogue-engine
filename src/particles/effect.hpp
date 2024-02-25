#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "particle_emitter.hpp"
#include "../entities/glow.hpp"


class Effect {
public:
    Effect();
    void render(); // update checks if the time ran out
    Uint32 lifetime; // duration of effect in ms
    Uint32 start; // start of the effect
    Entity* ent;
};

#endif