#include "equipment_window.hpp"
#include "../game.hpp"
#include "../map.hpp"
#include "equipped_item_window.hpp"
#include "../draw/draw_ui.hpp"


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

void renderSlot(equipSlots::equipSlots slot, int px, int py){
    std::vector<Entity*>* equipments = game->player->fighter->equipments;
    game->tileManager->drawSmallAsciiUI(px-1,py, "[", colors::grey);
    if ((*equipments)[slot] != nullptr)
        game->tileManager->drawSmallAsciiUI(px,py, (*equipments)[slot]->ch, (*equipments)[slot]->foreRgb);
    game->tileManager->drawSmallAsciiUI(px+1,py, "]", colors::grey);
}

void EquipmentWindow::render(){
    std::vector<Entity*>* equipments = game->player->fighter->equipments;
    int px = (game->map->mapRenderWidth/3)*2-2;
    int py = 2;
    int width = 25;
    int height = 25;
    drawWindowAndTitle("Equipment",px,py,width,height,colors::grey, colors::black);
    renderSlot(equipSlots::HEAD, px+width/2, py+2);
    renderSlot(equipSlots::NECK, px+width/2, py+4);
    renderSlot(equipSlots::BODY, px+width/2, py+7);
    renderSlot(equipSlots::HAND1, px+width/3, py+8);
    renderSlot(equipSlots::HAND2, px+2*width/3, py+8);
    renderSlot(equipSlots::RING1, px+width/3, py+5);
    renderSlot(equipSlots::RING2, px+2*width/3, py+5);
    renderSlot(equipSlots::LEG, px+width/2, py+10);
    renderSlot(equipSlots::FEET, px+width/2, py+12);
}