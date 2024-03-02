#ifndef AI_HPP
#define AI_HPP

#include <SDL2/SDL.h>
#include <list>
#include "../algorithms/fov.hpp"

class Entity;

class Ai {
public:
    Ai(Entity* owner);
    Entity* owner;
    std::list<position> path;
    virtual void update();
    virtual ~Ai();
    bool alive;
};

class CritterAi : public Ai {
public:
    CritterAi(Entity* owner) : Ai(owner) {};
    void update();
    void moveOrAttack(int targetX, int targetY);
};

class PlayerAi : public Ai {
public:
    PlayerAi(Entity* owner) : Ai(owner) {};
    bool rightStep = true; // last step taken was right
    void update();
    void moveFromWalkQueue();
    void moveOrAttack(int targetX, int targetY);
    void pickUp();
    void rest();
    void openDoor();
};

#endif
