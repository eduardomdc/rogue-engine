#include "map.hpp"

Map::Map(int mapWidth, int mapHeight){
    // set variables
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;

    // set tileset used
    codepage = TileManager::LoadTexture("assets/cp437.png");

    // add floor tiles
    for (int i = 0; i<this->mapHeight; i++){
        tileMap.push_back( std:: vector< Tile >() );
        for (int j = 0; j<this->mapWidth; j++){
            Tile* floorInstance = new Tile((const char*)"#", colors::white, colors::black, true, true); // how to use tile from tile_factory?
            tileMap[i].push_back(*floorInstance);
        }
    }
}

void Map::loadMap(){
    
}

void Map::drawMap(){
    int leftSide = this->mapPositionX-((this->mapRenderWidth-1)/2);
    int rightSide = this->mapPositionX+((this->mapRenderWidth-1)/2);
    int topSide = this->mapPositionY-((this->mapRenderHeight-1)/2);
    int bottomSide = this->mapPositionY+((this->mapRenderHeight-1)/2);
    
    Tile* tile = new Tile((const char*)"0", colors::white, colors::blue, true, true);
    bool out_of_map;
    for (int row = leftSide; row < rightSide; row++){
        for (int col = topSide; col < bottomSide; col++){
            out_of_map = false;
            if ((col>=0 && col<this->mapHeight) && (row>=0 && row<this->mapWidth)){
                *tile = this->tileMap[row][col];
            } else { // out of the map
                out_of_map = true;
            }
            if (!out_of_map){ // if tile is inside map then print it
                int tileHeight = 10; //tile resolution
                int tileWidth = 10;
                

                // calculate on-screen position of tiles
                int screenPosX = row-leftSide+this->mapOffsetX;
                int screenPosY = col-topSide+this->mapOffsetY;
                dest.x = screenPosX * tileWidth;
                dest.y = screenPosY * tileHeight;
                
                TileManager::drawAscii(codepage, src, dest, tile->ch, tile->foreRgb, tile->backRgb, tileHeight, tileWidth, 16, 16);
            }
        }
    }
}