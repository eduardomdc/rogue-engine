#include "action.hpp"
#include "../entities/item.hpp"
#include <algorithm>
#include "../procgen/dice.hpp"
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
    // turns taken to attack depend on attacker's
    // agility and current weapon modifiers
    int dmgMod = 0;
    int dmg = 0;
    int turnsNeeded = std::max(1, 21-fighter->agi);
    Entity* weapon = fighter->getWeapon();
    dmgMod += fighter->str-10;
    if (weapon){
        // add weight penalty
        turnsNeeded += std::max(0,
                int(weapon->item->weight*10-fighter->str)
                );
        dmgMod += weapon->item->damageMod;
        dmg = roll(1, weapon->item->damageDie);
    } else {
        dmg = roll(1, 4);
    }
    dmg += dmgMod;

    dmg = std::max(0, dmg);
    // attack roll
    int rolled = roll(1, 20);
    if (rolled == 20){
        dmg = dmg * 2; // CRITICAL!
        victim->getHitCritically(dmg);
    } else if (rolled > 1){
        if ( rolled + (fighter->str-10) < victim->armorClass ){
            victim->dodge();
        } else {
            std::cout << attacker->name << " hits "<< target->name << " for " << dmg << std::endl;
            dmg = std::max(0, dmg);
            victim->getHit(dmg);
        }
    } else {
        // swoooosh
        victim->dodge();
    }
    attacker->ai->turns -= turnsNeeded;
}
