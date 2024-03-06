#include "log.hpp"
#include "colors.hpp"
#include "game.hpp"

void localMsg(SDL_Point pos, std::string text, color col){
    msg msg;
    msg.text = text;
    msg.col = col;
    if (game->player->player->canSee(pos.x, pos.y)){
        game->log.push_back(msg);
    }
}


void localMsg(SDL_Point pos, std::string text){
    msg msg;
    msg.text = text;
    msg.col = colors::grey;
    if (game->player->player->canSee(pos.x, pos.y)){
        game->log.push_back(msg);
    }
}

void globalMsg(std::string text, color col){
    msg msg;
    msg.text = text;
    msg.col = col;
    game->log.push_back(msg);
}

void globalMsg(std::string text){
    msg msg;
    msg.text = text;
    msg.col = colors::grey;
    game->log.push_back(msg);
}