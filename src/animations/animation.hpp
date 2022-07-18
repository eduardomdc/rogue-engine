#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "../colors.hpp"

class Animation{
public:
    int posX;
    int posY;
    SDL_Rect src;
    SDL_Rect dest;
    
    int currentFrame;
    int frames;
    SDL_Texture* codepage;
    int tileWidth;
    int tileHeight;
    color foreRgb;
    color backRgb;

    Animation();

    void setFrames(std::vector<std::string> framesASCII);

    void nextFrame();
    void render();

private:
    std::vector<std::string> chFrames;
};

#endif