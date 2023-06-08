#include "action.hpp"
/*
void Attack::execute(Entity* attacker, Entity* target){
    //attacker->fighter->attackFighter(target->fighter);
    Fighter* fighter = attacker->fighter;
    Fighter* victim = target->fighter;
    attacker->ai->turns = 150;
    victim->getHit(3);
    //Animation* dmgCount = new Animation();
    //dmg->foreRgb =
}*/

void attackAction(Entity *attacker, Entity *target){
    Fighter* fighter = attacker->fighter;
    Fighter* victim = target->fighter;
    attacker->ai->turns = 150;
    victim->getHit(3);
}
