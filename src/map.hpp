#ifndef MAP_HPP
#define MAP_HPP

#pragma once
#include <vector>
#include "draw/tile_manager.hpp"
#include "entities/tile_factory.hpp"
#include "entities/tile.hpp"
//#include "entities/object.hpp"
//#include "entities/entity.hpp"

class Map{
public:
    Map(int mapWidth, int mapHeight);
    ~Map();

    std::vector< Entity > entityList; // array of entities on the map;

    int mapWidth = 50; // map size
    int mapHeight = 50;

    int mapRenderWidth = 40; // width of map window rendering (odd)
    int mapRenderHeight = 40;

    int mapOffsetX = 2; // where on the screen the map will be rendered
    int mapOffsetY = 2;

    int mapPositionX = 10; // what map position is being rendered (centered)
    int mapPositionY = 10;

    int leftSide = this->mapPositionX-((this->mapRenderWidth-1)/2);
    int rightSide = this->mapPositionX+((this->mapRenderWidth-1)/2);
    int topSide = this->mapPositionY-((this->mapRenderHeight-1)/2);
    int bottomSide = this->mapPositionY+((this->mapRenderHeight-1)/2);

    void loadMap();
    void drawMap();

    SDL_Rect src, dest;
    SDL_Texture* codepage;
    std::vector< std::vector< Tile > > tileMap;// array of tiles on map

    Tile* tile = new Tile((const char*)"0", colors::white, colors::black, true, true); //temp variable tile for operations

    int tileHeight = 20; //tile resolution (pixels)
    int tileWidth = 20;

    void moveCamera(int x, int y);
private:
};

#endif