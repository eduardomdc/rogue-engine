#include "animation.hpp"
#include "../draw/tile_manager.hpp"
#include <iostream>

Animation::Animation(){
    codepage = TileManager::LoadTexture("assets/10x10cp437.png");
    tileHeight = 10; // tileset resolution
    tileWidth = 10;
    currentFrame = 0;
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
    dest.x = posX * tileWidth;
    dest.y = posY * tileHeight;
    std::string passCh = chFrames[currentFrame];
    TileManager::drawAscii(codepage, src, dest, passCh, foreRgb, tileWidth, tileHeight, 16, 16);
    if (frames > 0) this->nextFrame();
}