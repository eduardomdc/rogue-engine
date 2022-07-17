#include "entity.hpp"
#include "ai.hpp"
#include "../map.hpp"
#include "../game.hpp"


void Ai::update(Entity* owner){

};

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
        }
        break;
    default:
        break;
    }
};

bool PlayerAi::moveOrAttack(Entity *owner, int targetX, int targetY){
        // to do: return units of time wasted, implement granular time rounds
        bool turned = false;// true if player has taken an action
        if ((targetY>=0 && targetY< game->map->mapHeight) && (targetX>=0 && targetX< game->map->mapWidth)){// if target is inside map
            if (game->map->tileMap[targetX][targetY].walkable){// if target is walkable floor
                turned = true;
                //if there is entity destructable attack it else:
                owner->posX = targetX;
                owner->posY = targetY;
                game->map->moveCamera(targetX, targetY);
            }
        }

        return turned;
}