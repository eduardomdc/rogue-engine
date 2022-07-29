#ifndef GLOW_HPP
#define GLOW_HPP

#include "../colors.hpp"

class Entity;

class Glow {
public:
    Glow(Entity* owner, color GlowColor, short intensity);

    color glowColor;
    short intensity;

    void update(Entity* owner);
};

#endif