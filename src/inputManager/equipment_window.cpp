#include "equipment_window.hpp"
#include "../game.hpp"
#include "equipped_item_window.hpp"

EquipmentWindow::EquipmentWindow(){
    return;
}

void EquipmentWindow::handleInput(SDL_Event currentEvent){
    std::vector<Entity*>* equipments = game->player->fighter->equipments;
    switch (currentEvent.type){
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
            std::cout << "Close equipment window" << std::endl;
            close();
            delete this;
            break;
        // default:
        //     if (currentEvent.key.keysym.sym >= 97
        //         && currentEvent.key.keysym.sym <= 122){
        //         std::vector<Entity*>* equipments = game->player->fighter->equipments;
        //         int selected = currentEvent.key.keysym.sym-97;

        //         // if (equipments->size()>selected){
        //         //     Entity* item=inventory[selected]; 
        //         //     game->windows.push_back(new ItemWindow(item));
        //         // }
        //     } 
        //     break;
        case SDLK_w:
            if ((*equipments)[equipSlots::HEAD] != nullptr){
                std::cout << "Head equipment selected" << std::endl;
                Entity* item = (*equipments)[equipSlots::HEAD];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        case SDLK_a:
            if ((*equipments)[equipSlots::HAND1] != nullptr){
                std::cout << "Hand1 equipment selected" << std::endl;
                Entity* item = (*equipments)[equipSlots::HAND1];
                game->windows.push_back(new EquippedItemWindow(item));
            }
            break;
        }
        break;
    default:
        break;
    }
}

void EquipmentWindow::render(){
    return;
}