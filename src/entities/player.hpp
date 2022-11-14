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
    bool pickup();
    std::vector<std::vector<short>> fov;
    std::vector<Entity> inventory;
private:
    int fovRadius = 24;
};

#endif