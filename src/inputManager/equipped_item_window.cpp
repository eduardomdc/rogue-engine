#include "equipped_item_window.hpp"
#include <SDL_events.h>
#include <string>
#include <sstream>
#include "../game.hpp"
#include "../colors.hpp"
#include "../draw/draw_ui.hpp"
#include "../draw/tile_manager.hpp"
#include "item_window.hpp"

EquippedItemWindow::EquippedItemWindow(Entity* item){
    std::cout << "Equipped item window created" << std::endl;
    this->item = item;
}

void EquippedItemWindow::handleInput(SDL_Event currentEvent){
    switch (currentEvent.type) {
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym) {
            case SDLK_ESCAPE:
                std::cout << "Close equipped item window" <<std::endl;
                close();
                delete this;
                break;
            case SDLK_e:
                std::cout << "Unequip item!"<<std::endl;
                if (game->player->fighter->unequipItem(this->item->item->equipSlot)){
                    game->turns = 1;
                    game->turn();
                    close();
                    delete this;
                }
                break;
            default:
                break;
        }
    default:
        break;
    }
}

void EquippedItemWindow::render(){
    int posX = 2;
    int posY = 2;
    int width = 16;
    int height = 22;
    renderItemInfo(item, posX, posY, width, height);
    renderText("[e] to unequip", posX, posY+21, colors::grey, false);
}
