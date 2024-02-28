#include "action.hpp"
#include "../entities/item.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include "../procgen/dice.hpp"
#include "../animations/animation.hpp"
#include "../game.hpp"
#include "../map.hpp"

void attackAction(Entity *attacker, Entity *target){
    Fighter* fighter = attacker->fighter;
    Fighter* victim = target->fighter;
    // turns taken to attack depend on attacker's
    // agility and current weapon modifiers
    int dmgMod = 0;
    int dmg = 0;
    Entity* weapon = fighter->getWeapon();
    dmgMod += fighter->str-10;
    if (weapon){
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
        std::ostringstream mesg;
        mesg<<attacker->name<<" hits "<<target->name<<" luckly for "<<dmg;
        game->log.push_back(mesg.str());
    } else if (rolled > 1){
        if (rolled + (fighter->str-10) < victim->armorClass){
            //std::cout<<target->name<<" dodges "<<attacker->name<<"'s attack"<<std::endl;
            victim->dodge();
            std::ostringstream mesg;
            mesg<<target->name<<" dodges "<<attacker->name<<"'s attack";
            game->log.push_back(mesg.str());
        } else {
            //std::cout << attacker->name << " hits "<< target->name << " for " << dmg << std::endl;
            dmg = std::max(0, dmg);
            victim->getHit(dmg);
            std::ostringstream mesg;
            mesg<<attacker->name<<" hits "<<target->name<<" for "<<dmg;
            game->log.push_back(mesg.str());
        }
    } else {
        // swoooosh
        std::ostringstream mesg;
        mesg<<target->name<<" is greatly missed by "<<attacker->name<<"'s attack";
        game->log.push_back(mesg.str());
        victim->dodge();
    }
    //std::cout<<attacker->name<<" used "<<turnsNeeded<<" turns"<<std::endl;
}

void moveAction(Entity *self, int x, int y){
    self->posX = x;
    self->posY = y;
    //std::cout<<self->name<<" used "<<turnsNeeded<<" to walk"<<std::endl;
}

void openDoorAction(Entity *self, int x, int y){
    if (game->map->tileMap[x][y]->door != nullptr){
        game->map->tileMap[x][y]->door->OpenClose();
    }
}
