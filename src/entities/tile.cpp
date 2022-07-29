#include "tile.hpp"

Tile::Tile(const char* ch, const color foreRgb, const color backRgb,
            bool walkable, bool transparent){
    this->posX = posX;
    this->posY = posY;
    this->ch = ch;
    this->walkable = walkable;
    this->transparent = transparent;
    this->hasBackground = true;

    this->illumination = {255,155,55};
    
    // randomize color according to color.redRand, color.greenRand...
    this->foreRgb = colorManager::randomize(foreRgb);
    this->backRgb = colorManager::randomize(backRgb);
    // things to do: every tile should be simulated physically
    // *melting points, structural resistance to impact, volumes of gas etc
}