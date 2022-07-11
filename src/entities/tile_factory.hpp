#ifndef TILE_FACTORY_HPP
#define TILE_FACTORY_HPP

#include "tile.hpp"

namespace tiles{
    Tile floor((const char*)"░", colors::white, colors::blue, true, true);
    Tile wall((const char*)"#", colors::red, colors::white, false, false);
}

#endif