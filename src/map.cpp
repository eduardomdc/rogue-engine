#include "map.hpp"
#include "factories/tile_factory.hpp"
#include "game.hpp"
#include "procgen/levelgen.hpp"
#include <iostream>

Map::Map(int mapWidth, int mapHeight){
    std::cout << "Generating map..." << std::endl;
    // set variables
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    mapRenderWidth = 49; //49
    mapRenderHeight = 25;

    // set tileset used
    codepage = game->codepageBig;
}

void Map::loadMap(){
    
}

void Map::genMap(){
    makeDungeon(this);
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
    this->leftSide = this->mapPositionX-((this->mapRenderWidth)/2);
    this->rightSide = this->mapPositionX+((this->mapRenderWidth-1)/2) + 1;
    this->topSide = this->mapPositionY-((this->mapRenderHeight)/2);
    this->bottomSide = this->mapPositionY+((this->mapRenderHeight)/2) + 1;
}

void Map::update(){
    for (int i = 0; i<this->mapWidth; i++){
        for (int j = 0; j<this->mapHeight; j++){
            tileMap[i][j].illumination = ambientLight; // ambient light
        }
    }
}

bool Map::inMap(int x, int y){
    if (x >= 0 && x < this->mapWidth && y >= 0 && y < this->mapHeight){
        return true;
    }
    return false;
}
bool Map::inCamera(int x, int y){
    if (this->inMap(x, y)){
        if ( 
        (y >= this->topSide && y < this->bottomSide) && 
        (x >= this->leftSide && x < this->rightSide)
        ){
            return true;
        } return false; // out of render area
    } return false; // out of map
}


Entity* Map::getFighterAt(int x, int y){
    for (long unsigned int i = 0; i<this->entityList.size(); i++){
        Entity* ent = this->entityList[i];
        if (ent->posX == x && ent->posY == y){
            if (ent->fighter && ent->fighter->alive){
                return ent;
            }
        }
    }
    return nullptr;
}
    
