#include "levelgen.hpp"
#include "../algorithms/perlin.hpp"
#include "../factories/monster_factory.hpp"
#include "../factories/item_factory.hpp"
#include "../entities/glow.hpp"
#include "../entities/entity.hpp"
#include <iostream>

struct rect {
    int w;
    int h;
} typedef rect;

void fillMap(Map* map, int floorTile){
    for (int i = 0; i<map->mapWidth; i++){
        map->tileMap.push_back( std:: vector< Tile* >() );
        for (int j = 0; j<map->mapHeight; j++){
            map->tile = tileFactory::makeTile(floorTile, i, j);
            map->tileMap[i].push_back(map->tile);
        }
    }
}

void makeTestChamber(Map *map){
    map->ambientLight = {20,20,50};
    fillMap(map, CAVE_MOSSY_FLOOR);
    map->entityList.push_back(makeRat(20,20));
    map->entityList.push_back(makeRat(21, 21));
    map->entityList.push_back(makeRat(19, 21));
    map->entityList.push_back(makeRat(21, 20));
    map->entityList.push_back(makeRat(20, 21));
    Entity* sword = makeLongsword(11, 8);
    map->entityList.push_back(sword);
    for (int i=0; i<40; i++){
        Entity* potion = makeHealingPotion(12, 9);
        map->entityList.push_back(potion);
    }
    Entity* chest = makeChest(15, 15);
    chest->inventory.push_back(makeLongsword(0, 0));
    map->entityList.push_back(chest);
}

void makeForest(Map *map){
    map->ambientLight = {0, 0, 158};

    Perlin* tallGrass = new Perlin(250);
    Perlin* rocks = new Perlin(250);
    fillMap(map, GRASS);
    for (int i = 0; i<map->mapWidth; i++){
        for (int j = 0; j<map->mapHeight; j++){
            if (rocks->value(i*0.1, j*0.1) > 0.5){
                map->tileMap[i][j] = tileFactory::makeTile(CAVE_WALL, i, j);
            }
            else if (tallGrass->value(i*0.1, j*0.1) > 0.2){
                map->tileMap[i][j] = tileFactory::makeTile(TALL_GRASS, i, j);
            }
        }
    }
}

void makeSnowyMountain(Map* map){
    //generate perlin map
    map->ambientLight = {50,50,150};

    Perlin* wallPerlin = new Perlin(250);
    Perlin* mossPerlin = new Perlin(250);
    std::cout << "Perlin noise generated" << std::endl;

    // add floor tiles
    fillMap(map, CAVE_FLOOR);

    // add rock walls and vegetation
    for (int i = 0; i<map->mapWidth; i++){
        for (int j = 0; j<map->mapHeight; j++){
            if (wallPerlin->value(i*0.1,j*0.1) > 0.2){
                map->tileMap[i][j] = tileFactory::makeTile(CAVE_WALL, i, j);
            }
            else if (mossPerlin->value(i*0.1,j*0.1) > 0.1){
                map->tileMap[i][j] = tileFactory::makeTile(CAVE_MOSSY_FLOOR, i, j);
            }
        }
    }
    //add wolves
    for (int i = 0; i<map->mapWidth; i++){
        for (int j = 0; j<map->mapHeight; j++){
            if (rand()%100==0){
                if (map->tileMap[i][j]->walkable){
                    Entity* monster = makeGoblin(i,j);
                    map->entityList.push_back(monster);
                }
            }
        }
    }
}

void makeRoom(Map* map, int floorTile, int posx, int posy, int width, int height){
    // make floor
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            if (map->inMap(i+posx, j+posy)){
                map->tileMap[i+posx][j+posy] = tileFactory::makeTile(floorTile, i+posx, j+posy);
            }
        }
    }
}

void makeCorridor(Map* map, int floorTile, int posx, int posy, int endx, int endy){
    int dx = endx - posx;
    int dy = endy - posy;
    if (dx >= 0) makeRoom(map, floorTile, posx, posy, dx, 1);
    else makeRoom(map, floorTile, endx, posy, -dx, 1);
    if (dy >= 0) makeRoom(map, floorTile, endx, posy, 1, dy);
    else makeRoom(map, floorTile, endx, endy, 1, -dy);
}


bool squareInMap(int x, int y, int width, int height){
    if (  game->map->inMap(x+width/2, y+height/2)
        &&game->map->inMap(x+width/2, y-height/2)
        &&game->map->inMap(x-width/2, y-height/2)
        &&game->map->inMap(x-width/2, y+height/2)
        )
        return true;
    else
        return false;
}
void makeDungeon(Map* map){
    map->ambientLight = {0,0,80};

    fillMap(map, CAVE_WALL);
    int nRooms = 1;//rand()%5+5; // number of rooms
    int i = 0;
    int lastx, lasty; // last room position
    while (i < nRooms){
        int x = rand()%map->mapWidth;
        int y = rand()%map->mapHeight;
        int width = rand()%10+3;
        int height = rand()%10+3;
        if (i == 0){
            x = 9;
            y = 9;
        }
        if (squareInMap(x, y, width+1, height+1)){
            makeRoom(map, CAVE_FLOOR, x, y, width, height); 
            Entity* fireplace = makeFireplace(x+width/2, y+height/2);
            map->entityList.push_back(fireplace);
            Entity* sword = makeLongsword(x+width/3, y+height/3);
            map->entityList.push_back(sword);
            Entity* rat = makeGoblin(x+width/2, y+height/2);
            map->entityList.push_back(rat);
            if (i!=0) makeCorridor(map, CAVE_FLOOR, x, y, lastx, lasty);
            lastx = x+width/2;
            lasty = y+height/2;
            i++;
        }
    }
}

void houseRoom(Map* map, rect pos, rect size, rect door){
    for (int i=pos.w; i<size.w+pos.w; i++){
        for (int j=pos.h; j<size.h+pos.h; j++){
            map->tileMap[i][j] = tileFactory::makeTile(STONE_FLOOR, i, j);
        }
    }
    //make walls
    for (int i=pos.w-1; i<size.w+pos.w+1; i++){
        map->tileMap[i][pos.h-1] = tileFactory::makeTile(STONE_WALL, i, pos.h-1);
        map->tileMap[i][pos.h+size.h] = tileFactory::makeTile(STONE_WALL, i, pos.h+size.h);
    }
    for (int i=pos.h; i<size.h+pos.h; i++){
        map->tileMap[pos.w-1][i] = tileFactory::makeTile(STONE_WALL, pos.w-1, i);
        map->tileMap[pos.w+size.w][i] = tileFactory::makeTile(STONE_WALL, pos.w+size.w, i);
    }
    // hole in wall for door
    map->tileMap[door.w][door.h] = makeWoodenDoor(door.w, door.h);
    Entity* fireplace = makeFireplace(pos.w+size.w/2, pos.h+size.h/2);
    map->entityList.push_back(fireplace);
}

void makeBigHouse(Map* map){
    map->ambientLight = {0,0,80};
    fillMap(map, GRASS);
    houseRoom(map, {5,10}, {20,10}, {12, 20});
}
