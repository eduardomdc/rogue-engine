#ifndef TILE_MANAGER_HPP
#define TILE_MANAGER_HPP

#pragma once
#include <string>
#include "../game.hpp"
#include "../colors.hpp"

class TileManager {
public:
    SDL_Texture* LoadTexture(const char* fileName);
    void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
    void DrawTile(SDL_Texture* tileset, SDL_Rect src, SDL_Rect dest, int id, color rgb, int tileHeight, int tileWidth, int setHeight, int setWidth);
    void DrawTransparentTile(SDL_Texture* tileset, SDL_Rect src, SDL_Rect dest, int id, color rgb, int tileHeight, int tileWidth, int setHeight, int setWidth, int alpha);
    void drawAscii(SDL_Texture* tileset, SDL_Rect src, SDL_Rect dest, std::string id, color foreRgb, color backRgb, int tileHeight, int tileWidth, int setHeight, int setWidth);
    void drawAscii(SDL_Texture* tileset, SDL_Rect src, SDL_Rect dest, std::string id, color foreRgb, int tileHeight, int tileWidth, int setHeight, int setWidth);
    void drawSmallAsciiUI(int x, int y, std::string id, color foreRgb);
    void update();
    int blinkAlpha = 100;
};

#endif