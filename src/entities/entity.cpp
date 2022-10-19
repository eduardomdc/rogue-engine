#include "entity.hpp"
#include "tile.hpp"
#include <iostream>
#include <algorithm>
#include <list>
#include "../draw/tile_manager.hpp"
#include "../game.hpp"
#include "../map.hpp"

Entity::Entity(){};

Entity::~Entity(){};

void Entity::setPos(int x, int y){
    if (this->glow){

    }
    this->posX = x;
    this->posY = y;
}

std::tuple<int,int> Entity::getPos(){
    return {this->posX, this->posY};
}

void Entity::render(){
    Map* map = game->map;
    if ((this->posY>=0 && this->posY< map->mapHeight) && (this->posX>=0 && this->posX<map->mapWidth)){
        if ( (this->posY >= map->topSide && this->posY < map->bottomSide) && (this->posX >= map->leftSide && this->posX < map->rightSide)){
            *map->tile = map->tileMap[this->posX][this->posY]; // get tile at entity location for background color matching
        } else return; // out of render area
    } else return; // out of map
    
    int screenPosX = this->posX - map->leftSide + map->mapOffsetX;
    int screenPosY = this->posY - map->topSide + map->mapOffsetY;
    map->dest.x = screenPosX * map->tileWidth;
    map->dest.y = screenPosY * map->tileHeight;
    if (this->glow == nullptr){
        // multiply native color by illumination color

        color lightColored = this->foreRgb;

        lightColored.red *= this->illumination.red/255.0;
        lightColored.blue *= this->illumination.blue/255.0;
        lightColored.green *= this->illumination.green/255.0;

        
        if (this->hasBackground){
            color lightColoredBg = this->backRgb;

            lightColoredBg.red *= this->illumination.red/255.0;
            lightColoredBg.blue *= this->illumination.blue/255.0;
            lightColoredBg.green *= this->illumination.green/255.0;

            int screenPosX = this->posX - map->leftSide + map->mapOffsetX;
            int screenPosY = this->posY - map->topSide + map->mapOffsetY;
            map->dest.x = screenPosX * map->tileWidth;
            map->dest.y = screenPosY * map->tileHeight;

            TileManager::drawAscii(
                map->codepage,
                map->src,
                map->dest,
                this->ch,
                lightColored,
                lightColoredBg,
                map->tileHeight, 
                map->tileWidth, 16, 16
            );
        } else {
            TileManager::drawAscii(
            map->codepage,
            map->src,
            map->dest,
            this->ch,
            lightColored,
            map->tileHeight, 
            map->tileWidth, 16, 16);
        }
    } else {
        TileManager::drawAscii(
            map->codepage,
            map->src,
            map->dest,
            this->ch,
            this->glow->glowColor,
            map->tileHeight, 
            map->tileWidth, 16, 16);
    }
    
};

void Entity::update(){
    if (this->ai){
        //this->ai->update(this);
    }
    
    if (!this->glow){
        // list of light sources of the tile = list of light sources of entity
        this->lightSources = game->map->tileMap[this->posX][this->posY].lightSources;
        this->illumination = game->map->tileMap[this->posX][this->posY].illumination;
        // go through light sources and add all contributions
        /*
        this->illumination = {0,0,0};
        std::list<Entity*>::iterator it;
        for (it=this->lightSources.begin(); it != this->lightSources.end(); it++){
            Glow* light = (*it)->glow;
            shineLight(light->glowColor.red, light->glowColor.green, light->glowColor.blue);
        }*/
    } else {
        // this->glow->clean(this) old light receivers
        this->glow->update(this);
    }
}

void Entity::shineLight(short red, short green, short blue){
    illumination.red = std::min(255, illumination.red+red);
    illumination.green = std::min(255, illumination.green+green);
    illumination.blue = std::min(255, illumination.blue+blue);
}

void Entity::destroy(){
    this->ch = this->chDestroyed;
    this->foreRgb = this->foreRgbDestroyed;
    if (this->creature){
        delete this->creature;
        this->creature = NULL; // death...;
        if (this->ai){
            delete this->ai;
            this->ai = NULL;
        }
    }
}