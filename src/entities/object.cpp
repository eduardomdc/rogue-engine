#include "object.hpp"

Object::Object(const char* ch, const color foreRgb, bool walkable, bool transparent, int posX, int posY){
    this->ch = ch;
    this->foreRgb = foreRgb;
    this->walkable = walkable;
    this->transparent = transparent;
    this->posX = posX;
    this->posY = posY;
}