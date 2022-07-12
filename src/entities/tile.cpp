#include "tile.hpp"

Tile::Tile(const char* ch, const color foreRgb, const color backRgb,
            bool walkable, bool transparent){
    this->posX = posX;
    this->posY = posY;
    this->ch = ch;
    this->walkable = walkable;
    this->transparent = transparent;
    
    // randomize color according to color.redRand, color.greenRand...
    this->foreRgb = foreRgb;
    this->backRgb = backRgb;
    this->foreRgb.red += rand() % (foreRgb.redRand + 1);
    this->foreRgb.green += rand() % (foreRgb.greenRand + 1);
    this->foreRgb.blue += rand() % (foreRgb.blueRand + 1);
    this->backRgb.red += rand() % (backRgb.redRand + 1);
    this->backRgb.green += rand() % (backRgb.greenRand + 1);
    this->backRgb.blue += rand() % (backRgb.blueRand + 1);
    
    // things to do: every tile should be simulated physically
    // *melting points, structural resistance to impact, volumes of gas etc
}