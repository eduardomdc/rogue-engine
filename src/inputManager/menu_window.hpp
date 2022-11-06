#ifndef MENU_WINDOW_HPP
#define MENU_WINDOW_HPP

#include <SDL2/SDL.h>
#include "input_manager.hpp"

class MenuWindow : public InputManager {
public:
    MenuWindow();
    virtual void handleInput(SDL_Event currentEvent);
};

#endif