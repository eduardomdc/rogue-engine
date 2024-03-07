#ifndef MAP_HPP
#define MAP_HPP

#include "entities/entity.hpp"
#include "particles/effect.hpp"
#include <SDL_rect.h>
#pragma once
#include <vector>
#include "draw/tile_manager.hpp"
#include "factories/tile_factory.hpp"
#include "entities/tile.hpp"
#include "algorithms/perlin.hpp"
#include <map>
//#include "entities/object.hpp"
//#include "entities/entity.hpp"

class EntityList {
public:
    EntityList();
    std::vector< Entity* > bottom; // holds bodies and other things to step on
    std::vector< Entity* > mid; // holds items and things you can interact with
    std::vector< Entity* > top; // holds you and things that can kill you
    void push_back(Entity*);
    std::vector< Entity* > entitiesAt(int x, int y); // returns entities at location
};

class EntityMap {
public:
    EntityMap();
    std::multimap<SDL_Point, Entity*> map;
};

class Map{
public:
    Map(int mapWidth, int mapHeight);
    ~Map();

    //std::vector< Entity* > entityList; // array of entities on the map;
    EntityList entityList;
    //list of active effects
    std::vector<Effect*> effects;

    int mapWidth; // map size
    int mapHeight;

    int mapRenderWidth = 25;//50; // 96x54 width of map window rendering (odd)
    int mapRenderHeight = 25;//29;

    int mapOffsetX = 0; // where on the screen the map will be rendered
    int mapOffsetY = 0;

    int mapPositionX = 10; // what map position is being rendered (centered)
    int mapPositionY = 10;

    int leftSide = this->mapPositionX-((this->mapRenderWidth-1)/2);
    int rightSide = this->mapPositionX+((this->mapRenderWidth-1)/2);
    int topSide = this->mapPositionY-((this->mapRenderHeight-1)/2);
    int bottomSide = this->mapPositionY+((this->mapRenderHeight-1)/2);

    lightColor ambientLight = {0,0,0};

    void loadMap();
    void genMap();
    void drawMap();
    void update();

    bool inMap(int x, int y);
    bool inCamera(int x, int y);
    Entity* getFighterAt(int x, int y);

    SDL_Rect src, dest;
    SDL_Texture* codepage;
    std::vector< std::vector< Tile* > > tileMap;// array of tiles on map
    std::vector<std::vector<bool>> fog;// revealed areas of the map, fog of war

    Tile* tile = new Tile((const char*)"0", colors::white, colors::black, true, true); //temp variable tile for operations

    int tileHeight = 20; //tile resolution (pixels)
    int tileWidth = 20;

    void moveCamera(int x, int y);
private:
};

#endif
