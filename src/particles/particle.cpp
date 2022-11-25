#include "particle.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <iostream>


Particle::Particle(){
    this->codepage = game->codepageSmall;
    this->startTime = SDL_GetTicks();
}

void Particle::render(){
    
    Map* map = game->map;
    int x = floor(this->posX);
    int y = floor(this->posY);
    if (map->inMap(x, y)){
        if ( 
            (y >= map->topSide && y < map->bottomSide) && 
            (x >= map->leftSide && x < map->rightSide)
            ){
            Tile tile = map->tileMap[x][y]; // get tile at entity location for background color matching
            this->illumination = tile.illumination;
        } else{
            this->done = true;
            return; // out of render area
        }
    } else{
        this->done = true;
        return; // out of map
    } 

    float screenPosX = this->posX - map->leftSide + map->mapOffsetX;
    float screenPosY = this->posY - map->topSide + map->mapOffsetY;
    dest.x = int(2*screenPosX) * tileWidth ;
    dest.y = int(2*screenPosY) * tileHeight ;

    color lightColored = this->foreRgb;

    lightColored.red *= this->illumination.red/255.0;
    lightColored.blue *= this->illumination.blue/255.0;
    lightColored.green *= this->illumination.green/255.0;

    game->tileManager->drawAscii(
        codepage,
        src,
        dest,
        this->ch,
        lightColored,
        tileHeight, 
        tileWidth, 16, 16);
}

void Particle::update(){
    posX += velocity[0];
    posY += velocity[1];
    if (SDL_GetTicks() - startTime > duration){
        done = true;
    }
}