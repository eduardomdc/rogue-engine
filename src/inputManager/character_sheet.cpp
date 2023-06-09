#include "character_sheet.hpp"
#include "../game.hpp"
#include "../draw/draw_ui.hpp"
#include "../colors.hpp"
#include <SDL_events.h>
#include <string>

CharacterSheet::CharacterSheet(){
    std::cout<<"Character sheet window created"<<std::endl;
}

void CharacterSheet::handleInput(SDL_Event currentEvent){
    switch (currentEvent.type) {
    case SDL_QUIT:
        game->isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch(currentEvent.key.keysym.sym){
        case SDLK_ESCAPE:
            std::cout<<"Close CharacterSheet window"<<std::endl;
            close();
            delete this;
            break;
        case SDLK_TAB:
            std::cout<<"Close CharacterSheet window"<<std::endl;
            close();
            delete this;
            break;
        }
        break;
    default:
        break;
    }
}

void CharacterSheet::render(){
    int posX = 5;
    int posY = 5;
    int width = 30;
    int height = 25;
    drawWindowAndTitle("Character Status", posX, posY, width, height, colors::grey, colors::black);
    renderText("Level ", posX, posY, colors::grey, false);
    renderText("Attributes", posX, posY+1, colors::grey, false);
    renderText("Strength", posX, posY+2, colors::grey, false);
    renderText(std::to_string(game->player->fighter->str), posX+16, posY+2, colors::grey, false);
    renderText("Agility", posX, posY+3, colors::grey, false);
    renderText(std::to_string(game->player->fighter->agi), posX+16, posY+3, colors::grey, false);
    renderText("Dexterity", posX, posY+4, colors::grey, false);
    renderText(std::to_string(game->player->fighter->dex), posX+16, posY+4, colors::grey, false);
    renderText("Constitution", posX, posY+5, colors::grey, false);
    renderText(std::to_string(game->player->fighter->con), posX+16, posY+5, colors::grey, false);
    renderText("Intelligence", posX, posY+6, colors::grey, false);
    renderText(std::to_string(game->player->fighter->itl), posX+16, posY+6, colors::grey, false);
    renderText("Wisdom", posX, posY+7, colors::grey, false);
    renderText(std::to_string(game->player->fighter->wis), posX+16, posY+7, colors::grey, false);
    renderText("Luck", posX, posY+8, colors::grey, false);
    renderText(std::to_string(game->player->fighter->luck), posX+16, posY+8, colors::grey, false);

}
