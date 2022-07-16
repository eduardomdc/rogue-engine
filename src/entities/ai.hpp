#ifndef AI_HPP
#define AI_HPP

#include <SDL2/SDL.h>

class Entity;

class Ai {
public:
    virtual void update(Entity *owner);
};

class PlayerAi : public Ai {
public:
    void update(Entity *owner);
    bool moveOrAttack(Entity *owner, int targetX, int targetY);
};

#endif