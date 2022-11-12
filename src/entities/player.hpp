#ifndef PLAYER_HPP
#define PLAYER_HPP

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
    std::vector<std::vector<bool>> fov;
    // std::list<position> newFov;
    int fovRadius;
};

#endif