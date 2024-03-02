#include "fighter.hpp"
#include "entity.hpp"
#include "../animations/animation.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "item.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <string>

Fighter::Fighter(Entity* owner){
    this->owner = owner;
    this->equipments = new std::vector<Entity*>(10); 
    this->stealth = false;
}

void Fighter::update(){
    // step on checks
    if (alive){
        std::vector<Entity*> ents = game->map->entityList.entitiesAt(this->owner->posX, this->owner->posY);
        for(int i=0; i<ents.size(); i++){
            if (ents[i]->stepOn!=nullptr){
                ents[i]->stepOn(this->owner);
            }
        }
    }
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

int Fighter::getHealed(int amount){
    int amountHealed = std::min(amount, maxHp-getHp());
    setHp(getHp()+amountHealed);
    Animation* heal = new Animation();
    heal->foreRgb = colors::green;
    std::string healString = std::to_string(amountHealed);
    heal->setFrames({{healString}});
    heal->posX = this->owner->posX;
    heal->speed = 100;
    heal->posY = this->owner->posY;
    heal->damageNumber = true;
    game->animationList.push_back(heal); 
    return amountHealed;
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
            die();
        }
    }
}

void Fighter::die(){
    this->hp = 0;
    alive = false;
    // push all equipment to inventory
    if (this->owner != game->player){
        for(int i=0; i<this->equipments->size(); i++){
            unequipItem(i);
        }
    }
    std::ostringstream mesg;
    mesg<<"The "<<owner->name<<" dies";
    game->log.push_back(mesg.str());
    this->owner->destroy();
    std::ostringstream newName;
    newName<<this->owner->name<<" corpse";
    this->owner->name = newName.str();
    if (this->owner->ai != nullptr) this->owner->ai->alive = false;
}

int Fighter::getHp(){
    return this->hp;
}

Entity* Fighter::getWeapon(){
    return (*this->equipments)[equipSlots::HAND1];
}

bool Fighter::equipItem(Entity *item){
    if (!item->item->equipable) return false;
    if (item->item->equipSlot == equipSlots::NONE) return false; 
    if ( (*this->equipments)[item->item->equipSlot] != nullptr){
        this->owner->inventory.push_back((*this->equipments)[item->item->equipSlot]);
    }
    this->owner->inventory.erase(
            std::remove( 
                this->owner->inventory.begin(),
                this->owner->inventory.end(),
                item)
            );
    (*this->equipments)[item->item->equipSlot] = item;
    return true;
}

bool Fighter::unequipItem(int slot){
    if (slot == equipSlots::NONE) return false;
    if ( (*this->equipments)[slot] == nullptr) return false;
    else {
        Entity* item = (*this->equipments)[slot];
        this->owner->inventory.push_back(item);
        (*this->equipments)[slot] = nullptr;
    }
    return true;
}

void Fighter::giveEquipment(Entity* item){
    //equips item without removing from inventory
    if (!item->item->equipable) return;
    if (item->item->equipSlot == equipSlots::NONE) return;
    (*this->equipments)[item->item->equipSlot] = item;
}