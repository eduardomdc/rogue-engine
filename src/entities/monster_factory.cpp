#include "monster_factory.hpp"

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
        "Wolf", // name
        "W", // char
        "%", // dead char
        colors::snow, // foreColor
        colors::black, // backColor
        colors::black, // origColor
        true, // walkable
        true, // transparent
        colors::red, // foreColorDestroyed
        nullptr,
        ai::CRITTER,
    },
};

