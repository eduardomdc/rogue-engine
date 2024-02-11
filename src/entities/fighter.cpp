#include "fighter.hpp"
#include "entity.hpp"
#include "../animations/animation.hpp"
#include "../game.hpp"
#include "item.hpp"
#include <algorithm>
#include <cstdlib>
#include <string>

Fighter::Fighter(Entity* owner){
    this->owner = owner;
    this->equipments = new std::vector<Entity*>(10); 
    this->stealth = false;
}

void Fighter::getHit(int damage){
    setHp(getHp() - damage);
    Animation* dmg = new Animation();
    if (damage){
        dmg->foreRgb = colors::red;
        std::string damageString = std::to_string(damage);
        dmg->setFrames({{damageString}});
    } else {
        dmg->foreRgb = colors::lightBlue;
        dmg->setFrames({{"0"}});
        
    }
    dmg->posX = this->owner->posX;
    dmg->speed = 100;
    dmg->posY = this->owner->posY;
    dmg->damageNumber = true;
    game->animationList.push_back(dmg); 
}

void Fighter::getHitCritically(int damage){
    setHp(getHp() - damage);
    Animation* dmg = new Animation();
    if (damage){
        dmg->foreRgb = colors::yellow;
        std::string damageString = std::to_string(damage);
        damageString.append("!");
        dmg->setFrames({{damageString}});
    } else {
        dmg->foreRgb = colors::lightBlue;
        dmg->setFrames({{"0!"}});
    }
    dmg->posX = this->owner->posX;
    dmg->speed = 150;
    dmg->posY = this->owner->posY;
    dmg->damageNumber = true;
    game->animationList.push_back(dmg); 
}

void Fighter::dodge(){
    Animation* miss = new Animation();
    miss->setFrames({{"~"}});
    miss->foreRgb = colors::lightBlue;
    miss->posX = this->owner->posX;
    miss->posY = this->owner->posY;
    miss->speed = 50;
    miss->damageNumber = true;
    game->animationList.push_back(miss);
}

void Fighter::setHp(int newHp){
    if (this->hp > 0){
        if (newHp > maxHp){
            this->hp = maxHp;
        } else this->hp = newHp;
        if ( this->hp <= 0){
            this->hp = 0;
            alive = false;
            this->owner->destroy();
        }
    }
}

int Fighter::getHp(){
    return this->hp;
}

Entity* Fighter::getWeapon(){
    return (*this->equipments)[equipSlots::HAND1];
}

void Fighter::equipItem(Entity *item){
    if (!item->item->equipable) return;
    if (item->item->equipSlot == equipSlots::NONE) return; 
    if ( (*this->equipments)[item->item->equipSlot] ){
        this->owner->inventory.push_back((*this->equipments)[item->item->equipSlot]);
    }
    this->owner->inventory.erase(
            std::remove( 
                this->owner->inventory.begin(),
                this->owner->inventory.end(),
                item)
            );
    (*this->equipments)[item->item->equipSlot] = item;
}
