#include "item_window.hpp"
#include <SDL_events.h>
#include "../game.hpp"
#include "../colors.hpp"
#include "../draw/draw_ui.hpp"

ItemWindow::ItemWindow(Entity* item){
    std::cout << "Item window created" << std::endl;
    this->item = item;
}

void ItemWindow::handleInput(SDL_Event currentEvent){
    switch (currentEvent.type) {
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym) {
            case SDLK_ESCAPE:
                std::cout << "Close item window" <<std::endl;
                close();
                delete this;
                break;
            case SDLK_e:
                std::cout << "Equip item!"<<std::endl;
                game->player->fighter->equipItem(this->item);
                close();
                delete this;
                break;
            case SDLK_d:
                std::cout << "Drop item!"<<std::endl;
                game->player->drop(this->item);
                close();
                delete this;
                break;
            default:
                break;
        }
    default:
        break;
    }
}

void ItemWindow::render(){
    int posX = 5;
    int posY = 15;
    int width = 16;
    int height = 22;
    drawWindowAndTitle(this->item->name, posX, posY, width, height, colors::grey, colors::black);
    renderText("[e] to equip", posX, posY+5, colors::grey, false);
    renderText("[d] to drop", posX, posY+6, colors::grey, false);
}
