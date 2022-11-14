#include "player.hpp"

#include "../game.hpp"
#include "../map.hpp"
#include "../algorithms/fov.hpp"
#include <iostream>

Player::Player(Entity* owner){
    this->owner = owner;
    this->inventory = std::vector<Entity>();
    updateFov();
    std::vector<std::vector <short>> fov (fovRadius*2+1, std::vector <short>(fovRadius*2+1, 0));
}

void Player::updateFov(){
    // fov = getVisibleRadius(owner->posX, owner->posY, fovRadius);
    fov = computeFOV(owner->posX, owner->posY, fovRadius);
}

bool Player::canSee(int x, int y){
    int dx = x - this->owner->posX + fovRadius;
    int dy = y - this->owner->posY + fovRadius;
    if (dx >= 0 && dx <= fovRadius*2 && dy >= 0 && dy <= fovRadius*2){
        return fov[dx][dy];
    } else {
        return false;
    }
}

bool Player::pickup(){
    // picks up item from floor and adds it to inventory, returns true if picked-up something
    // to do: menu to select between items
    std::vector<Entity*>::iterator item;
    item = game->map->entityList.begin();
    while(item != game->map->entityList.end()){
        if ((*item)->object != nullptr){
            if ((*item)->object->pickable && (*item)->posX == owner->posX && (*item)->posY == owner->posY){
                inventory.push_back(**item);
                game->map->entityList.erase(item);
                return true;
            }
        }
        item++;
    }
    return false;
}