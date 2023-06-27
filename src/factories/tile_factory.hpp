#ifndef TILE_FACTORY_HPP
#define TILE_FACTORY_HPP

#include <vector>
#include "../entities/tile.hpp"


typedef struct TileData{
    const char* ch;
    color foreRgb; 
    color backRgb;
    bool walkable;
    bool transparent;
} tileData;

class tileFactory {
public:
    static Tile* caveFloor();
    static Tile* makeTile(int tileEnum, int x, int y);
};

enum tileType {
    NOTHING = 0,
    CAVE_FLOOR,
    CAVE_WALL,
    CAVE_MOSSY_FLOOR,
    GRASS,
    TALL_GRASS,
    NUMBER_OF_TILES
};//thanks brogue!

extern tileData tileCatalog[NUMBER_OF_TILES];

#endif
