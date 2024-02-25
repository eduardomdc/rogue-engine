#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "particle_emitter.hpp"
#include "../entities/glow.hpp"


class Effect {
public:
    Effect();
    void render(); //renders and calls checkEnd
    void update();
    void end();
    void setup();
    Uint32 lifetime; // duration of effect in ms
    Uint32 start; // start of the effect
    Entity* ent;
    Uint32 initialIntensity; // beginning intensity
    Uint32 initialSpawnrate;
};

#endif
