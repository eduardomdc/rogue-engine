#include "animation.hpp"
#include "../draw/tile_manager.hpp"
#include "../draw/draw_ui.hpp"
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
    if (!damageNumber){
        currentFrame = ((SDL_GetTicks()-frameStart)/speed)%frames;
        std::string passCh = chFrames[currentFrame];
        if (onMap){
        Map* map = game->map;

        if (map->inCamera(this->posX, this->posY)){
            if (game->player->player->canSee(this->posX, this->posY)){
                Tile tile = map->tileMap[this->posX][this->posY]; // get tile at entity location for background color matching
                this->illumination = tile.illumination;
            }
            else {
                return;
            }//animation out of player view
        } else {
            return; 
        }// animation not in camera view

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
            game->tileManager->drawAscii(codepage, src, dest, passCh, foreRgb, backRgb, tileWidth, tileHeight, 16, 16);
        }
        if (currentFrame == frames - 1) {
            done = true;
        }
    } else if (damageNumber){
        Map* map = game->map;
        if (map->inCamera(this->posX, this->posY)){
            if (game->player->player->canSee(this->posX, this->posY)){
            }
            else return; //animation out of player view
        } else return; // animation not in camera view
        std::string text = chFrames[0];
        int screenPosX = (this->posX - map->leftSide + map->mapOffsetX)*2+subPosX;
        int screenPosY = (this->posY - map->topSide + map->mapOffsetY)*2+subPosY;
        renderText(text, screenPosX, screenPosY, this->foreRgb, false);
        if ((SDL_GetTicks()-frameStart) > Uint32(speed)){
            frameStart = SDL_GetTicks();
            subPosY--;
            damageNumberMove++;
            if (damageNumberMove > 4){
                done = true;
            }
        }
    }
}

void bipedalStepAnimation(int posX, int posY, int targetX, int targetY, bool rightStep){
    Animation* step = new Animation();
    step->foreRgb = colors::grey;
    step->setFrames({"#","*","."," "});
    step->posX = posX;
    step->speed = 100;
    step->posY = posY;
    if (targetY > posY){
        step->subPosY = 1;
        if (rightStep){
            step->subPosX = 0;
        } else step->subPosX = 1;
    } else if (targetY < posY) {
        step->subPosY = 0;
        if (rightStep){
            step->subPosX = 0;
        } else step->subPosX = 1;
    }
    if (targetX > posX){
        step->subPosX = 1;
        if (rightStep){
            step->subPosY = 0;
        } else step->subPosY = 1;
    } else if (targetX < posX) {
        step->subPosX = 0;
        if (rightStep){
            step->subPosY = 0;
        } else step->subPosY = 1;
    }

    step->onMap = true;
    game->animationList.push_back(step);
}
