#include "map.hpp"
#include "entities/tile_factory.hpp"
#include "game.hpp"

Map::Map(int mapWidth, int mapHeight){
    // set variables
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;

    // set tileset used
    codepage = TileManager::LoadTexture("assets/20x20cp437.png");

    //generate perlin map
    Perlin* perlin = new Perlin();

    // add floor tiles
    for (int i = 0; i<this->mapHeight; i++){
        tileMap.push_back( std:: vector< Tile >() );
        for (int j = 0; j<this->mapWidth; j++){
            tile = tileFactory::makeTile(CAVE_FLOOR, i, j);
            tileMap[i].push_back(*tile);
        }
    }

    // add some walls for testing
    for (int i = 0; i<this->mapHeight; i++){
        for (int j = 0; j<this->mapWidth; j++){
            
            if (rand()%30 == 0){
                
            }
            if (perlin->value(i*0.1,j*0.1) > 0.2){
                tileMap[i][j] = *tileFactory::makeTile(CAVE_WALL, i, j);
            }
            else if (perlin->value(i*0.1,j*0.1) > 0.1){
                tileMap[i][j] = *tileFactory::makeTile(CAVE_MOSSY_FLOOR, i, j);
            }
        }
    }
}

void Map::loadMap(){
    
}

void Map::drawMap(){
    // draw tiles
    for (std::vector<Tile> tileRow : tileMap){
        for (Tile tile : tileRow){
            tile.render();
        }
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
    for (int i = 0; i<this->mapHeight; i++){
        for (int j = 0; j<this->mapWidth; j++){
            tileMap[i][j].illumination = {0,0,0};
        }
    }
}