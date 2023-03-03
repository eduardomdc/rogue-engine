#include "fighter.hpp"
#include "entity.hpp"

Fighter::Fighter(Entity* owner){
    this->owner = owner;
}

void Fighter::getHit(int damage){
    setHp(getHp() - damage);
}

void Fighter::setHp(int newHp){
    if (this->hp > 0){
        if (newHp > maxHp){
            this->hp = maxHp;
        } else this->hp = newHp;
        if ( this->hp <= 0){
            alive = false;
        }
    }
}

int Fighter::getHp(){
    return this->hp;
}

void Fighter::attackFighter(Fighter* enemy){
    
}