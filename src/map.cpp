#include "map.hpp"
#include "entities/tile_factory.hpp"
#include "game.hpp"
#include "procgen/levelgen.hpp"
#include <iostream>

Map::Map(int mapWidth, int mapHeight){
    std::cout << "Generating map..." << std::endl;
    // set variables
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;

    // set tileset used
    codepage = game->codepageBig;
    makeSnowyMountain(this);
}

void Map::loadMap(){
    
}

void Map::drawMap(){
    // draw tiles
    try{
        // THIS IS SUPER SLOW? WHY
    // for (std::vector<Tile> tileRow : tileMap){
    //     for (Tile tile : tileRow){
    //         tile.render();
    //     }
    // }
        // FASTER
        for (int i = 0; i < mapWidth; i++){
            for (int j = 0; j < mapHeight; j++){
                tileMap[i][j].render();
            }
        }
    }
    catch(...){
        std::cout<<"drawMap error"<<std::endl;
    }
}

void Map::moveCamera(int x, int y){
    this->mapPositionX = x;
    this->mapPositionY = y;
    this->leftSide = this->mapPositionX-((this->mapRenderWidth-1)/2);
    this->rightSide = this->mapPositionX+((this->mapRenderWidth-1)/2);
    this->topSide = this->mapPositionY-((this->mapRenderHeight-1)/2);
    this->bottomSide = this->mapPositionY+((this->mapRenderHeight-1)/2);
}

void Map::update(){
    for (int i = 0; i<this->mapWidth; i++){
        for (int j = 0; j<this->mapHeight; j++){
            tileMap[i][j].illumination = {5,5,55}; // ambient light
        }
    }
}

bool Map::inMap(int x, int y){
    if (x >= 0 && x < this->mapWidth && y >= 0 && y < this->mapHeight){
        return true;
    }
    return false;
}