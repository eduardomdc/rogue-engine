#include "tile_factory.hpp"

Tile* tileFactory::caveFloor(){
    Tile* tile = new Tile((const char*)".", colors::blue, colors::dark, true, true);
    return tile;
}

Tile* tileFactory::caveWall(){
    Tile* tile = new Tile((const char*)"░", colors::dark, colors::rocky, false, false);
    return tile;
}