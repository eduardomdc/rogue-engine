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
    void getHitCritically(int damage);
    void dodge();
    void setHp(int newHp);
    int getHp();
    Entity* getWeapon();
    void equipItem(Entity* item);

    // equipments
    std::vector<Entity*>* equipments;// items are allocated according to equipSlot enum index

    int hp = 1;
    int maxHp = 1;
    // attributes
    int str = 1;
    int agi = 1;
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
