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
    int frames; // amount of frames
    int speed; // amount of ms between each frame
    SDL_Texture* codepage;
    int tileWidth; // resolution of tiles used
    int tileHeight;
    color foreRgb;
    color backRgb;

    bool done = false; // is the animation finished? 

    Animation();

    void setFrames(std::vector<std::string> framesASCII);

    void nextFrame();
    void render();

private:
    std::vector<std::string> chFrames;
};

#endif