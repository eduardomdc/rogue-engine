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
                    game->player->posX -=1;
                    game->map->moveCamera(game->map->mapPositionX-1, game->map->mapPositionY);
                    break;
            case SDLK_RIGHT:
                    game->player->posX +=1;
                    game->map->moveCamera(game->map->mapPositionX+1, game->map->mapPositionY);
                    break;
            case SDLK_UP:
                    game->player->posY -=1;
                    game->map->moveCamera(game->map->mapPositionX, game->map->mapPositionY-1);
                    break;
            case SDLK_DOWN:
                    game->player->posY +=1;
                    game->map->moveCamera(game->map->mapPositionX, game->map->mapPositionY+1);
                    break;
        }
        break;
    default:
        break;
    }
};