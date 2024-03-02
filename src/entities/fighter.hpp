#ifndef FIGHTER_HPP
#define FIGHTER_HPP

#include <vector>
#include "item.hpp"

class Entity;

class Fighter {
public:
    Fighter(Entity* owner);
    Entity* owner;
    bool alive = true;
    void update(); // update for debuff effects, check for step on traps etc
    void getHit(int damage);
    void getHitCritically(int damage);
    int getHealed(int amount);
    void dodge();
    void setHp(int newHp);
    int getHp();
    Entity* getWeapon();
    bool equipItem(Entity* item);
    void giveEquipment(Entity* item);
    bool unequipItem(int slot);
    void die();

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
    bool stealth;
};

#endif
