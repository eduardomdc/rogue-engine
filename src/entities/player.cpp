#include "player.hpp"

#include "../game.hpp"
#include "../map.hpp"
#include "../algorithms/fov.hpp"
#include <iostream>

Player::Player(Entity* owner){
    this->owner = owner;
    this->fovRadius = game->screenW/10;
    owner->inventory = std::vector<Entity*>();
    updateFov();
    std::vector<std::vector <short>> fov (fovRadius*2+1, std::vector <short>(fovRadius*2+1, 0));
    game->map->moveCamera(game->player->posX,game->player->posY);
}

void Player::updateFov(){
    // fov = getVisibleRadius(owner->posX, owner->posY, fovRadius);
    fov = computeFOV(owner->posX, owner->posY, fovRadius);
    // update map fog
    for (int x=0; x<game->map->mapWidth; x++){
        for(int y=0; y<game->map->mapHeight; y++){
            int dx = x - this->owner->posX + fovRadius;
            int dy = y - this->owner->posY + fovRadius;
            if (fov[dx][dy] == true && game->map->fog[x][y] == false){
                game->map->fog[x][y] = true;
            }
        }
    }
}

void Player::getWalkQueue(SDL_Event mouse){
    int screenX = mouse.button.x/20;
    int screenY = mouse.button.y/20;
    int x = screenX + game->map->leftSide - game->map->mapOffsetX;
    int y = screenY + game->map->topSide - game->map->mapOffsetY;
    this->walkQueue = straightPathToWall({owner->posX, owner->posY}, {x,y});
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

// bool Player::pickup(){
//     // picks up item from floor and adds it to inventory, returns true if picked-up something
//     // to do: menu to select between items
//     std::vector<Entity*>::iterator item;
//     item = game->map->entityList.begin();
//     while(item != game->map->entityList.end()){
//         if ((*item)->object != nullptr){
//             if ((*item)->object->pickable && (*item)->posX == owner->posX && (*item)->posY == owner->posY){
//                 inventory.push_back(**item);
//                 game->map->entityList.erase(item);
//                 return true;
//             }
//         }
//         item++;
//     }
//     return false;
// }
