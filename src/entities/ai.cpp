#include "entity.hpp"
#include "ai.hpp"
#include "../map.hpp"
#include "../game.hpp"

Ai::~Ai(){};

void Ai::update(Entity* owner){};

void PlayerAi::update(Entity* owner){
    SDL_Event ev = game->currentEvent;
    switch (ev.type){
    case SDL_KEYDOWN:
        switch( ev.key.keysym.sym ){
            case SDLK_a:
                    PlayerAi::moveOrAttack(game->player, game->player->posX-1, game->player->posY);
                    break;
            case SDLK_d:
                    PlayerAi::moveOrAttack(game->player, game->player->posX+1, game->player->posY);
                    break;
            case SDLK_w:
                    PlayerAi::moveOrAttack(game->player, game->player->posX, game->player->posY-1);
                    break;
            case SDLK_x:
                    PlayerAi::moveOrAttack(game->player, game->player->posX, game->player->posY+1);
                    break;
            case SDLK_r:
                    PlayerAi::rest(game->player);
                    break;
            case SDLK_q:
                    PlayerAi::moveOrAttack(game->player, game->player->posX-1, game->player->posY-1);
                    break;
            case SDLK_z:
                    PlayerAi::moveOrAttack(game->player, game->player->posX-1, game->player->posY+1);
                    break;
            case SDLK_c:
                    PlayerAi::moveOrAttack(game->player, game->player->posX+1, game->player->posY+1);
                    break;
            case SDLK_e:
                    PlayerAi::moveOrAttack(game->player, game->player->posX+1, game->player->posY-1);
                    break;
        }
        break;
    default:
        break;
    }
};

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

void PlayerAi::moveOrAttack(Entity *owner, int targetX, int targetY){
        int turns = 0;// >0 if player has taken an action
        if (game->map->inMap(targetX, targetY)){// if target is inside map
            if (game->map->tileMap[targetX][targetY].walkable){// if target is walkable floor
                turns = 100; // 100 turns to walk, todo: make it depend on weight, race, effects etc...
                BipedalStepAnimation(owner->posX, owner->posY, targetX, targetY, this->rightStep);
                this->rightStep = !this->rightStep;
                owner->posX = targetX;
                owner->posY = targetY;
                owner->player->updateFov();
                game->map->moveCamera(targetX, targetY);
            }//if there is entity attackable attack it else:
        }

        game->turns = turns;
}

void PlayerAi::rest(Entity* owner){
    game->turns = 100;
}

void CritterAi::update(Entity* owner){
    while ( this->turns >= 200 ){
        //if (has_path){
            int dx = rand()%3-1;
            int dy = rand()%3-1;
            CritterAi::moveOrAttack(owner, owner->posX + dx, owner->posY + dy);
            this->turns -= 10; // this needs reworking
    }
}

void CritterAi::moveOrAttack(Entity* owner, int targetX, int targetY){
    int turns = 0;
    if (game->map->inMap(targetX, targetY)){
        if (game->map->tileMap[targetX][targetY].walkable && (targetX != owner->posX || targetY != owner->posY)){
            //tile is walkable and is different from current
            turns = 200;
            BipedalStepAnimation(owner->posX, owner->posY, targetX, targetY, rand()%2);
            owner->posX = targetX;
            owner->posY = targetY;
            if (owner->creature){
                //do things for creatures
            }
        }//if there is entity attackable attack it else:
    }
    this->turns -= turns;
};