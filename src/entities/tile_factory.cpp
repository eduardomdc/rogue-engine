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


Tile* tileFactory::makeTile(int tileEnum, int x, int y){
    TileData tile = tileCatalog[tileEnum]; 
    Tile* tileObj = new Tile(tile.ch, tile.foreRgb, tile.backRgb, tile.walkable, tile.walkable);
    tileObj->posX = x;
    tileObj->posY = y;
    return tileObj;
}

TileData tileCatalog[NUMBER_OF_TILES] = {
    {" ", colors::black, colors::black, false, false}, // the nothing tile *_*
    {".", colors::caveBlue, colors::dark, true, true},
    {"#", colors::dark, colors::rocky, false, false},
    {",", colors::mossyGreen, colors::dark, true, true},
};
