#include "draw_ui.hpp"
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
        game->tileManager->drawAscii(
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

void drawWindow(int x, int y, int width, int height){
    SDL_Texture* codepage = game->codepageSmall;
    SDL_Rect src;
    SDL_Rect dest;
    for (int i = x; i < width+x; i++){
        for (int j = y; j < height+y; j++){
            dest.x = i*10;
            dest.y = j*10;
            game->tileManager->drawAscii(
            codepage,
            src,
            dest,
            " ",
            colors::white,
            colors::black,
            10, 
            10,
            16, 
            16);
        }
    }

    // make left and right border
    for (int j = y; j < y + height; j++){
        dest.x = (x - 1)*10;
        dest.y = j*10;
        game->tileManager->drawAscii(codepage,src,dest,"║",colors::white,colors::black,10, 10,16, 16);
        dest.x = (x+width)*10;
        game->tileManager->drawAscii(codepage,src,dest,"║",colors::white,colors::black,10, 10,16, 16);
    }
    // make top and bottom border
    for (int i = x; i < x + width; i++){
        dest.x = i*10;
        dest.y = (y-1)*10;
        game->tileManager->drawAscii(codepage,src,dest,"═",colors::white,colors::black,10, 10,16, 16);
        dest.y = (y+height)*10;
        game->tileManager->drawAscii(codepage,src,dest,"═",colors::white,colors::black,10, 10,16, 16);
    }

    // make corners
    dest.x = (x-1)*10;
    dest.y = (y-1)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╔",colors::white,colors::black,10, 10,16, 16);
    dest.x = (x+width)*10;
    dest.y = (y-1)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╗",colors::white,colors::black,10, 10,16, 16);
    dest.x = (x-1)*10;
    dest.y = (y+height)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╚",colors::white,colors::black,10, 10,16, 16);
    dest.x = (x+width)*10;
    dest.y = (y+height)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╝",colors::white,colors::black,10, 10,16, 16);
}

void drawTileSelect(int x, int y){
    // semi-transparent squares over selected tiles
    SDL_Texture* codepage = game->codepageBig;
    SDL_Rect src;
    SDL_Rect dest;
    dest.x = 20*x;
    dest.y = 20*y;
    game->tileManager->DrawTransparentTile(codepage, src, dest, 219, colors::blue, 20, 20, 16, 16, 70*(1+rand()%2));
}