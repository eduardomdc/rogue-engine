#include "tile.hpp"

Tile::Tile(const char* ch, const color foreRgb, const color backRgb,
            bool walkable, bool transparent){
    this->ch = ch;
    this->walkable = walkable;
    this->transparent = transparent;
    this->hasBackground = true;

    this->illumination = {0,0,0};
    
    // randomize color according to color.redRand, color.greenRand...
    this->foreRgb = colorManager::randomize(foreRgb);
    this->backRgb = colorManager::randomize(backRgb);
    // things to do: every tile should be simulated physically
    // *melting points, structural resistance to impact, volumes of gas etc
}

Door::Door(Tile* owner, Entity* key){
    this->owner = owner;
    this->open = false;
    if (key == nullptr){
        this->locked = false;
    } else {
        this->locked = true;
    }
}

void Door::OpenClose() {
    if (!open){
        if (!this->locked) {
            this->owner->ch = "/";
            this->owner->walkable = true;
            this->owner->transparent = true;
            this->open = !this->open;
        }
    } else {
        this->owner->ch = "+";
        this->owner->walkable = false;
        this->owner->transparent = false;
        this->open = !this->open;
    }
}
