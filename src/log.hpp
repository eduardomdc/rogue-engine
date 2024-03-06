#ifndef LOG_HPP
#define LOG_HPP

#include "colors.hpp"
#include <string>
#include <SDL.h>

struct msg {
    color col;
    std::string text;
} typedef msg;

void localMsg(SDL_Point pos, std::string text, color color);
void localMsg(SDL_Point pos, std::string text);
void globalMsg(std::string text, color color);
void globalMsg(std::string text);

#endif