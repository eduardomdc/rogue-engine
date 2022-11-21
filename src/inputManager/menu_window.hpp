#ifndef MENU_WINDOW_HPP
#define MENU_WINDOW_HPP

#include "input_manager.hpp"

class MenuWindow : public InputManager {
public:
    MenuWindow();
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
};

#endif