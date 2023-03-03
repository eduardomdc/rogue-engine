#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include <vector>

class Entity;

class Fighter {
public:
    Fighter(Entity* owner);
    Entity* owner;
    bool alive = true;
    void getHit(int damage);
    void setHp(int newHp);
    void attackFighter(Fighter* enemy);
    int getHp();

    // equipments
    std::vector<Entity>* equipments = new std::vector<Entity>(9); // items are allocated according to equipSlot enum index
    
private:
    int hp = 1;
    int maxHp = 1;
    // attributes
    int str = 1;
    int dex = 1;
    int con = 1;
    int itl = 1;//intelligence
    int wis = 1;
    int cha = 1;
    int luck = 0;
    // combat attributes
    int armorClass = 10;
};

#endif