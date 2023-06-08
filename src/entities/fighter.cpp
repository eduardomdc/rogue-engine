#include "fighter.hpp"
#include "entity.hpp"
#include "../animations/animation.hpp"
#include "../game.hpp"
#include <string>

Fighter::Fighter(Entity* owner){
    this->owner = owner;
}

void Fighter::getHit(int damage){
    setHp(getHp() - damage);
    Animation* dmg = new Animation();
    dmg->foreRgb = colors::red;
    std::string damageString = std::to_string(damage);
    damageString.append("!");
    dmg->setFrames({damageString});
    dmg->posX = this->owner->posX;
    dmg->speed = 100;
    dmg->posY = this->owner->posY;
    dmg->damageNumber = true;
    game->animationList.push_back(dmg); 
}

void Fighter::getHitCritically(int damage){
    setHp(getHp() - damage);
    Animation* dmg = new Animation();
    dmg->foreRgb = colors::yellow;
    std::string damageString = std::to_string(damage);
    damageString.append("!");
    dmg->setFrames({damageString});
    dmg->posX = this->owner->posX;
    dmg->speed = 150;
    dmg->posY = this->owner->posY;
    dmg->damageNumber = true;
    game->animationList.push_back(dmg); 
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
