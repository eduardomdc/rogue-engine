#include "entity.hpp"
#include "ai.hpp"
#include "../animations/animation.hpp"
#include "../map.hpp"
#include "../game.hpp"
#include <iostream>
#include "../actions/action.hpp"
#include "../inputManager/pickup_inventory_window.hpp"

Ai::Ai(Entity* owner){
    this->owner = owner;
}

Ai::~Ai(){
    path = std::list<position>();
};

void Ai::update(){};

void PlayerAi::update(){
    SDL_Event ev = game->currentEvent;
    /*
    if (owner->player->walkQueue.size() > 0){
        PlayerAi::moveFromWalkQueue();
        return; // if player has queued up moves he can't play
    }*/
    switch (ev.type){
        /** mouse support!!
        case SDL_MOUSEBUTTONDOWN:
            switch(ev.button.button){
                case SDL_BUTTON_LEFT:
                    owner->player->getWalkQueue(ev);
                    moveFromWalkQueue(owner);
                    break;
                default:
                    break;
            }
            break;
        **/
        case SDL_KEYDOWN:
            switch( ev.key.keysym.sym ){
                case SDLK_a:
                        PlayerAi::moveOrAttack(game->player->posX-1, game->player->posY);
                        break;
                case SDLK_d:
                        PlayerAi::moveOrAttack(game->player->posX+1, game->player->posY);
                        break;
                case SDLK_w:
                        PlayerAi::moveOrAttack(game->player->posX, game->player->posY-1);
                        break;
                case SDLK_x:
                        PlayerAi::moveOrAttack(game->player->posX, game->player->posY+1);
                        break;
                case SDLK_r:
                        PlayerAi::rest();
                        break;
                case SDLK_q:
                        PlayerAi::moveOrAttack(game->player->posX-1, game->player->posY-1);
                        break;
                case SDLK_z:
                        PlayerAi::moveOrAttack(game->player->posX-1, game->player->posY+1);
                        break;
                case SDLK_c:
                        PlayerAi::moveOrAttack(game->player->posX+1, game->player->posY+1);
                        break;
                case SDLK_e:
                        PlayerAi::moveOrAttack(game->player->posX+1, game->player->posY-1);
                        break;
                case SDLK_g:
                        PlayerAi::pickUp();
                        break;
                case SDLK_o:
                        PlayerAi::openDoor();
                        break;
            }
            break;
        default:
            break;
    }
};

void PlayerAi::moveFromWalkQueue(){
    position dest = this->owner->player->walkQueue.front();
    this->owner->player->walkQueue.pop_front();
    PlayerAi::moveOrAttack(dest.x, dest.y);
}

void PlayerAi::pickUp(){
    int turns = 0;
    if (owner->pickUp()){
        std::cout<<"player picks up"<<std::endl;
        turns = 1;
        game->turns = turns;
        return;
    }
    std::vector<Entity*>::iterator item;
    item = game->map->entityList.bottom.begin();
    while(item != game->map->entityList.bottom.end()){
        if ((*item)->posX == this->owner->posX 
            && (*item)->posY == this->owner->posY){
            std::cout<<"entity"<<std::endl;
            if((*item)->inventory.size()>0){
                std::cout << "open inventory window for chest" << std::endl;
                game->windows.push_back(new PickupInventoryWindow(*item));
                return;
            }
        }
        item++;
    }
    return;
}

void PlayerAi::moveOrAttack(int targetX, int targetY){
        if (game->map->inMap(targetX, targetY)){// if target is inside map
            if ((game->map->tileMap[targetX][targetY]->walkable) 
                && (targetX != owner->posX || targetY != owner->posY)){// if target is walkable floor
            Entity* targetEntity = game->map->getFighterAt(targetX, targetY);
            if (targetEntity){
                attackAction(this->owner, targetEntity);
                game->turns = 1; //takes one action to attack
            } else if (targetEntity==nullptr) { // only go if there are no fighters there
                bipedalStepAnimation(this->owner->posX, owner->posY, targetX, targetY, this->rightStep);
                this->rightStep = !this->rightStep;
                moveAction(this->owner, targetX, targetY);
                this->owner->player->updateFov();
                game->map->moveCamera(targetX, targetY);
                game->turns = 1; //takes one action to move
            }
            } 
        }
}

void PlayerAi::rest(){
    game->turns = 1;
}

void PlayerAi::openDoor(){
    // search for doors in players neighborhood
    for (int i=owner->posX-1; i<=owner->posX+1; i++){
        for (int j=owner->posY-1; j<=owner->posY+1; j++){
            if (game->map->tileMap[i][j]->door != nullptr){
                openDoorAction(owner, i, j);
                return;
            }
        }
    }
}

float euclideanDistance(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void CritterAi::update(){
    // look for player
    try 
    {
    if (euclideanDistance(this->owner->posX, this->owner->posY, game->player->posX, game->player->posY) < 10){
        path = straightPath({this->owner->posX,owner->posY},{game->player->posX, game->player->posY});
    }

    if (path.size() == 0){
        //if there is no path to player
        int dx = rand()%3-1;
        int dy = rand()%3-1;
        if (std::abs(owner->posX-game->player->posX) <= 1 && std::abs(owner->posY-game->player->posY) <= 1){
            CritterAi::moveOrAttack(game->player->posX, game->player->posY);
        } else {
            CritterAi::moveOrAttack(owner->posX + dx, owner->posY + dy);
        }
    }
    else {
        position* step = &path.front();
        CritterAi::moveOrAttack(step->x, step->y);
        path.pop_front();
    }
    

    }
    catch (...){std::cout<<"Critter AI error" << std::endl;}
}

void CritterAi::moveOrAttack(int targetX, int targetY){
    Entity* targetEntity;
    if (game->map->inMap(targetX, targetY)){
        if (game->map->tileMap[targetX][targetY]->walkable && (targetX != owner->posX || targetY != owner->posY)){
            targetEntity = game->map->getFighterAt(targetX, targetY);
            if (targetEntity){
                if (targetEntity == game->player){
                    attackAction(this->owner, game->player);
                }
            } else if (targetEntity==nullptr) { // only go if there are no fighters there
                bipedalStepAnimation(this->owner->posX, this->owner->posY, targetX, targetY, rand()%2);
                moveAction(this->owner, targetX, targetY); 
                if (this->owner->creature){
                    //do things for creatures
                }
            } else {
                // wait
                //this->turns -= 10;
            }
            
        }//if there is entity attackable attack it else:
    }
};
