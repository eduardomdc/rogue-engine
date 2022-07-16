#include "tile_factory.hpp"

Tile* tileFactory::caveFloor(){
    Tile* tile = new Tile((const char*)".", colors::blue, colors::dark, true, true);
    return tile;
}