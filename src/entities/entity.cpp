#include "entity.hpp"
#include "tile.hpp"

#include "../draw/tile_manager.hpp"

Entity::Entity(){};

Entity::~Entity(){};

void Entity::render(Map* map){
    if ((this->posY>=0 && this->posY< map->mapHeight) && (this->posX>=0 && this->posX<map->mapWidth)){
        if ( (this->posY >= map->topSide && this->posY < map->bottomSide) && (this->posX >= map->leftSide && this->posX < map->rightSide)){
            *map->tile = map->tileMap[this->posX][this->posY]; // get tile at entity location for background color matching
        } else return; // out of render area
    } else return; // out of map
    int screenPosX = this->posX - map->leftSide + map->mapOffsetX;
    int screenPosY = this->posY - map->topSide + map->mapOffsetY;
    map->dest.x = screenPosX * map->tileWidth;
    map->dest.y = screenPosY * map->tileHeight;

    TileManager::drawAscii(map->codepage,
        map->src,
        map->dest,
        this->ch,
        this->foreRgb, 
        map->tile->backRgb, 
        map->tileHeight, 
        map->tileWidth, 16, 16);
};