#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include <list>
#include "../algorithms/fov.hpp"

class Entity;

class Player {
public:
    Player(Entity* owner);
    Entity* owner;
    bool canSee(int x, int y);
    void updateFov();
    void getWalkQueue(SDL_Event mouse);
    bool pickup();
    std::vector<std::vector<short>> fov;
    std::vector<Entity> inventory = {};
    std::list<position> walkQueue = {};
private:
    int fovRadius = 24;
};

#endif