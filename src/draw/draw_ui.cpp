#include "draw_ui.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "tile_manager.hpp"
#include "../game.hpp"


void renderText(std::string text, int x, int y, color color, bool centered){
    SDL_Texture* codepage = game->codepageSmall;
    SDL_Rect src;
    SDL_Rect dest;
    int start = 0;
    if (centered) start = text.length()/2;
    for (long unsigned int i = 0; i < text.length(); i++){
        std::string ch = text.substr(i,1);
        dest.x = (x-start)*10;
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

void renderTextAndBg(std::string text, int x, int y, color fgColor, color bgColor, bool centered){
    SDL_Texture* codepage = game->codepageSmall;
    SDL_Rect src;
    SDL_Rect dest;
    int start = 0;
    if (centered) start = text.length()/2;
    for (long unsigned int i = 0; i < text.length(); i++){
        std::string ch = text.substr(i,1);
        dest.x = (x-start)*10;
        dest.y = y*10;
        game->tileManager->drawAscii(
            codepage,
            src,
            dest,
            ch,
            fgColor,
            bgColor,
            10, 
            10,
            16, 
            16);
        x += 1;
    }
}


void drawWindow(int x, int y, int width, int height, color fgColor, color bgColor){
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
            fgColor,
            bgColor,
            10, 
            10,
            16, 
            16);
        }
    }

    drawBorder(x,y,width,height,fgColor,bgColor);
}

void drawWindowAndTitle(std::string title, int x, int y, int width, int height, color fgColor, color bgColor){
    SDL_Texture* codepage = game->codepageSmall;
    SDL_Rect src;
    SDL_Rect dest;
    // fill with black
    for (int i = x; i < width+x; i++){
        for (int j = y; j < height+y; j++){
            dest.x = i*10;
            dest.y = j*10;
            game->tileManager->drawAscii(
            codepage,
            src,
            dest,
            " ",
            fgColor,
            bgColor,
            10, 
            10,
            16, 
            16);
        }
    } 
    drawBorder(x,y,width,height,fgColor,bgColor);
    renderTextAndBg(title, x+width/2, y-1, bgColor, fgColor, true);
}

void drawBorder(int x, int y, int width, int height, color fgColor, color bgColor){
    SDL_Texture* codepage = game->codepageSmall;
    SDL_Rect src;
    SDL_Rect dest;
    // make left and right border
    for (int j = y; j < y + height; j++){
        dest.x = (x - 1)*10;
        dest.y = j*10;
        game->tileManager->drawAscii(codepage,src,dest,"║",fgColor,bgColor,10, 10,16, 16);
        dest.x = (x+width)*10;
        game->tileManager->drawAscii(codepage,src,dest,"║",fgColor,bgColor,10, 10,16, 16);
    }
    // make top and bottom border
    for (int i = x; i < x + width; i++){
        dest.x = i*10;
        dest.y = (y-1)*10;
        game->tileManager->drawAscii(codepage,src,dest,"═",fgColor,bgColor,10, 10,16, 16);
        dest.y = (y+height)*10;
        game->tileManager->drawAscii(codepage,src,dest,"═",fgColor,bgColor,10, 10,16, 16);
    }

    // make corners
    dest.x = (x-1)*10;
    dest.y = (y-1)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╔",fgColor,bgColor,10, 10,16, 16);
    dest.x = (x+width)*10;
    dest.y = (y-1)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╗",fgColor,bgColor,10, 10,16, 16);
    dest.x = (x-1)*10;
    dest.y = (y+height)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╚",fgColor,bgColor,10, 10,16, 16);
    dest.x = (x+width)*10;
    dest.y = (y+height)*10;
    game->tileManager->drawAscii(codepage,src,dest,"╝",fgColor,bgColor,10, 10,16, 16);
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

void drawQuantityBar(std::string label, int value, int maxValue, int x, int y, int width, color color){
    int fullBlocks = int((float(value)/maxValue)*width);
    for (int i=0; i<width; i++){
        game->tileManager->drawSmallAsciiUI(x+i, y, "█", colors::black);
    }
    for (int i=0; i<fullBlocks; i++){
        game->tileManager->drawSmallAsciiUI(x+i, y, "█", color);
    }
    float boundaryValue = value - fullBlocks*float(maxValue)/width;
    float actualValue = float(maxValue)/width;
    if (boundaryValue > 0.66*actualValue){
        game->tileManager->drawSmallAsciiUI(x+fullBlocks, y, "▓", color, colors::black);
    } else if ( boundaryValue > 0.33*actualValue){
        game->tileManager->drawSmallAsciiUI(x+fullBlocks, y, "▒", color, colors::black);
    } else if (boundaryValue > 0){
        game->tileManager->drawSmallAsciiUI(x+fullBlocks, y, "░", color, colors::black);
    }
    renderText(label, x, y, colors::white, false);
    std::string quantityLabel = std::to_string(value);
    quantityLabel.append("/");
    quantityLabel.append(std::to_string(maxValue));
    renderText(quantityLabel, x+width-quantityLabel.length(), y, colors::white, false);
}
