#include "tile_factory.hpp"

Tile* tileFactory::caveFloor(){
    Tile* tile = new Tile((const char*)".", colors::blue, colors::dark, true, true);
    return tile;
}
/**
Tile* tileFactory::caveWall(){
    Tile* tile = new Tile((const char*)"☺", colors::dark, colors::rocky, false, false);
    return tile;
}**/


Tile* tileFactory::makeTile(int tileEnum){
    TileData tile = tileCatalog[tileEnum]; 
    Tile* tileObj = new Tile(tile.ch, tile.foreRgb, tile.backRgb, tile.walkable, tile.walkable);
    return tileObj;
}

TileData tileCatalog[NUMBER_OF_TILES] = {
    {" ", colors::black, colors::black, false, false}, // the nothing tile *_*
    {".", colors::blue, colors::dark, true, true},
    {"#", colors::dark, colors::rocky, false, false},
};
