#include "menu_window.hpp"
#include "../game.hpp"
#include "game_window.hpp"
#include "../draw/draw_ui.hpp"

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
            std::cout << "Remove menu window" << std::endl;
            close();
            delete this;
            break;
        case SDLK_q:
            std::cout<< "Quit Pressed" << std::endl;
            game->isRunning = false;
            break;
        }
    }
}

void MenuWindow::render(){
    renderText("Options Menu", 35, 35, colors::white, false);
    renderText("Q to quit", 35, 36, colors::white, false);
}
