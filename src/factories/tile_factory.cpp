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

Tile* makeWoodenDoor(int x, int y){
    Tile* door;
    door = new Tile("+", colors::grey, colors::yellow, false, false);
    door->name = "Wooden Door";
    door->posX = x;
    door->posY = y;
    door->door = new Door(door, nullptr);
    return door;
}

Tile* tileFactory::makeTile(int tileEnum, int x, int y){
    TileData tile = tileCatalog[tileEnum]; 
    Tile* tileObj = new Tile(tile.ch, tile.foreRgb, tile.backRgb, tile.walkable, tile.transparent);
    tileObj->posX = x;
    tileObj->posY = y;
    return tileObj;
}

TileData tileCatalog[NUMBER_OF_TILES] = {
    {" ", colors::black, colors::black, false, false}, // the nothing tile *_*
    {".", colors::caveBlue, colors::dark, true, true},
    {"#", colors::dark, colors::white, false, false},
    {"\"", colors::mossyGreen, colors::dark, true, true},
    {"\"", colors::grassyGreen, colors::darkGrassy, true, true},
    {"⌠", colors::grassyGreen, colors::darkGrassy, true, false},
    {".", colors::white, colors::grey, true, true},
    {"#", colors::dark, colors::white, false, false},
};
