#include "entity.hpp"
#include "ai.hpp"
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
                    //map->moveCamera(map->mapPositionX-1, map->mapPositionY);
        }
        break;
    default:
        break;
    }
};