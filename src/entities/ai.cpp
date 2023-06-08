#include "entity.hpp"
#include "ai.hpp"
#include "../map.hpp"
#include "../game.hpp"
#include <iostream>
#include "../actions/action.hpp"

Ai::Ai(Entity* owner){
    this->owner = owner;
}

Ai::~Ai(){
    path = std::list<position>();
};

void Ai::update(){};

void PlayerAi::update(){
    SDL_Event ev = game->currentEvent;
    if (owner->player->walkQueue.size() > 0){
        PlayerAi::moveFromWalkQueue();
        return; // if player has queued up moves he can't play
    }
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

void BipedalStepAnimation(int posX, int posY, int targetX, int targetY, bool rightStep){
    Animation* step = new Animation();
    step->foreRgb = colors::grey;
    step->setFrames({"#","*","."," "});
    step->posX = posX;
    step->speed = 100;
    step->posY = posY;
    if (targetY > posY){
        step->subPosY = 1;
        if (rightStep){
            step->subPosX = 0;
        } else step->subPosX = 1;
    } else if (targetY < posY) {
        step->subPosY = 0;
        if (rightStep){
            step->subPosX = 0;
        } else step->subPosX = 1;
    }
    if (targetX > posX){
        step->subPosX = 1;
        if (rightStep){
            step->subPosY = 0;
        } else step->subPosY = 1;
    } else if (targetX < posX) {
        step->subPosX = 0;
        if (rightStep){
            step->subPosY = 0;
        } else step->subPosY = 1;
    }

    step->onMap = true;
    game->animationList.push_back(step);
}

void PlayerAi::pickUp(){
    int turns = 0;
    if (owner->pickUp()){
        turns = 100;
    }
    game->turns = turns;
    return;
}

void PlayerAi::moveOrAttack(int targetX, int targetY){
        int turns = 0;// >0 if player has taken an action
        if (game->map->inMap(targetX, targetY)){// if target is inside map
            if (game->map->tileMap[targetX][targetY].walkable){// if target is walkable floor
                turns = 100; // 100 turns to walk, todo: make it depend on weight, race, effects etc...
                BipedalStepAnimation(this->owner->posX, owner->posY, targetX, targetY, this->rightStep);
                this->rightStep = !this->rightStep;
                this->owner->posX = targetX;
                this->owner->posY = targetY;
                this->owner->player->updateFov();
                game->map->moveCamera(targetX, targetY);
            }//if there is entity attackable attack it else:
        }
        game->turns = turns;
}

void PlayerAi::rest(){
    game->turns = 100;
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

    while ( this->turns >= 200 ){
        if (path.size() == 0){
            int dx = rand()%3-1;
            int dy = rand()%3-1;
            CritterAi::moveOrAttack(owner->posX + dx, owner->posY + dy);
            this->turns -= 10; // this needs reworking
        }
        else {
            position* step = &path.front();
            CritterAi::moveOrAttack(step->x, step->y);
            path.pop_front();
        }
    }
    }
    catch (...){std::cout<<"Critter AI error" << std::endl; }
}

void CritterAi::moveOrAttack(int targetX, int targetY){
    int turns = 0; // turns this AI will take this round
    Entity* targetEntity;
    if (game->map->inMap(targetX, targetY)){
        if (game->map->tileMap[targetX][targetY].walkable && (targetX != owner->posX || targetY != owner->posY)){
            targetEntity = game->map->getFighterAt(targetX, targetY);
            if (targetEntity){
                if (targetEntity == game->player){
                    attackAction(this->owner, game->player);
                }
            } else if (targetEntity==nullptr) { // only go if there are no fighters there
                turns = 150;
                BipedalStepAnimation(this->owner->posX, this->owner->posY, targetX, targetY, rand()%2);
                this->owner->posX = targetX;
                this->owner->posY = targetY;
                if (this->owner->creature){
                    //do things for creatures
                }
            } else {
                // wait
                turns = 50;
            }
            
        }//if there is entity attackable attack it else:
    }
    this->turns -= turns;
};
