#include "animation.hpp"
#include "../draw/tile_manager.hpp"
#include <iostream>

Animation::Animation(){
    codepage = TileManager::LoadTexture("assets/10x10cp437.png");
    tileHeight = 10; // tileset resolution
    tileWidth = 10;
    currentFrame = 0;
}

void Animation::setFrames(const char* framesASCII){
    ch = framesASCII;
    frames = ch.length();
    std::cout << frames << std::endl;
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
    std::string passString = ch.substr(currentFrame, 1);
    const char* passCh = passString.c_str(); // extended ascii not supported
    TileManager::drawAscii(codepage, src, dest, passCh, foreRgb, tileWidth, tileHeight, 16, 16);
    if (frames > 0) this->nextFrame();
}