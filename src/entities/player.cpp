#include "player.hpp"

#include "../game.hpp"
#include "../map.hpp"
#include "../algorithms/fov.hpp"
#include <iostream>

Player::Player(Entity* owner){
    this->owner = owner;
    updateFov();
    fovRadius = 24;
    // std::vector<std::vector<bool>> fov = std::vector<std::vector <bool>>( fovRadius*2+1, std::vector <bool>(fovRadius*2+1, false));
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