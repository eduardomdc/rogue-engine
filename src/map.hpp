#ifndef MAP_HPP
#define MAP_HPP

#pragma once
#include <vector>
#include "game.hpp"
#include "draw/tile_manager.hpp"
#include "entities/tile.hpp"


class Map{
public:
    Map(int mapWidth, int mapHeight);
    ~Map();

    int mapWidth = 20; // map size
    int mapHeight = 20;

    int mapRenderWidth = 31; // width of map window rendering (odd)
    int mapRenderHeight = 31;

    int mapOffsetX = 4; // where on the screen the map will be rendered
    int mapOffsetY = 4;

    int mapPositionX = 10; // what map position is being rendered (centered)
    int mapPositionY = 10;

    void loadMap();
    void drawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture* codepage;
    std::vector< std::vector< Tile > > tileMap;// array of tiles on map
};

#endif