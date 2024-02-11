#include "item_window.hpp"
#include <SDL_events.h>
#include <string>
#include <sstream>
#include "../game.hpp"
#include "../colors.hpp"
#include "../draw/draw_ui.hpp"
#include "../draw/tile_manager.hpp"

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
    int posX = 2;
    int posY = 2;
    int width = 16;
    int height = 22;
    drawWindowAndTitle(this->item->name, posX, posY, width, height, colors::grey, colors::black);
    SDL_Texture* codepage = game->codepageBig;
    SDL_Rect src;
    SDL_Rect dest;
    dest.x = (posX+width/2-1)*10;
    dest.y = (posY+1)*10;
    game->tileManager->drawAscii(codepage,src,dest,this->item->ch,this->item->foreRgb,20,20,16, 16);
    if (this->item->item->type == itemType::WEAPON){
        std::string damage = "Damage "; 
        damage.append(std::to_string(this->item->item->dieAmount));
        damage.append("d");
        damage.append(std::to_string(this->item->item->damageDie));
        if (this->item->item->damageMod){
            damage.append("+");
            damage.append(std::to_string(this->item->item->damageMod));
        }
        renderText(damage, posX, posY+5, colors::red, false);
    }
    std::ostringstream weight;
    weight<<"W";
    weight.precision(2);
    weight<<(this->item->item->weight);
    weight<<"Kg";
    renderText(weight.str(), posX, posY+6, colors::grey, false);
    if (item->item->equipable)
        renderText("[e] to equip", posX, posY+20, colors::grey, false);
    renderText("[d] to drop", posX, posY+21, colors::grey, false);
}
