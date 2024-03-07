#include "monster_factory.hpp"
#include "../procgen/dice.hpp"
#include "item_factory.hpp"

Entity* makeRat(int posX, int posY){
    Entity* rat = new Entity();

    rat->posX = posX;
    rat->posY = posY;

    rat->name = "Giant Rat";
    rat->ch = "r";
    rat->chDestroyed = "%";
    rat->foreRgb = colors::grey;
    rat->foreRgbDestroyed = colors::red;
    rat->ai = new CritterAi(rat);
    rat->fighter = new Fighter(rat);
    rat->fighter->maxHp = roll(1,4);
    rat->fighter->setHp(rat->fighter->maxHp);


    rat->fighter->str = 8;
    rat->fighter->agi = 10;
    rat->fighter->dex = 9;
    rat->fighter->con = 8;
    rat->fighter->itl = 4;
    rat->fighter->wis = 3;
    rat->fighter->cha = 1;
    rat->fighter->luck = 0;

    return rat;
}

Entity* makeZombie(int posX, int posY){
    Entity* zombie = new Entity();

    zombie->posX = posX;
    zombie->posY = posY;

    zombie->name = "Undead";
    zombie->ch = "Z";
    zombie->chDestroyed = "%";
    zombie->foreRgb = colors::mossyGreen;
    zombie->foreRgbDestroyed = colors::red;
    zombie->ai = new SlowCritterAi(zombie);
    zombie->fighter = new Fighter(zombie);
    zombie->fighter->maxHp = roll(1,8);
    zombie->fighter->setHp(zombie->fighter->maxHp);


    zombie->fighter->str = 8;
    zombie->fighter->agi = 5;
    zombie->fighter->dex = 4;
    zombie->fighter->con = 8;
    zombie->fighter->itl = 4;
    zombie->fighter->wis = 3;
    zombie->fighter->cha = 1;
    zombie->fighter->luck = 0;

    return zombie;
}

Entity* makeGoblin(int posX, int posY){
    Entity* goblin = new Entity();

    goblin->posX = posX;
    goblin->posY = posY;

    goblin->name = "Goblin";
    goblin->ch = "g";
    goblin->chDestroyed = "%";
    goblin->foreRgb = colors::goblinGreen;
    goblin->foreRgbDestroyed = colors::red;
    goblin->ai = new CritterAi(goblin);
    goblin->fighter = new Fighter(goblin);
    goblin->fighter->maxHp = roll(1,6);
    goblin->fighter->setHp(goblin->fighter->maxHp);
    goblin->fighter->giveEquipment(makeShortsword(posX, posY));
    goblin->fighter->str = 11;
    goblin->fighter->agi = 10;
    goblin->fighter->dex = 10;
    goblin->fighter->con = 8;
    goblin->fighter->itl = 6;
    goblin->fighter->wis = 4;
    goblin->fighter->cha = 1;
    goblin->fighter->luck = 1;

    return goblin;
}