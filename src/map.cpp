#include "map.hpp"

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
            tile = tileFactory::caveFloor();
            tileMap[i].push_back(*tile);
        }
    }

    // add some walls for testing
    for (int i = 0; i<this->mapHeight; i++){
        for (int j = 0; j<this->mapWidth; j++){
            if (rand()%10 == 0){
                tileMap[i][j] = *tileFactory::caveWall();
            }
        }
    }
}

void Map::loadMap(){
    
}

void Map::drawMap(){
    // draw tiles
    bool outOfMap;
    for (int row = leftSide; row < rightSide; row++){
        for (int col = topSide; col < bottomSide; col++){
            outOfMap = false;
            if ((col>=0 && col<this->mapHeight) && (row>=0 && row<this->mapWidth)){
                *tile = this->tileMap[row][col];
            } else { // out of the map
                outOfMap = true;
            }
            if (!outOfMap){ // if tile is inside map then print it
                

                // calculate on-screen position of tiles
                int screenPosX = row-leftSide+this->mapOffsetX;
                int screenPosY = col-topSide+this->mapOffsetY;
                dest.x = screenPosX * tileWidth;
                dest.y = screenPosY * tileHeight;
                
                TileManager::drawAscii(codepage, src, dest, tile->ch, tile->foreRgb, tile->backRgb, this->tileHeight, this->tileWidth, 16, 16);
            }
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