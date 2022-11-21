#include "levelgen.hpp"
#include "../algorithms/perlin.hpp"
#include "../entities/monster_factory.hpp"
#include <iostream>

void makeSnowyMountain(Map* map){
    //generate perlin map
    Perlin* wallPerlin = new Perlin(250);
    Perlin* mossPerlin = new Perlin(250);
    std::cout << "Perlin noise generated" << std::endl;

    // add floor tiles
    for (int i = 0; i<map->mapWidth; i++){
        map->tileMap.push_back( std:: vector< Tile >() );
        for (int j = 0; j<map->mapHeight; j++){
            map->tile = tileFactory::makeTile(CAVE_FLOOR, i, j);
            map->tileMap[i].push_back(*map->tile);
        }
    }

    // add rock walls and vegetation
    for (int i = 0; i<map->mapWidth; i++){
        for (int j = 0; j<map->mapHeight; j++){
            if (wallPerlin->value(i*0.1,j*0.1) > 0.3){
                map->tileMap[i][j] = *tileFactory::makeTile(CAVE_WALL, i, j);
            }
            else if (mossPerlin->value(i*0.2,j*0.2) > 0.1){
                map->tileMap[i][j] = *tileFactory::makeTile(CAVE_MOSSY_FLOOR, i, j);
            }
        }
    }
    int count = 0;
    //add wolves
    for (int i = 0; i<map->mapWidth; i++){
        for (int j = 0; j<map->mapHeight; j++){
            if (rand()%1000==0){
                if (map->tileMap[i][j].walkable){
                    count++;
                    Entity* monster = makeMonster(WOLF, i, j);
                    map->entityList.push_back(monster);
                }
            }
        }
    }
    std::cout<<count<<" wolves"<<std::endl;
}