#ifndef ACTION_HPP
#define ACTION_HPP

#include "../entities/entity.hpp"
/*
struct pos {
    int x; int y;
} typedef pos;

class Action {
public:
    virtual void execute();
    virtual ~Action();
};

class Attack : Action {
public:
    void execute(Entity* attacker, Entity* target);
};
*/
void attackAction(Entity* attacker, Entity* target);

#endif