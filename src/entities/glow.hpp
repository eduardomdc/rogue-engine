#ifndef GLOW_HPP
#define GLOW_HPP

#include "../colors.hpp"

class Entity;

class Glow {
public:
    Glow(Entity* owner, color GlowColor, short intensity);

    color glowColor;
    color glowOrigColor;
    short intensity;

    void update(Entity* owner);
    void cleanLightReceivers(Entity* owner); // removes all light from this light source to receivers
    void newUpdate(Entity* owner);
};

#endif