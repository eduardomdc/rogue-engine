#include "levelgen.hpp"
#include "../algorithms/perlin.hpp"
#include "../factories/monster_factory.hpp"
#include "../factories/item_factory.hpp"
#include "../entities/glow.hpp"
#include "../entities/entity.hpp"
#include <iostream>
#include <vector>

bool inside(Room room, rect pos){
    if (pos.w < room.pos.w)
        return false;
    
    return true;
}

std::vector<Room> Generator::isInRooms(rect pos){
    std::vector<Room> inRooms = {};
    for (int i=0; i<rooms.size(); i++){
        if (inside(rooms[i], pos)){
            
        }
    }
    return inRooms;
}

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

void spawnMonsters(int level, Map* map, rect pos){
    if (level == 1){
        int choice = rand()%3;
        switch (choice){
            case 1:
                makeHorde(map, *makeRat, pos, rand()%4+1);
                break;
            case 2:
                makeHorde(map, *makeZombie, pos, rand()%2+1);
                break;
        }
    }
}

void makeRoom(Map* map, int floorTile, Room room){
    // make floor
    for (int i = 0; i < room.size.w; i++){
        for (int j = 0; j < room.size.h; j++){
            if (map->inMap(i+room.pos.w, j+room.pos.h)){
                map->tileMap[i+room.pos.w][j+room.pos.h] = tileFactory::makeTile(floorTile, i+room.pos.w, j+room.pos.h);
            }
        }
    }
}

void makeCorridor(Map* map, int floorTile, Room start, Room end){
    rect startc = roomCenter(start);
    rect endc = roomCenter(end);
    int dx = endc.w - startc.w;
    int dy = endc.h - startc.h;
    if (dx >= 0) makeRoom(map, floorTile, {{startc.w, startc.h}, {dx+1, 1}});
    else makeRoom(map, floorTile, {{endc.w, startc.h},{-dx, 1}});
    if (dy >= 0) makeRoom(map, floorTile, {{endc.w, startc.h}, {1, dy+1}});
    else makeRoom(map, floorTile, {{endc.w, endc.h},{1, -dy}});
}

void makeCorridorwithDoors(Map* map, int floorTile, Room start, Room end){
    rect startc = roomCenter(start);
    rect endc = roomCenter(end);
    int dx = endc.w - startc.w;
    int dy = endc.h - startc.h;
    if (dx >= 0) makeRoom(map, floorTile, {{startc.w, startc.h}, {dx+1, 1}});
    else makeRoom(map, floorTile, {{endc.w, startc.h},{-dx, 1}});
    if (dy >= 0) makeRoom(map, floorTile, {{endc.w, startc.h}, {1, dy+1}});
    else makeRoom(map, floorTile, {{endc.w, endc.h},{1, -dy}});
    //doors
    if (dx >= 0) map->tileMap[startc.w+start.size.w/2][startc.h] = makeWoodenDoor(startc.w+start.size.w/2,startc.h);
}

bool squareInMap(int x, int y, int width, int height){
    //check if square with corner x,y is in map
    if (  game->map->inMap(x, y)
        &&game->map->inMap(x+width, y)
        &&game->map->inMap(x, y+height)
        &&game->map->inMap(x+width, y+height)
        )
        return true;
    else
        return false;
}

bool roomInMap(Room room){
    //check if square with corner x,y is in map
    if (  game->map->inMap(room.pos.w-1, room.pos.h-1)
        &&game->map->inMap(room.pos.w+room.size.w+1, room.pos.h-1)
        &&game->map->inMap(room.pos.w-1, room.pos.h+room.size.h+1)
        &&game->map->inMap(room.pos.w+room.size.w+1, room.pos.h+room.size.h+1)
        )
        return true;
    else
        return false;
}

rect roomCenter(Room room){
    return {room.pos.w+room.size.w/2, room.pos.h+room.size.h/2};
}

void makeDungeon(Map* map){
    map->ambientLight = {0,0,80};
    fillMap(map, CAVE_WALL);
    Generator dungeon;
    dungeon.map = map;
    dungeon.rooms = {};
    int nRooms = 5;
    int i = 0;
    while (i < nRooms){
        Room room;
        room.pos.w = rand()%map->mapWidth;
        room.pos.h = rand()%map->mapHeight;
        room.size.w = rand()%10+3;
        room.size.h = rand()%10+3;
        if (i == 0){
            room.pos.w = 9;
            room.pos.h = 9;
        }
        if (roomInMap(room)){
            makeRoom(map, CAVE_FLOOR, room);
            Entity* fireplace = makeFireplace(room.pos.w-1, room.pos.h+2);
            map->entityList.push_back(fireplace);
            makeHorde(map, *makeRat, roomCenter(room), rand()%4);
            if (i!=0){
                Room lastRoom = dungeon.rooms.back();
                makeCorridorwithDoors(map, CAVE_FLOOR, room, lastRoom);
            }
            dungeon.rooms.push_back(room);
            i++;
        }
    }
}

void makeHorde(Map* map, Entity*(*monster)(int posx, int posy), rect pos, int quantity){
    int monsters = 0;
    rect newpos = pos;
    while(monsters<quantity){
        newpos.w = pos.w+rand()%3;
        newpos.h = pos.h+rand()%3;
        if (!map->inMap(newpos.w, newpos.h)) continue;
        if (!map->tileMap[newpos.w][newpos.h]->walkable) continue;
        //if (map->getFighterAt(newpos.w, newpos.h)!=nullptr) continue;
        map->entityList.push_back(monster(newpos.w, newpos.h));
        monsters++;
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

void makeCave(Map* map){
    Perlin* floorPerlin = new Perlin(250);
    map->ambientLight = {0,30,60};
    fillMap(map, CAVE_WALL);
    rect pos;//position of drunk dwarf
    pos.h = game->map->mapHeight/2;
    pos.w = game->map->mapWidth/2;
    rect dir;//direction of drunk dwarf
    dir.h = 0;
    dir.w = 1;
    int steps = 1000; // steps taken by drunk dwarf
    int turnRate = 2; // average steps taken between turning
    int stepsMonsterRate = 20; // steps taken between spawning monsters
    for(int i=0; i<steps; i++){
        rect newPos;
        newPos.w = pos.w+dir.w;
        newPos.h = pos.h+dir.h;
        if(!map->inMap(newPos.w, newPos.h)){
            newPos.w = game->map->mapWidth/2;
            newPos.h = game->map->mapHeight/2;
        }
        map->tileMap[newPos.w][newPos.h] = tileFactory::makeTile(CAVE_FLOOR, newPos.w, newPos.h);
        if (rand()%turnRate==0){
            if(rand()%2==0){
                //horizontal
                dir.h = 0;
                dir.w = rand()%3-1;
            } else {
                //vertical
                dir.h = rand()%3-1;
                dir.w = 0;
            }
        }
        pos = newPos;
        //spawn monsters
        if (rand()%stepsMonsterRate==0){
            spawnMonsters(1, map, pos);
        }
    }
    for (int i = 0; i<map->mapWidth; i++){
        for (int j = 0; j<map->mapHeight; j++){
            if (floorPerlin->value(i*0.2, j*0.2) > 0.2){
                map->tileMap[i][j] = tileFactory::makeTile(CAVE_FLOOR, i, j);
            }
        }
    }
    map->entityList.push_back(makeMinersHat(game->map->mapWidth/2, game->map->mapHeight/2));
}