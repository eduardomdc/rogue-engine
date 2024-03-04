#include "map.hpp"
#include "entities/entity.hpp"
#include "factories/tile_factory.hpp"
#include "game.hpp"
#include "procgen/levelgen.hpp"
#include <iostream>
#include <vector>

EntityList::EntityList(){

}

void EntityList::push_back(Entity* ent){
    if (ent->fighter){
        this->top.push_back(ent);
    } else if (ent->item or ent->inventory.size()>0){
        this->mid.push_back(ent);
    }
    else {
        this->bottom.push_back(ent);
    }
}

std::vector<Entity*> EntityList::entitiesAt(int x, int y){
    std::vector<Entity*> ents;
    for(int i=0; i<this->bottom.size(); i++){
        if (bottom[i]->posX == x && bottom[i]->posY == y){
            ents.push_back(bottom[i]);
        }
    }
    for(int i=0; i<this->mid.size(); i++){
        if (mid[i]->posX == x && mid[i]->posY == y){
            ents.push_back(mid[i]);
        }
    }
    for(int i=0; i<this->top.size(); i++){
        if (top[i]->posX == x && top[i]->posY == y){
            ents.push_back(top[i]);
        }
    }
    return ents;
}

Map::Map(int mapWidth, int mapHeight){
    std::cout << "Generating map..." << std::endl;
    // set variables
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    mapRenderWidth = (game->screenW)/20; //49
    mapRenderHeight = game->screenH/20;

    // set tileset used
    codepage = game->codepageBig;
    effects = {};
}

void Map::loadMap(){
    
}

void Map::genMap(){
    //makeTestChamber(this);
    makeSewers(this);
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
                tileMap[i][j]->render();
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
    this->rightSide = this->mapPositionX+((this->mapRenderWidth +1)/2);
    this->topSide = this->mapPositionY-((this->mapRenderHeight)/2);
    this->bottomSide = this->mapPositionY+((this->mapRenderHeight+1)/2);
}

void Map::update(){
    for (int i = 0; i<this->mapWidth; i++){
        for (int j = 0; j<this->mapHeight; j++){
            tileMap[i][j]->illumination = ambientLight; // ambient light
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
    for (long unsigned int i = 0; i<this->entityList.top.size(); i++){
        Entity* ent = this->entityList.top[i];
        if (ent->posX == x && ent->posY == y){
            if (ent->fighter && ent->fighter->alive){
                return ent;
            }
        }
    }
    return nullptr;
}
    
