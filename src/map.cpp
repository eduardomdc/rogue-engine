#include "map.hpp"
#include "entities/tile_factory.hpp"


Map::Map(int mapWidth, int mapHeight){
    // set variables
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;

    // set tileset used
    codepage = TileManager::LoadTexture("assets/20x20cp437.png");

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
            if (rand()%10 == 0){
                tileMap[i][j] = *tileFactory::makeTile(CAVE_WALL, i, j);
            }
        }
    }

    // illumination test
    int x = 5;
    int y = 12;
    int radius = 4;
    short brightValue = 0;
    for (int i = -radius; i<=radius; i++){
        for (int j = -radius; j<=radius; j++){
            brightValue = 255/((abs(i*i+j*j)/7)+1);
            tileMap[x+i][y+j].illumination = {brightValue,(short)(brightValue/1.2),(short)(brightValue/2)};
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