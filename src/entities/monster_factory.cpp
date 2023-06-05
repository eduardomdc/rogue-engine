#include "monster_factory.hpp"
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

    rat->name = "Rat";
    rat->ch = "r";
    rat->chDestroyed = "%";
    rat->foreRgb = colors::grey;
    rat->foreRgbDestroyed = colors::red;
    rat->ai = new CritterAi();
    rat->fighter = new Fighter(rat);
    rat->fighter->setHp(2);

    return rat;
}
