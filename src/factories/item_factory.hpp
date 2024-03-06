#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "../entities/entity.hpp"
#include "../map.hpp"

//EQUIPMENTS
Entity* makeLongsword(int x, int y);
Entity* makeShortsword(int x, int y);
Entity* makeMinersHat(int x, int y);
//CONSUMABLES
Entity* makeHealingPotion(int x, int y);
//ENVIROMENT
Entity* makeFireplace(int x, int y);
Entity* makeChest(int x, int y);

#endif

