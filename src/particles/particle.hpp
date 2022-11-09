#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SDL2/SDL.h>
#include "../colors.hpp"
#include <string>
#include <vector>

class Particle {
public:
    Particle();
    void update();
    void render();
    float posX, posY;
    std::vector<float> velocity;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture* codepage;
    Uint32 startTime;
    std::string ch;
    color foreRgb;
    lightColor illumination = {0,0,0};
    Uint32 duration; // in ms
    bool done = false;
    int tileWidth = 10; // resolution of tiles used
    int tileHeight = 10;
};

#endif