#include "menu_window.hpp"
#include "../game.hpp"
#include "game_window.hpp"

MenuWindow::MenuWindow(){
    std::cout << "MenuWindow created" << std::endl;
}

void MenuWindow::handleInput(SDL_Event currentEvent) {
    switch (currentEvent.type){
    case SDL_QUIT:
        std::cout << "Quit Pressed" << std::endl;
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
            std::cout << "Open game window" << std::endl;
            game->inputManager = new GameWindow();
            break;
        }
    }

}