#include "text.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include "tile_manager.hpp"
#include "../game.hpp"


void renderText(std::string text, int x, int y, color color, bool centered){
    SDL_Texture* codepage = game->codepageSmall;
    SDL_Rect src;
    SDL_Rect dest;
    for (long unsigned int i = 0; i < text.length(); i++){
        std::string ch = text.substr(i,1);
        dest.x = x*10;
        dest.y = y*10;
        TileManager::drawAscii(
            codepage,
            src,
            dest,
            ch,
            color,
            10, 
            10,
            16, 
            16);
        x += 1;
    }
}