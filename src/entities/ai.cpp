#include "entity.hpp"
#include "ai.hpp"
#include "../map.hpp"
#include "../game.hpp"


void Ai::update(Entity* owner){};

void PlayerAi::update(Entity* owner){
    SDL_Event ev = game->currentEvent;
    switch (ev.type){
    case SDL_KEYDOWN:
        switch( ev.key.keysym.sym ){
            case SDLK_LEFT:
                    PlayerAi::moveOrAttack(game->player, game->player->posX-1, game->player->posY);
                    break;
            case SDLK_RIGHT:
                    PlayerAi::moveOrAttack(game->player, game->player->posX+1, game->player->posY);
                    break;
            case SDLK_UP:
                    PlayerAi::moveOrAttack(game->player, game->player->posX, game->player->posY-1);
                    break;
            case SDLK_DOWN:
                    PlayerAi::moveOrAttack(game->player, game->player->posX, game->player->posY+1);
                    break;
            case SDLK_r:
                    PlayerAi::rest(game->player);
                    break;
        }
        break;
    default:
        break;
    }
};

void PlayerAi::moveOrAttack(Entity *owner, int targetX, int targetY){
        int turns = 0;// >0 if player has taken an action
        if ((targetY>=0 && targetY< game->map->mapHeight) && (targetX>=0 && targetX< game->map->mapWidth)){// if target is inside map
            if (game->map->tileMap[targetX][targetY].walkable){// if target is walkable floor
                turns = 100; // 100 turns to walk, todo: make it depend on weight, race, effects etc...
                owner->posX = targetX;
                owner->posY = targetY;
                game->map->moveCamera(targetX, targetY);
            }//if there is entity attackable attack it else:
        }

        game->turns = turns;
}

void PlayerAi::rest(Entity* owner){
    game->turns = 100;
}

void CritterAi::update(Entity* owner){
    while ( this->turns >= 100 ){
        //if (has_path){
            int dx = rand()%3-1;
            int dy = rand()%3-1;
            CritterAi::moveOrAttack(owner, owner->posX + dx, owner->posY + dy);
    }
}

void CritterAi::moveOrAttack(Entity* owner, int targetX, int targetY){
    int turns = 0;
    if ((targetY>=0 && targetY< game->map->mapHeight) && (targetX>=0 && targetX< game->map->mapWidth)){
        if (game->map->tileMap[targetX][targetY].walkable){
            turns = 100;
            owner->posX = targetX;
            owner->posY = targetY;
        }//if there is entity attackable attack it else:
    }
    this->turns -= turns;
};