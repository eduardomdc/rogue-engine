#include "game_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include <iostream>
#include "menu_window.hpp"

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
            game->inputManager = new MenuWindow();
            break;
        default:
            game->player->ai->update(game->player);
            break;
        }
    default: // with menus this will be alot more complicated
        break;
    }

    if (game->turns){//if player took action
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