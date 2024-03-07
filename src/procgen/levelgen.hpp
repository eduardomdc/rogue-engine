#ifndef LEVELGEN_HPP
#define LEVELGEN_HPP

#include "../map.hpp"
#include <vector>

void makeTestChamber(Map* map);
void makeSnowyMountain(Map* map);
void makeForest(Map* map);
void makeDungeon(Map* map);
void makeBigHouse(Map* map);
void makeSewers(Map* map);
void makeCave(Map* map);


struct rect {
    int w;
    int h;
} typedef rect;

struct Room {
    rect pos;
    rect size;
} typedef Room;

class Generator {
public:
    Map* map;
    std::vector<Room> rooms;
    std::vector<Room> isInRooms(rect pos); // returns rooms that contain pos
};

bool inside(Room room, rect pos);
rect roomCenter(Room room);
void makeHorde(Map* map, Entity*(*monster)(int posx, int posy), rect pos, int quantity);
void spawnMonsters(int level, Map* map, rect pos);


#endif
