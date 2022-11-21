#ifndef INVENTORY_WINDOW_HPP
#define INVENTORY_WINDOW_HPP

#include "input_manager.hpp"

class InventoryWindow : public InputManager {
public:
    InventoryWindow();
    virtual void handleInput(SDL_Event currentEvent);
    virtual void render();
};

#endif