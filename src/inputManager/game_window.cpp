#include "game_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <iostream>
#include "menu_window.hpp"
#include "inventory_window.hpp"
#include "../draw/draw_ui.hpp"

GameWindow::GameWindow(){
    std::cout << "Game Window created" << std::endl;
}

void GameWindow::handleInput(SDL_Event currentEvent) {
    game->turns = 0; //after every event turns taken are set to 0 again

    switch (currentEvent.type){
    case SDL_QUIT:
        std::cout << "Quit game from game window Pressed" << std::endl;
        game->isRunning = false;
        //game->inputManager = new MenuWindow();
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
            std::cout << "Open menu window" << std::endl;
            game->windows.push_back(new MenuWindow());
            break;
        case SDLK_i:
            std::cout << "Open inventory window" << std::endl;
            game->windows.push_back(new InventoryWindow());
        default:
            game->player->ai->update(game->player);
            break;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        game->player->ai->update(game->player);
        break;
    default:
        break;
    }

    if (game->turns && game->player->player->walkQueue.size() == 0){//if player took action
        for (Entity* ent : game->map->entityList){
            if (ent != game->player){
                if (ent->ai){
                    //increment turns
                    ent->ai->turns += game->turns;
                    ent->ai->update(ent);
                }
            }
        }
    }
    else if (game->player->player->walkQueue.size() > 0){
        while (game->player->player->walkQueue.size() > 0){
            game->player->ai->update(game->player);
            for (Entity* ent : game->map->entityList){
                if (ent != game->player){
                    if (ent->ai){
                        //increment turns
                        ent->ai->turns += game->turns;
                        ent->ai->update(ent);
                    }
                }
            }
        }
    }
}

void GameWindow::render(){
    game->map->drawMap();
    // draw entities
    for (Entity* ent : game->map->entityList){
        ent->render();
        if (ent->particleEmitter){
            if (game->player->player->canSee(ent->posX, ent->posY)){
                ent->particleEmitter->update();
            }
        }
    }
    std::vector<Animation*>::iterator it;

    it = game->animationList.begin();
    while (it != game->animationList.end()){
        Animation* anim = *it;
        anim->render();
        
        if (anim->done == true){
            it = game->animationList.erase(it);
        } else {
            it++;
        }
    }

    // draw path to mouse
    int x,y;
    SDL_GetMouseState(&x,&y);
    std::list<position>::iterator itui;
    std::list<position> path = bresenham({game->map->mapRenderWidth/2-1, game->map->mapRenderHeight/2}, {x/20-game->map->mapRenderWidth/2+1,y/20-game->map->mapRenderHeight/2});
    path.pop_front();
    itui = path.begin();
    while (itui != path.end()){
        drawTileSelect(itui->x, itui->y);
        itui++;
    }
}