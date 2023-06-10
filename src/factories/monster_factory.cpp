#include "monster_factory.hpp"
#include "../procgen/dice.hpp"
/*
Entity* makeMonster(int monsterEnum, int posX, int posY){
    Monster monster = monsterCatalog[monsterEnum];
    Entity* monsterObj = new Entity();

    monsterObj->posX = posX;
    monsterObj->posY = posY;

    monsterObj->name = monster.name;
    monsterObj->ch = monster.ch;
    monsterObj->chDestroyed = monster.chDestroyed;
    monsterObj->foreRgb = monster.foreRgb;
    monsterObj->chDestroyed = monster.chDestroyed;
    monsterObj->foreRgbDestroyed = monster.foreRgbDestroyed;

    switch (monster.ai){
        case ai::CRITTER:
            monsterObj->ai = new CritterAi();
            break;
    }

    monsterObj->fighter = new Fighter(monsterObj);
    monsterObj->fighter->setHp(2);

    return monsterObj;
};

Monster monsterCatalog[NUMBER_OF_MONSTERS]={
    {
        "Rat", // name
        "r", // char
        "%", // dead char
        colors::grey, // foreColor
        colors::black, // backColor
        colors::black, // origColor
        true, // walkable
        true, // transparent
        colors::red, // foreColorDestroyed
        nullptr,
        ai::CRITTER,
    },
    {
        "Goblin", // name
        "g", // char
        "%", // dead char
        colors::goblinGreen, // foreColor
        colors::black, // backColor
        colors::black, // origColor
        true, // walkable
        true, // transparent
        colors::red, // foreColorDestroyed
        nullptr,
        ai::CRITTER,
    },
};*/
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
    rat->fighter->agi = 12;
    rat->fighter->dex = 9;
    rat->fighter->con = 8;
    rat->fighter->itl = 4;
    rat->fighter->wis = 3;
    rat->fighter->cha = 1;
    rat->fighter->luck = 10;

    return rat;
}
