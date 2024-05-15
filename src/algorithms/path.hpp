#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include "../game.hpp"

typedef struct pos
{
    unsigned int x;
    unsigned int y;
} pos;

std::vector<pos> find_path(pos src, pos dest, Game* game);

#endif
