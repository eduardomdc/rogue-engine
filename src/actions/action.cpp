#include "action.hpp"
#include "../entities/item.hpp"
#include <algorithm>
#include "../procgen/dice.hpp"
#include "../animations/animation.hpp"

void attackAction(Entity *attacker, Entity *target){
    Fighter* fighter = attacker->fighter;
    Fighter* victim = target->fighter;
    // turns taken to attack depend on attacker's
    // agility and current weapon modifiers
    int dmgMod = 0;
    int dmg = 0;
    int turnsNeeded = std::max(1, 21-int(fighter->agi-10/2));
    Entity* weapon = fighter->getWeapon();
    dmgMod += fighter->str-10;
    if (weapon){
        // add weight penalty
        turnsNeeded += std::max(0,
                2*int(weapon->item->weight*10-fighter->str)
                );
        dmgMod += weapon->item->damageMod;
        dmg = roll(weapon->item->dieAmount, weapon->item->damageDie);
        slashAnimation(target->posX, target->posY); 
    } else {
        punchAnimation(target->posX, target->posY, 1,1);
        dmg = roll(1, 4);
    }
    dmg += dmgMod;

    dmg = std::max(0, dmg);
    // attack roll
    int rolled = roll(1, 20);
    if (rolled >= 20 - fighter->luck){
        dmg = dmg * 2; // CRITICAL!
        victim->getHitCritically(dmg);
        //std::cout<<attacker->name<<" hits "<<target->name<<" for "<<dmg<<std::endl;
    } else if (rolled > 1){
        if (rolled + (fighter->str-10) < victim->armorClass){
            //std::cout<<target->name<<" dodges "<<attacker->name<<"'s attack"<<std::endl;
            victim->dodge();
        } else {
            //std::cout << attacker->name << " hits "<< target->name << " for " << dmg << std::endl;
            dmg = std::max(0, dmg);
            victim->getHit(dmg);
        }
    } else {
        // swoooosh
        victim->dodge();
    }
    //std::cout<<attacker->name<<" used "<<turnsNeeded<<" turns"<<std::endl;
    attacker->ai->turns -= turnsNeeded;
}

void moveAction(Entity *self, int x, int y){
    int turnsNeeded = std::max(1, 21-(self->fighter->agi-10)/2);
    self->posX = x;
    self->posY = y;
    //std::cout<<self->name<<" used "<<turnsNeeded<<" to walk"<<std::endl;
    self->ai->turns -= turnsNeeded;
}

int returnSmallestAction(Entity* self){
    return std::max(1, 21-(self->fighter->agi-10)/2);
}
