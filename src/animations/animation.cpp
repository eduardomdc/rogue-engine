#include "animation.hpp"
#include "../draw/tile_manager.hpp"
#include "../map.hpp"
#include "../game.hpp"
#include <iostream>

Animation::Animation(){
    codepage = game->codepageSmall;
    tileHeight = 10; // tileset resolution
    tileWidth = 10;
    currentFrame = 0;
    frameStart = SDL_GetTicks();
}

void Animation::setFrames(std::vector<std::string> framesASCII){
    chFrames = framesASCII;
    frames = framesASCII.size();
}

void Animation::nextFrame(){
    if (currentFrame >= frames - 1){
        currentFrame = 0;
    } else {
        currentFrame += 1;
    }
}

void Animation::render(){
    
    currentFrame = ((SDL_GetTicks()-frameStart)/speed)%frames;
    std::string passCh = chFrames[currentFrame];

    if (onMap){
        Map* map = game->map;
        if (map->inMap(this->posX, this->posY)){
            if ( 
                (this->posY >= map->topSide && this->posY < map->bottomSide) && 
                (this->posX >= map->leftSide && this->posX < map->rightSide)
                ){
                if (game->player->player->canSee(this->posX, this->posY)){
                    Tile tile = map->tileMap[this->posX][this->posY]; // get tile at entity location for background color matching
                    this->illumination = tile.illumination;
                }
                else return; // animation out of player view
            } else return; // out of render area
        } else return; // out of map

        int screenPosX = this->posX - map->leftSide + map->mapOffsetX;
        int screenPosY = this->posY - map->topSide + map->mapOffsetY;
        dest.x = 2 * screenPosX * tileWidth + tileWidth * subPosX;
        dest.y = 2 * screenPosY * tileHeight + tileHeight * subPosY;

        color lightColored = this->foreRgb;

        lightColored.red *= this->illumination.red/255.0;
        lightColored.blue *= this->illumination.blue/255.0;
        lightColored.green *= this->illumination.green/255.0;

        game->tileManager->drawAscii(
            codepage,
            src,
            dest,
            passCh,
            lightColored,
            tileHeight, 
            tileWidth, 16, 16);
    }
    else{
        dest.x = posX * tileWidth;
        dest.y = posY * tileHeight;
        game->tileManager->drawAscii(codepage, src, dest, passCh, foreRgb, tileWidth, tileHeight, 16, 16);
    }
    if (currentFrame == frames - 1) {
        done = true;
    }
    
}   