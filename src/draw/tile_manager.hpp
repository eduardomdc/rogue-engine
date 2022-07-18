#ifndef TILE_MANAGER_HPP
#define TILE_MANAGER_HPP

#pragma once
#include <string>
#include "../game.hpp"
#include "../colors.hpp"

class TileManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
    static void DrawTile(SDL_Texture* tileset, SDL_Rect src, SDL_Rect dest, int id, color rgb, int tileHeight, int tileWidth, int setHeight, int setWidth);
    static void drawAscii(SDL_Texture* tileset, SDL_Rect src, SDL_Rect dest, std::string id, color foreRgb, color backRgb, int tileHeight, int tileWidth, int setHeight, int setWidth);
    static void drawAscii(SDL_Texture* tileset, SDL_Rect src, SDL_Rect dest, std::string id, color foreRgb, int tileHeight, int tileWidth, int setHeight, int setWidth);
};

#endif