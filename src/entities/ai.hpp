#ifndef AI_HPP
#define AI_HPP

#include <SDL2/SDL.h>

class Entity;

class Ai {
public:
    int turns = 0;
    virtual void update(Entity *owner);
    virtual ~Ai();
};

class CritterAi : public Ai {
public:
    void update(Entity *owner);
    void moveOrAttack(Entity *owner, int targetX, int targetY);
};

class PlayerAi : public Ai {
public:
    bool rightStep = true; // last step taken was right
    void update(Entity *owner);
    void moveOrAttack(Entity *owner, int targetX, int targetY);
    void rest(Entity *owner);
};

#endif