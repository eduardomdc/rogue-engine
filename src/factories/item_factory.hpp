#ifndef ITEM_FACTORY_HPP
#define ITEM_FACTORY_HPP

#include "../entities/entity.hpp"
#include "../map.hpp"

Entity* makeLongsword(int x, int y);
Entity* makeHealingPotion(int x, int y);
Entity* makeFireplace(int x, int y);

#endif

